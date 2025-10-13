#include "LedBar.h"
#include "project.h"

/* VARIABLES DE ESTADO INTERNAS (OCULTAS AL USUARIO)*/

// Variables para el estado general y los modos numéricos
static uint8 _mode = LEDBAR_MODE_NONE;      // Guarda el modo de operación actual
static uint16 _status = LEDBAR_LED_NONE;    // El último nivel en bits mandado
static uint8 _value = 0;                    // El valor en decimal de nivel de leds

// Variables de estado específicas para el modo patrones
static const uint16* _patterns = NULL;
static uint8 _patterns_size = 0;
static uint8 _patterns_index = 0;

static void LedBar_WriteToPorts(uint16 leds);

void LedBar_WriteToPorts(uint16 leds) {
    
    
    uint8 firstLeds = (uint8)(leds & 0x1F);
    uint8 secondLeds = (uint8)(leds >> 5);
    
    LedsFirst_Write(firstLeds);
    LedsSecond_Write(secondLeds);
}

void LedBar_Start(void) {
    _mode = LEDBAR_MODE_NONE;
    _value = 0;
    _status = LEDBAR_LED_NONE;
    _patterns = NULL;
    _patterns_size = 0;
    _patterns_index = 0;
    LedBar_WriteToPorts(_status);
}

void LedBar_SetMode(uint8 mode) {
    switch(mode) {
        case LEDBAR_MODE_NONE:
            LedBar_Start();
            break;
        case LEDBAR_MODE_LEVEL:
        case LEDBAR_MODE_BAR:
            _value = 0;
            _mode = mode;                   // Parpadear el nivel 2 para demostar que se seleccionó el modo bar
            _status = LEDBAR_LED_NONE;
            LedBar_WriteToPorts(_status);
            break;
        case LEDBAR_MODE_PATTERNS:          // Pendiente
            _mode = mode;
            _patterns = NULL;
            _patterns_size = 0;
            _patterns_index = 0;
            LedBar_WriteToPorts(LEDBAR_LED_NONE);
            break;
        default:
            _mode = LEDBAR_MODE_NONE;
            break;
    }
    
}

uint8 LedBar_GetMode(void) {
    return _mode;
}

void LedBar_SetLevel(uint8 value) {
    
    switch(_mode) {
        case LEDBAR_MODE_BAR:
            if(value == 0) {
                _value = 0;
                _status = LEDBAR_LED_NONE;
                LedBar_WriteToPorts(_status);
            }
            else if(value <= LEDBAR_NUM_LEDS) {
                _value = value;
                uint8 max = value - 1;
                _status = (uint16)(1 << max);
                LedBar_WriteToPorts(_status);
            }
            break;
        case LEDBAR_MODE_LEVEL:
            if(value == 0) {
                _value = 0;
                _status = LEDBAR_LED_NONE;
                LedBar_WriteToPorts(_status);
            }
            else if(value <= LEDBAR_NUM_LEDS) {
                _value = value;
                _status = (uint16)((1 << value) - 1);
                LedBar_WriteToPorts(_status);
            }
            break;
        default:
            break;
    }
    
}

uint8 LedBar_GetLevel(void) {
    return _value;
}

bool LedBar_IncrementLevel(void) {
    bool result = FALSE;
    switch(_mode) {
        case LEDBAR_MODE_BAR:
            if(_value < LEDBAR_NUM_LEDS) {
                _value++;
                LedBar_SetLevel(_value);
                result = TRUE;
            }
            break;
        case LEDBAR_MODE_LEVEL:
            if(_value < LEDBAR_NUM_LEDS) {
                result = TRUE;
                _value++;
                LedBar_SetLevel(_value);
            }
            break;
        default: // do nothing
            break;
    }
    return result;
}

bool LedBar_DecrementLevel(void) {
    bool result = FALSE;
    switch(_mode) {
        case LEDBAR_MODE_BAR:
            if(_value > 0) {
                _value--;
                LedBar_SetLevel(_value);
                result = TRUE;
            }
            break;
        case LEDBAR_MODE_LEVEL:
            if(_value > 0) {
                _value--;
                LedBar_SetLevel(_value);
                result = TRUE;
            }
            break;
        default: // do nothing
            break;
    }
    return result;
}

bool LedBar_IsFull(void) {
    return(_value >= LEDBAR_NUM_LEDS);
}

bool LedBar_IsEmpty(void) {
    return(_value == 0);
}

void LedBar_SetPatternArray(const uint16* patterns, uint8 size) {
    switch(_mode) {
        case LEDBAR_MODE_PATTERNS:
            if(patterns != NULL && size > 0) {
                _patterns = patterns;
                _patterns_size = size;
                _patterns_index = 0; 
            }
            else {
                _patterns = NULL;
                _patterns_size = 0;
                _patterns_index = 0;
            }
            break;
        default:
            break;
    }
}

void LedBar_SetPatternIndex(uint8 index) {
    switch(_mode) {
        case LEDBAR_MODE_PATTERNS:
            if(_patterns != NULL && index < _patterns_size) {
                _patterns_index = index;
                _status = _patterns[_patterns_index];
                LedBar_WriteToPorts(_status);
            }
            break;
        default:
            break;
    }
}

uint8 LedBar_GetPatternIndex(void) {
    if(_mode == LEDBAR_MODE_PATTERNS) {
        return _patterns_index;
    }
    return 0;
}

bool LedBar_NextPattern(void) {
    bool result = FALSE;
    switch(_mode) {
        case LEDBAR_MODE_PATTERNS:
            if(_patterns != NULL && _patterns_size > 0) {
                
                if(_patterns_index < _patterns_size - 1) {
                    _patterns_index++;
                    LedBar_SetPatternIndex(_patterns_index);
                    result = TRUE;
                } 
            }
            break;
        default:
            break;
    }
    return result;
}

bool LedBar_PreviousPattern(void) {
    bool result = FALSE;
    switch(_mode) {
        case LEDBAR_MODE_PATTERNS:
            if(_patterns != NULL && _patterns_size > 0) {
                _patterns_index--;
                LedBar_SetPatternIndex(_patterns_index);
                result = TRUE;
            }
            
            break;
        default:
            break;
    }
    return result;
}
