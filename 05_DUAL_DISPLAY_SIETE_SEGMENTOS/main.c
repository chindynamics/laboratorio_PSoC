#include "DDisplay.h"
#include "project.h"
#include <cytypes.h>

const uint16 pattern[] = {
    
    // PATRON DE HO
    ( (DDISPLAY_SEGMENT_F_L << 8 | DDISPLAY_SEGMENT_E_L << 8 | DDISPLAY_SEGMENT_B_L << 8 | DDISPLAY_SEGMENT_C_L << 8 | DDISPLAY_SEGMENT_G_L << 8) |
      (DDISPLAY_SEGMENT_A_R | DDISPLAY_SEGMENT_F_R | DDISPLAY_SEGMENT_E_R | DDISPLAY_SEGMENT_D_R | DDISPLAY_SEGMENT_C_R | DDISPLAY_SEGMENT_B_R)
    ),
    
    // PATRON DE OL
    ( (DDISPLAY_SEGMENT_A_R << 8 | DDISPLAY_SEGMENT_F_R << 8 | DDISPLAY_SEGMENT_E_R << 8 | DDISPLAY_SEGMENT_D_R << 8 | DDISPLAY_SEGMENT_C_R << 8 | DDISPLAY_SEGMENT_B_R << 8) |
      (DDISPLAY_SEGMENT_F_L | DDISPLAY_SEGMENT_E_L | DDISPLAY_SEGMENT_D_L)
    ),
    
    // PATRON LA
    ( (DDISPLAY_SEGMENT_F_L << 8 | DDISPLAY_SEGMENT_E_L << 8 | DDISPLAY_SEGMENT_D_L << 8) |
      (DDISPLAY_SEGMENT_A_R | DDISPLAY_SEGMENT_F_R | DDISPLAY_SEGMENT_E_R | DDISPLAY_SEGMENT_C_R | DDISPLAY_SEGMENT_B_R | DDISPLAY_SEGMENT_G_R)
    ),
    
    // PATRON A_
    ( (DDISPLAY_SEGMENT_A_R << 8 | DDISPLAY_SEGMENT_F_R << 8 | DDISPLAY_SEGMENT_E_R << 8 | DDISPLAY_SEGMENT_C_R << 8 | DDISPLAY_SEGMENT_B_R << 8 | DDISPLAY_SEGMENT_G_R << 8) |
      (DDISPLAY_SEGMENT_D_L)
    ),
    
    // PATRON DE __
    ( (DDISPLAY_SEGMENT_D_L << 8 ) |
      (DDISPLAY_SEGMENT_D_R)
    ),
    
};  

int main(void)
{
    CyGlobalIntEnable; 
    
    DDisplay_Start();
    
    uint8 size = sizeof(pattern) / sizeof(pattern[0]);
    
    // PRUEBA 1 MODO DECIMAL (00 A 99)
    
    DDisplay_SetMode(DDISPLAY_MODE_DECIMAL);
    CyDelay(5000);
    while(DDisplay_IncrementValue(FALSE)) {
        CyDelay(200);
    }
    
    CyDelay(1000);
    
    // --- PRUEBA 2: INCREMENTAR y DECREMENTAR ---
    DDisplay_SetValue(0); // Empezar en 0
    CyDelay(2000);
    for (uint8 i = 0; i < 15; i++)
    {
        DDisplay_IncrementValue(FALSE);
        CyDelay(200);
    }
    CyDelay(1000);
    for (uint8 i = 0; i < 5; i++)
    {
        DDisplay_DecrementValue(FALSE);
        CyDelay(200);
    }
    CyDelay(2000); 
    
    // --- PRUEBA 3: MODO HEXADECIMAL (00 a FF) ---
    DDisplay_SetMode(DDISPLAY_MODE_HEXADECIMAL);
    DDisplay_SetValue(240); 
    CyDelay(1000);
    DDisplay_SetValue(50); 
    CyDelay(1000);
    DDisplay_SetValue(89); 
    CyDelay(1000);
    
    // --- PRUEBA 4: MODO DE PATRONES ---
    DDisplay_SetMode(DDISPLAY_MODE_PATTERNS);
    DDisplay_SetPatternsArray(pattern, size);
    DDisplay_ShowPattern(0);
    
    CyDelay(2000);
    
    while(DDisplay_NextPattern(FALSE)) {
        CyDelay(1000);
    }
    
    while(DDisplay_PreviousPattern(FALSE)) {
        CyDelay(1000);
    }

    for(;;)
    {
        
    }  
}