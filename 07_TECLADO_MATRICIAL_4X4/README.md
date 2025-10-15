# RESUMEN DE LA PRÁCTICA

El objetivo de esta práctica es desarrollar un sistema embebido capaz de leer e interpretar las pulsaciones de un teclado matricial 4x4 y mostrar el carácter correspondiente en un display de 7 segmentos. La lógica de control se implementará en un microcontrolador PSoC, reutilizando una librería previamente desarrollada para el manejo del display.

# FUNDAMENTO TÉCNICO DEL TECLADO MATRICIAL

Un teclado matricial 4x4 consiste en 16 interruptores de pulsador momentáneo organizados en una matriz de 4 filas y 4 columnas. En lugar de requerir 16 pines dedicados, esta topología reduce el requisito a solo 8 pines (4 para filas y 4 para columnas). Internamente, cada interruptor se encuentra en la intersección de una línea de fila y una de columna. En su estado de reposo, todos los interruptores están en un circuito abierto, impidiendo el flujo de corriente entre filas y columnas. Al presionar un botón, se cierra el circuito en esa intersección específica, creando una conexión eléctrica directa entre su fila y columna correspondiente.
