#include "LedBar.h"
#include "project.h"
#include <cytypes.h>

const uint16 patterns[] = {
    LEDBAR_LED_1 | LEDBAR_LED_10,   // 1. Solo los extremos
    LEDBAR_LED_2 | LEDBAR_LED_9,    // 2. Los siguientes hacia adentro
    LEDBAR_LED_3 | LEDBAR_LED_8,    // 3. 
    LEDBAR_LED_4 | LEDBAR_LED_7,    // 4.
    LEDBAR_LED_5 | LEDBAR_LED_6,    // 5. Los dos centrales
    LEDBAR_LED_ALL,                 // 6. Todos encendidos
    LEDBAR_LED_NONE                 // 7. Todos apagados
};

int main(void)
{
    CyGlobalIntEnable;
    LedBar_Start();
    
    // PRUEBA MODO BARRA
    
    LedBar_SetMode(LEDBAR_MODE_BAR);
    LedBar_SetLevel(1);
    CyDelay(300);
    
    // PRUEBA MODO NIVEL
    LedBar_SetMode(LEDBAR_MODE_LEVEL);
    LedBar_SetLevel(8);
    CyDelay(300);
    
    // PRUEBA MODO INCREMENT
    LedBar_SetMode(LEDBAR_MODE_BAR);
    LedBar_SetLevel(0);
    while(LedBar_IncrementLevel()) {
        CyDelay(200);
    }
    
    while(LedBar_DecrementLevel()) {
        CyDelay(200);
    } 
    
    // PRUEBA MODO PATRONES
    LedBar_SetMode(LEDBAR_MODE_PATTERNS);
    uint8 size = sizeof(patterns) / sizeof(patterns[0]);
    LedBar_SetPatternArray(patterns, size);
    
    LedBar_SetPatternIndex(0);
    
    CyDelay(1000);
    
    while(LedBar_NextPattern()) {
        CyDelay(500);   
    }
    
    while(LedBar_PreviousPattern()) {
        CyDelay(500);  
    }

    for(;;)
    {
        
    }
}

