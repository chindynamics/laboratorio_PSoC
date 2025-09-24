/**
 * DDisplay.c
 * Implementación interna de la librería DDisplay.
 * Contiene la lógica y el manejo de estado para el control
 * de un display dual de 7 segmentos.
 */

#include "DDisplay.h"
#include "project.h"

/* VARIABLES DE ESTADO INTERNAS (OCULTAS AL USUARIO) */

// Variables para el estado general y los modos numéricos
static uint8 _mode = DDISPLAY_MODE_NONE;        // Guarda el modo de operación actual.
static uint16 _status = DDISPLAY_SEGMENT_NONE;  // Guarda el último patrón de 16 bits enviado al hardware.
static uint8 _value = 0;                        // Guarda el último valor numérico establecido.

// Variables de estado específicas para el modo de patrones
static const uint16 *_patterns = NULL;          // Puntero al arreglo de patrones personalizados.
static uint8 _patterns_size = 0;                // Tamaño del arreglo de patrones.
static uint8 _patterns_index = 0;               // Índice del patrón que se muestra actualmente.

/* CONSTRUCCIÓN DE FUNCIONES OCULTAS AL USUARIO (NO DEBE DE INTERACTURA CON ESTAS FUNCIONES DIRECTAMENTE) */
static void DDisplay_WriteToPorts(uint16 leds);
static void getIndexes(uint8 number, uint8 *tens, uint8 *units);

/* TABLA DE CONSULTA PARA DÍGITOS 0-F */
// Es guardada en la ROM al usar const y así evitar guardarlo en la RAM. Es compartida por todas las funciones
static const uint8 _num_patterns[] = {
    DDISPLAY_0,
    DDISPLAY_1,
    DDISPLAY_2,
    DDISPLAY_3,
    DDISPLAY_4,
    DDISPLAY_5,
    DDISPLAY_6,
    DDISPLAY_7,
    DDISPLAY_8,
    DDISPLAY_9,
    DDISPLAY_A,
    DDISPLAY_B,
    DDISPLAY_C,
    DDISPLAY_D,
    DDISPLAY_E,
    DDISPLAY_F,
};

/* IMPLEMENTACIÓN DE FUNCIONES DEL DDISPLAY.H */
// La documentación detallada de lo que hacen estas funciones está en el archivo DDISPLAY.H

void DDisplay_Start(void) {
    _mode = DDISPLAY_MODE_NONE;
    _status = DDISPLAY_SEGMENT_NONE;
    _value = 0;
    _patterns = NULL;
    _patterns_size = 0;
    _patterns_index = 0;
    DDisplay_WriteToPorts(_status);     
}

uint8 DDisplay_GetMode(void) {
    return _mode;
}

void DDisplay_SetMode(uint8 mode) {
    _mode = mode;
    
    // Al cambiar de modo, se muestra un 0 para los modos numéricos
    switch(mode) {
        case DDISPLAY_MODE_NONE:
            DDisplay_Start();
            break;
        case DDISPLAY_MODE_DECIMAL:
        case DDISPLAY_MODE_HEXADECIMAL:
            DDisplay_SetValue(0);
            break;
        case DDISPLAY_MODE_PATTERNS: // pendiente
            break;
        default: // do nothing
            break;
            
    }
}

uint8 DDisplay_GetValue(void) {
    return _value;
}

void DDisplay_SetValue(uint8 value) {
    
    uint8 digit_left;
    uint8 digit_right;
    
    _value = value;
    
    switch(_mode) {
        case DDISPLAY_MODE_DECIMAL:
            if(value < 100) {
                // Separa el número en decenas y unidades.
                getIndexes(value, &digit_left, &digit_right);
                // Combina los patrones de 8 bits en uno de 16 y lo guarda en el estado.
                _status = (uint16)(_num_patterns[digit_left] << 8) | _num_patterns[digit_right];
                DDisplay_WriteToPorts(_status); // pasar número de 16 bits usar or para juntar los de 8 bits
            } else { // do nothing
               
            }
            break;
        case DDISPLAY_MODE_HEXADECIMAL: 
            // no se necesita un if porque todo el rango ya es 255 y siempre dará true
            // Para obtener el dígito izquierdo (nibble alto), se desplaza los bits a la derecha
            // @ejemplo recibir 156 del usuario -> 1001 1100 >> 4 -> 0000 1001 -> Obtuvimos el nibble alto
            
            digit_left = (value >> 4); 
            
            // Para el dígito derecho (nibble bajo), se usa una máscara AND con 0x0F (0000 1111)
            // Al aplicar & nos aseguramos que solo se mantengan los bits que sean 1 del nibble bajo que recibimos del usuario
            // Esto por la propiedad del and, donde ambos bits deben ser 1 para obtener un resultado verdadero.
            // @ejemplo recibir 156 del usuario -> 1001 1100 -> 1001 1100 & 0000 1111 -> 0000 1100 -> Obtuvimos el nibble bajo
            
            digit_right = value & 0x0F;
            
            /*
            *   Construye el patrón final de 16 bits para los dos displays:
            *   1. (uint16)_num_patterns[digit_left]: Convierte el patrón de 8 bits a 16 bits para evitar pérdida de datos en el desplazamiento.
            *   2. << 8: Desplaza el patrón a la parte alta del número (los 8 bits de la izquierda).
            *   3. | _num_patterns[digit_right]: Une (OR) el resultado con el patrón derecho, que ocupa la parte baja (los 8 bits de la derecha).
            *   Esto lo hacemos con el fin de tener en una variable de 16 bits los dos patrones para los displays
            */
            _status = (uint16)(_num_patterns[digit_left] << 8) | _num_patterns[digit_right]; 
            DDisplay_WriteToPorts(_status); // Función que escribirá los números a los puertos correspondientes
            break;
        default: // do nothing
            break;
    }
}

static void DDisplay_WriteToPorts(uint16 leds) {
    // Variable temporal para manjear la inversión de ánodo común si se presenta el caso
    uint16 final_leds_pattern = leds;   // Crea variable para el patrón final
    
    #if (DDISPLAY_CONFIG == 0)
        final_leds_pattern = ~leds; // Si es anodo común, mándalo negado
    #endif
    
    // Separa el patrón de 16 bits en dos de 8 bits para cada puerto
    uint8 pattern_right = (uint8)final_leds_pattern; // truncar valor para obtener lo de la derecha para las unidades
    uint8 pattern_left = (uint8)(final_leds_pattern >> 8); // mover bits a la derecha para obtener las decenas y truncarlo de nuevo
    
    // Funciones generadas por el PSoC cuando construimos el proyecto
    Display1_Pins_Write(pattern_right);
    Display2_Pins_Write(pattern_left);
}

/**
*   Separa un número (0-99) en sus dígitos de decenas y unidades.
*   @parametro number El número de entrada
*   @parametro tens Puntero donde se guardará el dígito de las decenas
*   @parametro units Puntero donde se guardará el dígito de las unidades
*/
static void getIndexes(uint8 number, uint8 *tens, uint8 *units) {
    
    *tens = 0;
    *units = 0;
   
    // Bucle de restas sucesivas, eso en algunos MCUs es más eficiente
    while(number >= 10) {
        number -= 10;
        *tens += 1;
    }
    
    // El resto es el dígito de las unidades
    *units = number;
    
}

bool DDisplay_IncrementValue(void) {
    // La lógica de esta función es determinar el nuevo valor y luego
    // delegar el trabajo a mostarlo a DDisplay_SetValue
    bool result = FALSE;
    switch(_mode) {
        case DDISPLAY_MODE_DECIMAL:
            if(_value < 99) {
                _value++;
                result = TRUE;
            }
            else if(_value == 99) { // Wrap-around (como carrusel)
                _value = 0;
                result = TRUE;
            }
            DDisplay_SetValue(_value);
            break;
        case DDISPLAY_MODE_HEXADECIMAL:
            if(_value < 255) {
                _value++;
                result = TRUE;
            }
            else if(_value == 255) { // Wrap-around
                _value = 0;
                result = TRUE;
            }
            DDisplay_SetValue(_value);
            break;
    }
    
    return result;
}

bool DDisplay_DecrementValue(void) {
    bool result = FALSE;
    switch(_mode) {
        case DDISPLAY_MODE_DECIMAL:
            if(_value > 0) {
                _value--;
                result = TRUE;
            }
            else if(_value == 0) { // Wrap-around
                _value = 99;
                result = TRUE;
            }
            DDisplay_SetValue(_value);
            break;
        case DDISPLAY_MODE_HEXADECIMAL:
            if(_value > 0) {
                _value--;
                result = TRUE;
            }
            else if(_value == 0) { // Wrap-around
                _value = 255;
                result = TRUE;
            }
            DDisplay_SetValue(_value);
            break;
    }
    
    return result;
}

void DDisplay_SetPatternsArray(const uint16* patterns, uint8 size) {
    switch(_mode) {
        case DDISPLAY_MODE_PATTERNS:
            if(patterns != NULL && size > 0) { // comprobar que no estén vacios los patrones y el tamaño sea mayor
                _patterns = patterns;
                _patterns_size = size;
                _patterns_index = 0; // Reinicia el carrusel
            }
            else {
                // Si nos pasan datos inválidos, se resetea el estado de patrones
                _patterns = NULL;
                _patterns_size = 0;
                _patterns_index = 0;
            }
            break;
        default: //do nothing
            break;
    }
}

void DDisplay_ShowPattern(uint8 index) {
    // Comprueba que todo sea válido antes de intentar acceder a la memoria del arreglo
    switch(_mode) {
        case DDISPLAY_MODE_PATTERNS:
            if(_patterns != NULL && index < _patterns_size) {
                _patterns_index = index;
                _status = _patterns[_patterns_index];
                DDisplay_WriteToPorts(_status);
            }
            break;
        default: //do nothing
            break;
    }
}

uint8 DDisplay_GetPatternIndex(void) {
    switch(_mode) {
        case DDISPLAY_MODE_PATTERNS:
            return _patterns_index;
            break;
        default: //do nothing
            break;
    }
    return 0;
}

bool DDisplay_NextPattern(void) {
    bool result = FALSE;
    switch(_mode) {
        case DDISPLAY_MODE_PATTERNS:
            if(_patterns != NULL && _patterns_size > 0) {
                _patterns_index++;
                
                if(_patterns_index >= _patterns_size) { // Wrap-around
                    _patterns_index = 0;
                }
                _status = _patterns[_patterns_index];
                DDisplay_WriteToPorts(_status); 
                result = TRUE;
            }
            break;
        default: //do nothing
            break;
    }
    return result;
}

bool DDisplay_PreviousPattern(void) {
    bool result = FALSE;
    switch(_mode) {
        case DDISPLAY_MODE_PATTERNS:
            if(_patterns != NULL && _patterns_size > 0) {
 
                if(_patterns_index == 0) { // Wrap-around
                    _patterns_index = _patterns_size - 1; 
                } else {
                    _patterns_index--;
                }
                _status = _patterns[_patterns_index];
                DDisplay_WriteToPorts(_status);
                result = TRUE;
            }
            break;
        default: //do nothing
            break;
    }
    return result;
}