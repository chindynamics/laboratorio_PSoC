#ifndef _LEDBAR_H_
#define _LEDBAR_H_

#include "cytypes.h"
#include "bool.h"

// REQUISITOS DE IMPLEMENTACIÓN:
// - Utilizar dos puertos de 5 bits para los 10 leds (o dos de 6 en caso de 12 leds)
// - No utilizar tabla (arreglo) de constantes, los patrones deben ser calculados en
//   tiempo de ejecución

// MODO "LEVEL":
//      Para el nivel n, se encuentran encendidos los leds 1 hasta el n.
//      Para el nivel 0 todos los leds se encuentran apagados
// MODO "BAR":
//      Para el nivel n, se encuentra encendido sólo el led n.
//      Para el nivel 0 todos los leds se encuentran apagados
// MODO "PATTERNS":
//      El usuario decide el patrón de leds a utilizar proporcionando
//      un arreglo externo
#define LEDBAR_MODE_NONE        0
#define LEDBAR_MODE_LEVEL       1
#define LEDBAR_MODE_BAR         2
#define LEDBAR_MODE_PATTERNS    3

#define LEDBAR_LED_NONE     0x0000
#define LEDBAR_LED_1        0x0001
#define LEDBAR_LED_2        0x0002
#define LEDBAR_LED_3        0x0004
#define LEDBAR_LED_4        0x0008
#define LEDBAR_LED_5        0x0010
#define LEDBAR_LED_6        0x0020
#define LEDBAR_LED_7        0x0040
#define LEDBAR_LED_8        0x0080
#define LEDBAR_LED_9        0x0100
#define LEDBAR_LED_10       0x0200
#define LEDBAR_LED_ALL      0x03FF

#define LEDBAR_NUM_LEDS     10

// Inicializa el componente
void LedBar_Start(void);

// Establece el modo actual de la barra de leds
// El cambio de modo reinicia el componente
void LedBar_SetMode(uint8 mode);
// Devuelve el modo actual de la barra de leds
uint8 LedBar_GetMode(void);

// ** Las siguientes funciones sólo operan en los modos "LEVEL" y "BAR"
// Establece el nivel de la barra de leds
void LedBar_SetLevel(uint8 value);
// Devuelve el nivel de la barra de leds
uint8 LedBar_GetLevel(void);
// Aumenta en uno el nivel actual de la barra de leds
// Devuelve "true" si fue posible incrementar el nivel, "false" en caso contrario
bool LedBar_IncrementLevel(void);
// Reduce en uno el nivel actual de la barra de leds
// Devuelve "true" si fue posible decrementar el nivel, "false" en caso contrario
bool LedBar_DecrementLevel(void);

// Devuelve "true" si la barra de leds está llena (nivel máximo),
// "false" en caso contrario
bool LedBar_IsFull(void);
// Devuelve "true" si la barra de leds está vacía (nivel 0),
// "false" en caso contrario
bool LedBar_IsEmpty(void);

// ** Las siguientes funciones sólo operan en el modo "PATTERNS"
// Establece el arreglo externo de patrones a utilizar
void LedBar_SetPatternArray(const uint16* patterns, uint8 size);
// Muestra el siguiente patrón en la barra de leds
// El máximo índice para avanzar es size-1
// Devuelve "true" si fue posible avanzar al siguiente patrón,
// "false" en caso contrario
bool LedBar_NextPattern(void);
// Muestra el patrón previo en la barra de leds
// El mínimo índice para retroceder es 0
// Devuelve "true" si fue posible retroceder al patrón previo,
// "false" en caso contrario
bool LedBar_PreviousPattern(void);
// Establece el índice del patrón a mostrar en la barra de leds
// El rango válido de índices es de 0 a size-1
void LedBar_SetPatternIndex(uint8 index);
// Devuele el índice actual del patrón presente en la barra de leds
uint8 LedBar_GetPatternIndex(void);

#endif // _LEDBAR_H_
