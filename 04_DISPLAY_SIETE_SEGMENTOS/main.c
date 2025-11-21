#include "project.h"
#include "Display.h"

static const uint8 patterns[] = {
    DISPLAY_SEGMENT_B | DISPLAY_SEGMENT_C | DISPLAY_SEGMENT_E | DISPLAY_SEGMENT_F | DISPLAY_SEGMENT_G,
    DISPLAY_SEGMENT_A | DISPLAY_SEGMENT_B | DISPLAY_SEGMENT_C | DISPLAY_SEGMENT_D | DISPLAY_SEGMENT_E | DISPLAY_SEGMENT_F,
    DISPLAY_SEGMENT_D | DISPLAY_SEGMENT_E | DISPLAY_SEGMENT_F,
    DISPLAY_SEGMENT_A | DISPLAY_SEGMENT_B | DISPLAY_SEGMENT_C | DISPLAY_SEGMENT_E | DISPLAY_SEGMENT_F | DISPLAY_SEGMENT_G,
    DISPLAY_SEGMENT_D
};

int main(void)
{
    CyGlobalIntEnable;
    
    Display_Start();
    
    Display_SetMode(DISPLAY_MODE_PATTERNS);
    
    uint8 size = sizeof(patterns) / sizeof(patterns[0]); //Sacar el número de bytes que utiliza esa variable, número de elementos
    Display_SetPatternsArray(patterns, size); //Contar dirección de memoria y tamaño para evitar pasarnos.
        
    /*Display_SetMode(DISPLAY_MODE_DECIMAL);
    
    Display_SetValue(2);
    CyDelay(1000);
    Display_SetValue(5);
    CyDelay(1000);
    Display_SetValue(3);
    CyDelay(1000); */

    for(;;)
    {
        /*Display_SetMode(DISPLAY_MODE_DECIMAL);
        while (Display_IncrementValue()) { CyDelay(500); }
        while (Display_DecrementValue()) { CyDelay(500); }
        
        Display_SetMode(DISPLAY_MODE_HEXADECIMAL);
        while (Display_IncrementValue()) { CyDelay(500); }
        while (Display_DecrementValue()) { CyDelay(500); }*/
        for (uint8 i = 0; i < size; i++) {
            Display_ShowPattern(i);
            CyDelay(1000);
        }
        
        
    }
}

