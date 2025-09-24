/**
*   Librería que permite manejar dos displays de 7 segmentos como una sola unidad con soporte
*   para modos decimal (0-99), hexadecimal (0-255) y una secuencia de patrones personalizados de 16 bits.
*/

#ifndef _DDISPLAY_H_
#define _DDISPLAY_H_

#include <cytypes.h>
#include <bool.h>
    
/**
*   Define el tipo de display conectado
*   para un display Ánodo Común (los segmentos se encienden con 0) colocar un 0
*   para un display Cátodo Común (los segmentos se encuenden con 1) colocar un 1
*/

#define DDISPLAY_CONFIG 1

// DISPLAY DERECHO PARA UNIDADES
#define DDISPLAY_SEGMENT_A_R       0x0040
#define DDISPLAY_SEGMENT_B_R       0x0020
#define DDISPLAY_SEGMENT_C_R       0x0010
#define DDISPLAY_SEGMENT_D_R       0x0008
#define DDISPLAY_SEGMENT_E_R       0x0004
#define DDISPLAY_SEGMENT_F_R       0x0002
#define DDISPLAY_SEGMENT_G_R       0x0001
#define DDISPLAY_SEGMENT_ALL_R     0x007F
    
// DISPLAY IZQUIERDO PARA DECENAS
#define DDISPLAY_SEGMENT_A_L       0x0040 
#define DDISPLAY_SEGMENT_B_L       0x0020 
#define DDISPLAY_SEGMENT_C_L       0x0010 
#define DDISPLAY_SEGMENT_D_L       0x0008 
#define DDISPLAY_SEGMENT_E_L       0x0004 
#define DDISPLAY_SEGMENT_F_L       0x0002 
#define DDISPLAY_SEGMENT_G_L       0x0001 
#define DDISPLAY_SEGMENT_ALL_L     0x007F 
    
// AMBOS DISPLAYS
#define DDISPLAY_SEGMENT_NONE       0x0000
#define DDISPLAY_ALL                (DDISPLAY_ALL_L | DISPLAY_ALL_R)
    
// PATRONES PREDEFINIDOS PARA DÍGITOS (8 bits)
#define DDISPLAY_0   0x7E
#define DDISPLAY_1   0x30
#define DDISPLAY_2   0x6D
#define DDISPLAY_3   0x79
#define DDISPLAY_4   0x33
#define DDISPLAY_5   0x5B
#define DDISPLAY_6   0x5F
#define DDISPLAY_7   0x70
#define DDISPLAY_8   0x7F
#define DDISPLAY_9   0x7B
#define DDISPLAY_A   0x77
#define DDISPLAY_B   0x1F
#define DDISPLAY_C   0x0D
#define DDISPLAY_D   0x3D
#define DDISPLAY_E   0x4F
#define DDISPLAY_F   0x47

// MODOS DE OPERACIÓN
#define DDISPLAY_MODE_NONE           0
#define DDISPLAY_MODE_DECIMAL        1
#define DDISPLAY_MODE_HEXADECIMAL    2
#define DDISPLAY_MODE_PATTERNS       3
    
// FUNCIONES

/**
*   Inicializa la librería y apaga los displays
*   igualmente puede ser usada como un reinicio del display.
*   Esta función debe ser la primera en ser llamada
*/
       
void DDisplay_Start(void);

/**
*   Obtiene el modo de operación actual.
*   @ejemplo return El modo actual (DDISPLAY_MODE_...)
*/

uint8 DDisplay_GetMode(void);

/**
*   Establece el modo de operación de la librería
*   El nuevo modo a establecer (DDISPLAY_MODE_...)
*/

void DDisplay_SetMode(uint8 mode);

/**
*   Obtiene el valor mostrado actual.
*   Esta función solo funciona en modo decimal-hexadecimal.
*   @ejemplo return El valor actual mostrado
*/

uint8 DDisplay_GetValue(void);

/**
*   Muestra un valor númerico en los displays
*   El comportamiento depende del modo actual (Decimal o Hexadecimal).
*   @ejemplo value El número a mostrar (0-99 para decimal, 0-255 para hexadecimal)
*/

void DDisplay_SetValue(uint8 value);

/**
*   Incrementa el valor númerico actual en 1 y actualiza el display.
*   Si llega al límite (99 o 255), da la vuelta a 0.
*   @ejemplo return TRUE si el incremento fue exitoso, FALSE si no está en un modo numérico
*/

bool DDisplay_IncrementValue(void);

/**
*   Decrementa el valor numérico actual en 1 y actualiza el display.
*   Si llega a 0, da la vuelta al límite (99 o 255).
*   @ejemplo return TRUE si el decremento fue exitoso, FALSE si no está en un modo numérico
*/

bool DDisplay_DecrementValue(void);

/**
*   Configura el arreglo de patrones personalizados para el modo PATTERNS.
*   @ejemplo patterns Puntero a un arreglo de patrones de 16 bits.
*   @ejemplo size El número de elementos en el arreglo de patrones.
*/

// Patterns mode, PENDIENTE => 16 bits
void DDisplay_SetPatternsArray(const uint16* patterns, uint8 size);

/**
*   Muestra un patrón específico del arreglo configurado.
*   @ejemplo index El índice del patrón a mostar (comenzando en 0).
*/

void DDisplay_ShowPattern(uint8 index);

/**
*   Obtiene el índice del patrón que se está mostrando actualmente.
*   @ejemplo return El índice del patrón actual.
*/

uint8 DDisplay_GetPatternIndex(void);

/**
*   Muestra el siguiente patrón del arreglo. Vuelve al inicio si llega al final
*   @ejemplo return TRUE si fue exitoso, FALSE si no está en modo patrones.
*/

bool DDisplay_NextPattern(void);

/**
*   Muestra el patrón anterior del arreglo. Salta al final si está en el inicio
*   @ejemplo return TRUE si fue exitoso, FALSE si no está en modo patrones.
*/

bool DDisplay_PreviousPattern(void);


#endif // _DDISPLAY_H_
