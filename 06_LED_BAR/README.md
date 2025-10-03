# Guía de Uso y Referencia de la API 'LedBar'

Este apartado describe la interfaz de programación (API) para la librería 'LedBar'. Cada función pública está detallada con su propósito, parámetros, valor de retorno y un ejemplo de su aplicación práctica.

## Funciones Generales y de Configuración

Estas son las funciones básicas para inicializar y configurar el estado general de la librería.

---
#### ### `void LedBar_Start(void);`
Inicializa la librería a su estado por defecto. Resetea el modo a `NONE`, el nivel a `0` y la configuración de patrones, y apaga todos los LEDs.

* **Uso Típico:** Se llama una sola vez al principio del programa (`main.c`) para asegurar que la librería y los LEDs comiencen en un estado limpio y conocido.

---
#### ### `void LedBar_SetMode(uint8 mode);`
Establece el modo de operación de la barra de LEDs, cambiando su comportamiento fundamental. Al cambiar de modo, el estado interno (nivel o índice de patrón) se reinicia a `0`.

* **`@param mode`**: El modo de operación deseado. Debe ser uno de los siguientes:
    * `LEDBAR_MODE_NONE`
    * `LEDBAR_MODE_LEVEL`
    * `LEDBAR_MODE_BAR`
    * `LEDBAR_MODE_PATTERNS`
* **Uso Típico:** Se utiliza para cambiar entre las diferentes visualizaciones. Por ejemplo, `LedBar_SetMode(LEDBAR_MODE_LEVEL)` para que la barra actúe como un medidor de nivel, o `LedBar_SetMode(LEDBAR_MODE_PATTERNS)` para mostrar una animación personalizada.

---
#### ### `uint8 LedBar_GetMode(void);`
Devuelve el modo de operación actual de la librería.

* **`@return`**: El valor del modo actual (ej. `LEDBAR_MODE_LEVEL`).
* **Uso Típico:** Útil para que el programa principal tome decisiones. `if (LedBar_GetMode() == LEDBAR_MODE_BAR) { // Hacer algo específico si estamos en modo BAR }`.

---
### Funciones para Modos `LEVEL` y `BAR`

Este conjunto de funciones permite usar la barra de LEDs como un visualizador numérico. Son ideales para aplicaciones como un vúmetro de audio, un medidor de batería, un tacómetro o un indicador de volumen.

---
#### ### `void LedBar_SetLevel(uint8 value);`
Establece el nivel de la barra de LEDs. El patrón de LEDs correspondiente se calcula en tiempo de ejecución y se muestra inmediatamente.

* **`@param value`**: El nivel a mostrar, en un rango de **0 a 10**. Si *`value`* es `0`, todos los LEDs se apagan. Si es mayor a 10, se limita a 10.
* **Uso Típico:** Para representar visualmente el valor de un sensor. Si un sensor de temperatura devuelve un valor de `7` en una escala de 10, se llama a `LedBar_SetLevel(7)`. En modo `LEVEL` se encenderán 7 LEDs; en modo `BAR`, solo el séptimo.

---
#### ### `uint8 LedBar_GetLevel(void);`
Devuelve el nivel numérico actual de la barra.

* **`@return`**: El nivel actual (de 0 a 10).
* **Uso Típico:** Para leer el estado actual de la barra y guardarlo o tomar decisiones. `uint8 nivel_actual = LedBar_GetLevel();`.

---
#### ### `bool LedBar_IncrementLevel(void);` y `bool LedBar_DecrementLevel(void);`
Incrementan o decrementan el nivel actual en 1 y actualizan el display. Estas funciones no dan la vuelta (se detienen en los límites 0 y 10).

* **`@return`**: `TRUE` si fue posible cambiar el nivel. `FALSE` si ya estaba en el límite (0 o 10).
* **Uso Típico:** Perfectas para responder a la pulsación de botones. Si un usuario presiona un botón de "subir volumen", se llama a `LedBar_IncrementLevel()`. El valor de retorno `FALSE` es útil para saber cuándo se ha llegado al límite.

---
#### ### `bool LedBar_IsFull(void);` y `bool LedBar_IsEmpty(void);`
Comprueban si la barra de LEDs está en su nivel máximo (10) o mínimo (0).

* **`@return`**: `TRUE` o `FALSE` según el estado.
* **Uso Típico:** Para tomar decisiones rápidas sin necesidad de obtener el valor numérico. `if (LedBar_IsFull()) { // Activar una alarma de sobrecarga }` o `if (LedBar_IsEmpty()) { // Indicar que la batería está agotada }`.

---
### Funciones para Modo `PATTERNS`

Este modo ofrece total libertad creativa, permitiendo al usuario definir y mostrar secuencias de "dibujos" de 16 bits. Es ideal para animaciones, secuencias de diagnóstico o indicadores de estado personalizados.

---
#### ### `void LedBar_SetPatternArray(const uint16* patterns, uint8 size);`
Configura la librería con un "álbum de fotos" (un arreglo de patrones) definido por el usuario.

* **`@param patterns`**: Un puntero a un arreglo de patrones de 16 bits (`uint16`).
* **`@param size`**: El número de elementos que contiene el arreglo *`patterns`*.
* **Uso Típico:** Se llama una vez después de `SetMode` para cargar una secuencia de animaciones que se ha definido previamente en `main.c`, como un efecto de "carga" o una secuencia de luces de error.

---
#### ### `void LedBar_SetPatternIndex(uint8 index);`
Muestra un patrón específico del arreglo, identificado por su índice.

* **`@param index`**: El índice del patrón a mostrar (de `0` a `size - 1`).
* **Uso Típico:** Para saltar a un indicador de estado específico. Por ejemplo, en un dispositivo, `LedBar_SetPatternIndex(0)` podría mostrar un patrón de "OK" y `LedBar_SetPatternIndex(1)` podría mostrar un patrón de "Error".

---
#### ### `uint8 LedBar_GetPatternIndex(void);`
Devuelve el índice del patrón que se está mostrando actualmente.

* **`@return`**: El índice actual del carrusel de patrones.
* **Uso Típico:** Para saber en qué cuadro de una animación se encuentra actualmente el sistema y guardar su estado.

---
#### ### `bool LedBar_NextPattern(void);` y `bool LedBar_PreviousPattern(void);`
Avanzan o retroceden al siguiente patrón en el arreglo y lo muestran. No dan la vuelta.

* **`@return`**: `TRUE` si fue posible moverse. `FALSE` si ya estaba en el primer o último patrón.
* **Uso Típico:** Se usan dentro de un bucle `while` en `main.c` para recorrer una animación. Por ejemplo, `while(LedBar_NextPattern()) { CyDelay(100); }` reproduciría una secuencia de inicio una sola vez.
