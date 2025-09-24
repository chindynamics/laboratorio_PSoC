# 05 - Librería para Display Dual de 7 Segmentos

Este proyecto contiene una librería en C (`DDisplay`) desarrollada desde cero para controlar dos displays de 7 segmentos en un microcontrolador PSoC. El objetivo es crear un driver modular, reutilizable y fácil de usar que encapsule la complejidad del hardware.

La librería convierte un número de 8 bits en su representación de dos dígitos, ya sea en formato decimal o hexadecimal, y también permite mostrar secuencias de patrones personalizados por el usuario.

## Características principales
- **Control Dual Unificado:** Maneja dos displays de 7 segmentos como una sola unidad a través de una interfaz de 16 bits.
- **Modo Decimal:** Capaz de mostrar cualquier número entre 0 y 99.
- **Modo Hexadecimal:** Capaz de mostrar cualquier valor, desde `00` hasta `FF` (0-255).
- **Modo de Patrones:** Permite mostrar secuencias de "dibujos" o símbolos personalizados de 16 bits definidos por el usuario.
- **Funciones de Navegación:** Incluye funciones como `IncrementValue()`, `DecrementValue()`, `NextPattern()` y `PreviousPattern()` para una fácil interacción sin necesidad de manejar contadores en el programa principal.
- **Configurable:** Soporta tanto displays de **ánodo común** como de **cátodo común** a través de una sola macro (`DDISPLAY_CONFIG`) en el archivo `.h`.

## Conexión física

En este ejemplo, trabajamos con dos displays de siete segmentos de cátodo común. Lo que quiere decir que requiere un 1 (o 5 volts) para prender. A diferencia de un ánodo común donde necesita un 0 (o 0 volts) para prender. Sigue el siguiente diagrama de conexión. El diagrama no cambia mucho con un ánodo común, simplemente en vez de conectar tierra (VSS) conectarás voltaje (VCC).

**DIAGRAMA DEL CIRCUITO:**
![Diagrama de conexión del PSoC a dos displays de 7 segmentos de cátodo común](./img/diagrama.png)

## Configuración de Pines
Crea dos pines de salida digitales de 7 pines cada uno. Recuerda colocarles strong drive (switch de 0 a 5V), posterior a esto, dependiendo de si tu display es Cátodo Común o Ánodo Común, deberás elegir su estado inicial como 0 o 1 respectivamente.

**CAPTURA DE LA CONFIGURACIÓN DE PINES:**
![Captura de pantalla de la configuración de pines en PSoC Creator para cátodo común](./img/pines.png)

## Configuración de puertos
Para configurar los puertos de los pines creados anteriormente, es necesario abrir el apartado de Pines en el apartado de Project -> Design Wide Resources -> Pins. En este apartado, debes de colocar a que puertos del PSoC quieres que correspondan los pines. En este caso, debes de colocar los puertos de tal manera que en el código cuando escribas a los puertos del Display de la izquierda estos correspondan a las decenas y el display de la derecha corersponda a las unidades. Con esta configuración, entonces deberías de ser capaz de observar el modo decimal funcionando correctamente, no olvides presionar el botón de (`Build`) después de realizar estos cambios.

**Un error común es invertir los puertos y probar el modo decimal y ver que el display de la izquierda muestra las unidades y el de la derecha las decenas, para corregir esto simplemente invierte los puertos de lugar, es decir que si tenias el display uno al P0 y el display dos al P2, cambiarás el P0 al P2 y el P2 al P0.**

**DIAGRAMA DE PUERTOS:**
![Captura de pantalla de la configuración de puertos](./img/puertos.png)

## Programar el microcontrolador
Para probar este proyecto en tu propia tarjeta PSoC, sigue estos pasos.

1.  **Obtén los Archivos de la Librería:** Clona o descarga este repositorio y localiza los siguientes archivos dentro de la carpeta `05_DUAL_DISPLAY_SIETE_SEGMENTOS/`:
    * `DDisplay.h`
    * `DDisplay.c`
    * `bool.h`
    * `main.c` (para usarlo como ejemplo)

2.  **Configura tu Proyecto PSoC:**
    * Crea un nuevo proyecto vacío en PSoC Creator.
    * Sigue las instrucciones de **"Configuración de Pines"** y **"Configuración de Puertos"** de arriba para añadir y nombrar los pines de salida para tus displays.

3.  **Añade los Archivos de la Librería:**
    * **Copia** los archivos `DDisplay.h`, `DDisplay.c` y `bool.h` a la carpeta de tu nuevo proyecto en tu computadora.
    * En PSoC Creator, en el **"Workspace Explorer"**:
        * Haz clic derecho en **"Header Files"** -> **"Add"** -> **"Existing Item..."** y selecciona `DDisplay.h` y `bool.h`.
        * Haz clic derecho en **"Source Files"** -> **"Add"** -> **"Existing Item..."** y selecciona `DDisplay.c`.

4.  **Añade el Código Principal:**
    * Abre el archivo `main.c` de tu nuevo proyecto.
    * Copia y pega el contenido del `main.c` de este repositorio en tu propio `main.c`.

5.  **Construye y Programa:** Presiona **Build** y luego **Program** en PSoC Creator. ¡Tu display debería funcionar!

## Aclaraciones técnicas

**SEGMENTOS A, B, C, D, ...**
En (`DDisplay.h`), se definen varias constantes con valor hexadecimal. Estas constantes son máscaras de bits. Cada una representa un único "interruptor" encendido en un número de 8 bits, que corresponde a un pin físico de tu PSoC. Cada uno de los 8 pines de tu puerto corresponden a una especie de interruptor, donde la relación está de la siguiente manera:

| Pin del puerto | Bit encendido | Valor hexadecimal | Constante asignada | Segmento del display |
| -------------- | ------------- | ----------------- | ------------------ | -------------------- |
| Pin 0          | 0000 0001     | 0x01              | DDISPLAY_SEGMENT_G_R | G                  |
| Pin 1	         | 0000 0010	   | 0x02              | DDISPLAY_SEGMENT_F_R	| F                  |
| Pin 2	         | 0000 0100	   | 0x04	             | DDISPLAY_SEGMENT_E_R	| E                  |
| Pin 3	         | 0000 1000	   | 0x08	             | DDISPLAY_SEGMENT_D_R	| D                  |
| Pin 4	         | 0001 0000	   | 0x10	             | DDISPLAY_SEGMENT_C_R	| C                  |
| Pin 5	         | 0010 0000	   | 0x20	             | DDISPLAY_SEGMENT_B_R	| B                  |
| Pin 6	         | 0100 0000	   | 0x40	             | DDISPLAY_SEGMENT_A_R	| A                  |

Entonces (`DDISPLAY_SEGMENT_A_R (0x40)`) es simplemente el número que se necesita para encender únicamente el pin 6 (y por lo tanto, el segmento A y mantener todos los demás apagados, podemos notar como no usamos en ningún momento el número tres (0000 0011) pues esto encendería el segmento G y F. Esta misma tabla aplica para los segmentos del lado izquierdo, para el ejemplo se usaron los de la derecha pero es exactamente igual.

**SEGMENTOS 0, 1, 2, 3, ...**

Ahora, podemos observar en el código que existen patrones numéricos como (`DDISPLAY_0`). Estos valores son simplemente combinaciones pre-calculadas de las máscaras de segmentos de arriba. Se crean uniendo con el operador OR (|) todos los segmentos necesarios para formar un carácter.

Por ejemplo, para formar el número *0*:
1. Para dibujar el 0, necesitas encender los segmentos A, B, C, D, E y F.
2. Para encenderlos puedes aplicar una operación OR de los segmentos definidos anteriormente (más sencillo) o el enfoque en el código, el cuál es precalcular los patrones.
3. Para encender el 0 entonces necesitarías tener en binario `0111 1110` lo cuál en hexadecimal es representado como `0x7E`.

Es importante conocer como funciona los dígitos hexadecimal para entender la relación hexadecimal-binario, pero el principio básico es que cada dígito hexadeciaml corresponde a 4 bits. Por lo tanto `0x7E` corresponde a un valor de 8 bits porque tiene dos dígitos hexadecimal. El 7 viene de los 4 bits más significativoso el nibble alto en binario (`0111`), lo cuál es 7, mientrás que el dígito E (14) viene de los 4 bits menos significativos o el nibble bajo en binario `1110`, el cuál es 14.

Estas constantes se definen para cada uno de los números hexadecimales (0-F). Esto es usado para el modo decimal y hexadecimal, donde el rango de nuestro display en decimal es de 0-9 en UN display y 0-F en UN display en modo hexadecimal.

## Preguntas frecuentes.

1.- ¿Por qué la función getIndexes usa punteros y un bucle de restas?
La función `getIndexes` necesita calcular dos valores (decenas y unidades) y devolverlos. Dado que una función en C solo puede usar `return` para un único valor, se recurre a los punteros para solucionar este problema. Esta técnica se conoce como paso por referencia. En lugar de pasar una copia de las variables, se pasa su dirección de memoria, como si se entregara la dirección de una casa en lugar de una foto de ella. De esta manera, `getIndexes` puede usar esas direcciones para modificar directamente las variables originales tens y units que existen en la función `DDisplay_SetValue`.

En cuanto al método de cálculo, se utiliza un bucle con restas sucesivas porque es una técnica clásica de sistemas embebidos, muy eficiente en microcontroladores simples que podrían no tener hardware dedicado para la división. Existen otras dos alternativas comunes: el uso de división y módulo (`/` y `%`), que es el método más legible y muy rápido en microcontroladores actuales, la otra alternativa es el uso de una **tabla de búsqueda (LUT, Lookup Table)**, que es el método más rápido posible en ejecución a costa de usar más memoria de programa. La implementación actual con el bucle es un sólido punto intermedio entre velocidad y uso de memoria, aunque sería más útil utilizar módulo y división en el PSoC, recientemente he aprendido a programar en ensamblador y a veces las ideas se revuelven.



