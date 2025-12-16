#include "project.h"
#include "LedMatrix.h"

// carita feliz
const uint8 pattern_smile[8] = {
    0b00111100, // Fila 0 (0x3C)
    0b01000010, // Fila 1 (0x42)
    0b10100101, // Fila 2 (0xA5)
    0b10000001, // Fila 3 (0x81)
    0b10100101, // Fila 4 (0xA5)
    0b10011001, // Fila 5 (0x99)
    0b01000010, // Fila 6 (0x42)
    0b00111100  // Fila 7 (0x3C)
};

// un marco
const uint8 pattern_frame[8] = {
    0b11111111, // Fila 0 (0xFF)
    0b10000001, // Fila 1 (0x81)
    0b10000001, // Fila 2 (0x81)
    0b10000001, // Fila 3 (0x81)
    0b10000001, // Fila 4 (0x81)
    0b10000001, // Fila 5 (0x81)
    0b10000001, // Fila 6 (0x81)
    0b11111111  // Fila 7 (0xFF)
};

const uint8 animation[6][8] = {
    { 
        0b01111111, // 0x7F
        0b00000001, // 0x01
        0b00000001, // 0x01
        0b01111111, // 0x7F
        0b00000001, // 0x01
        0b00000001, // 0x01
        0b01111111, // 0x7F
        0b00000000  // 0x00
    },
    { 
        0b00111111, // 0x3F
        0b01100001, // 0x61
        0b01100001, // 0x61
        0b01100001, // 0x61
        0b01100001, // 0x61
        0b01100001, // 0x61
        0b00111111, // 0x3F
        0b00000000  // 0x00
    },
    {
        0b01111110, // 0x7E
        0b00000001, // 0x01
        0b00000001, // 0x01
        0b01111110, // 0x7E
        0b01000000, // 0x40
        0b01000000, // 0x40
        0b01111111, // 0x7F
        0b00000000  // 0x00
    },
    { 
        0b00111110, // 0x3E
        0b01000001, // 0x41
        0b01000001, // 0x41
        0b01000001, // 0x41
        0b01000001, // 0x41
        0b01000001, // 0x41
        0b00111110, // 0x3E
        0b00000000  // 0x00
    },
    { 
        0b01100001, // 0x61
        0b01100011, // 0x63
        0b01100101, // 0x65
        0b01101001, // 0x69
        0b01110001, // 0x71
        0b01100001, // 0x61
        0b01100001, // 0x61
        0b00000000  // 0x00
    },
    {
        0b00000000, // 0x00
        0b01100110, // 0x66
        0b11111111, // 0xFF 
        0b11111111, // 0xFF
        0b01111110, // 0x7E
        0b00111100, // 0x3C
        0b00011000, // 0x18
        0b00000000  // 0x00
    }
};

int main(void)
{
    CyGlobalIntEnable; 
    
    LedMatrix_Start();                      // iniciar libreria
    LedMatrix_SetMode(LEDMATRIX_MODE_LED);  
    
    CyDelay(1000);
    
    //-------------------------------------PRUEBA 1: MODO LED---------------------------------------
    
    // velita
    LedMatrix_SetLed(3, 1, TRUE);
    LedMatrix_SetLed(3, 2, TRUE);
    LedMatrix_SetLed(3, 3, TRUE);
    LedMatrix_SetLed(3, 4, TRUE);
    LedMatrix_SetLed(4, 2, TRUE);
    LedMatrix_SetLed(5, 3, TRUE);
    LedMatrix_SetLed(4, 3, TRUE);
    
    // El casco del barco
    LedMatrix_SetLed(0, 5, TRUE);
    LedMatrix_SetLed(1, 5, TRUE);
    LedMatrix_SetLed(2, 5, TRUE);
    LedMatrix_SetLed(3, 5, TRUE);
    LedMatrix_SetLed(4, 5, TRUE);
    LedMatrix_SetLed(5, 5, TRUE);
    LedMatrix_SetLed(6, 5, TRUE);
    
    LedMatrix_SetLed(1, 6, TRUE);
    LedMatrix_SetLed(2, 6, TRUE);
    LedMatrix_SetLed(3, 6, TRUE);
    LedMatrix_SetLed(4, 6, TRUE);
    LedMatrix_SetLed(5, 6, TRUE);
    
    CyDelay(3000); // esperar 3 segundos y apagar dibujo
    
    // velita
    LedMatrix_SetLed(3, 1, FALSE);
    LedMatrix_SetLed(3, 2, FALSE);
    LedMatrix_SetLed(3, 3, FALSE);
    LedMatrix_SetLed(3, 4, FALSE);
    LedMatrix_SetLed(4, 2, FALSE);
    LedMatrix_SetLed(5, 3, FALSE);
    LedMatrix_SetLed(4, 3, FALSE);
                         
    // El casco del barco
    LedMatrix_SetLed(0, 5, FALSE);
    LedMatrix_SetLed(1, 5, FALSE);
    LedMatrix_SetLed(2, 5, FALSE);
    LedMatrix_SetLed(3, 5, FALSE);
    LedMatrix_SetLed(4, 5, FALSE);
    LedMatrix_SetLed(5, 5, FALSE);
    LedMatrix_SetLed(6, 5, FALSE);
                          
    LedMatrix_SetLed(1, 6, FALSE);
    LedMatrix_SetLed(2, 6, FALSE);
    LedMatrix_SetLed(3, 6, FALSE);
    LedMatrix_SetLed(4, 6, FALSE);
    LedMatrix_SetLed(5, 6, FALSE);
    
    CyDelay(1000);
    
    //-------------------------------------PRUEBA 2: MODO SINGLE---------------------------------------
    
    LedMatrix_SetMode(LEDMATRIX_MODE_SINGLE);
    LedMatrix_SetSinglePattern(pattern_smile);
    
    CyDelay(3000);
    
    LedMatrix_SetSinglePattern(pattern_frame);
    
    CyDelay(3000);
    
    //-------------------------------------PRUEBA 3: MODO MULTI----------------------------------------
    
    uint8 frame_index = 0; // Para llevar la cuenta del fotograma
    uint8 size = sizeof(animation) / sizeof(animation[0]);
    
    LedMatrix_SetMode(LEDMATRIX_MODE_MULTI);
    
    LedMatrix_SetMultiPattern(animation, size);
    

    for(;;)
    {
        // Muestra el fotograma actual
        LedMatrixShowPatternAtIndex(frame_index);
        
        // Avanza al siguiente fotograma
        frame_index++;
        
        // Si llegamos al final, reinicia
        if (frame_index >= size) {
            frame_index = 0;
        }
        
        // Control de velocidad
        if (frame_index == 0) { // Si acabamos de mostrar el corazón...
            CyDelay(1000);
        } else {
            CyDelay(600); // Tiempo entre letras
        }
    }
}


