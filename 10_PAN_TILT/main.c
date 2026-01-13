#include "project.h"
#include "keypad.h"
#include "PanTilt.h"

uint8 buffer[3]; 
uint8 bufferIndex = 0;

const Position autoSequence[] = { 
    {0, 0}, {90, 90}, {180, 180}, {45, 135}, {135, 45}
};

// --- FUNCIONES AUXILIARES ---

// Limpia el buffer para recibir un nuevo número
void ClearBuffer(void) {
    for(int i = 0; i < 3; i++) buffer[i] = 0;
    bufferIndex = 0;
}

// Agrega un dígito al buffer (0-9)
void Buffer_Add(uint8 number) {
    if (bufferIndex < 3) { 
        buffer[bufferIndex] = number;
        bufferIndex++;
    }
}

// Convierte el buffer {1, 8, 0} en el número 180
uint8 Buffer_GetVal(void) {
    uint16 total = 0;
    for(uint8 i = 0; i < bufferIndex; i++) {
        total = (total * 10) + buffer[i];
    }
    // Protección de seguridad (Servo max 180)
    if (total > 180) total = 180;
    
    return (uint8)total;
}

int main(void)
{
    CyGlobalIntEnable; /* Habilita interrupciones globales */
    
    Keypad_Start();
    PanTilt_Start();
    
    uint8 size = sizeof(autoSequence)/sizeof(Position);
    
    PanTilt_SetAutoPattern(autoSequence, size); 

    for(;;)
    {

        PanTilt_Process();
        
        // ========================================================
        // 2. LECTURA DEL TECLADO
        // ========================================================
        if(Keypad_HasKey()) {
            
            uint8 key = Keypad_GetKey(); 
            
            CyDelay(2000); 
            
            if (PanTilt_GetMode() == PANTILT_MODE_SINGLE) {
                switch(key) {
                    case KEYPAD_0: Buffer_Add(0); break;
                    case KEYPAD_1: Buffer_Add(1); break;
                    case KEYPAD_2: Buffer_Add(2); break;
                    case KEYPAD_3: Buffer_Add(3); break;
                    case KEYPAD_4: Buffer_Add(4); break;
                    case KEYPAD_5: Buffer_Add(5); break;
                    case KEYPAD_6: Buffer_Add(6); break;
                    case KEYPAD_7: Buffer_Add(7); break;
                    case KEYPAD_8: Buffer_Add(8); break;
                    case KEYPAD_9: Buffer_Add(9); break;
                    default: break; 
                }
            }
            
            switch(key) {
                
                // >>>> SELECCIÓN DE MODO <<<<
                case KEYPAD_A: 
                    PanTilt_SetMode(PANTILT_MODE_MANUAL);
                    ClearBuffer();
                    break;
                    
                case KEYPAD_B: 
                    PanTilt_SetMode(PANTILT_MODE_SINGLE);
                    ClearBuffer();
                    break;
                    
                case KEYPAD_C: 
                    PanTilt_SetMode(PANTILT_MODE_AUTO);
                    ClearBuffer();
                    break;
                
                case KEYPAD_F: 
                    if (PanTilt_GetMode() == PANTILT_MODE_SINGLE) {
                        uint8 angle = Buffer_GetVal(); 
                        Position pos = PanTilt_GetPoint();
                        pos.x = angle; // Actualizar solo X
                        PanTilt_SetPoint(pos);
                        ClearBuffer();
                    }
                    else if (PanTilt_GetMode() == PANTILT_MODE_AUTO) {
                        PanTilt_AutoStart(); // Arrancar Secuencia
                    }
                    break;

                // >>>> TECLA GATO (#) = ENTER Y / STOP <<<<
                case KEYPAD_E: 
                    if (PanTilt_GetMode() == PANTILT_MODE_SINGLE) {
                        uint8 angle = Buffer_GetVal();
                        Position pos = PanTilt_GetPoint();
                        pos.y = angle; // Actualizar solo Y
                        PanTilt_SetPoint(pos);
                        ClearBuffer();
                    }
                    else if (PanTilt_GetMode() == PANTILT_MODE_AUTO) {
                        PanTilt_AutoStop(); // Pausar Secuencia
                    }
                    break;
            }
        }
    }
}