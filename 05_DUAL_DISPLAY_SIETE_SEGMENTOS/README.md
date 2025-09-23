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

