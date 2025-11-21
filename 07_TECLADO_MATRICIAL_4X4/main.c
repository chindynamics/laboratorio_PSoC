#include "project.h"
#include "keypad.h"
#include "Display.h"

int main(void)
{
    CyGlobalIntEnable; 
    
    Keypad_Start();

    Display_Start();
    Display_SetMode(DISPLAY_MODE_HEXADECIMAL);
    
    Display_SetValue(5); //prueba
    
    CyDelay(1000);

    for(;;)
    {
        if(Keypad_HasKey()) {
            uint8 key = Keypad_GetKey();
            
            switch(key) {
                case KEYPAD_0: Display_SetValue(0);     break;
                case KEYPAD_1: Display_SetValue(1);     break;
                case KEYPAD_2: Display_SetValue(2);     break;
                case KEYPAD_3: Display_SetValue(3);     break;
                case KEYPAD_4: Display_SetValue(4);     break;
                case KEYPAD_5: Display_SetValue(5);     break;
                case KEYPAD_6: Display_SetValue(6);     break;
                case KEYPAD_7: Display_SetValue(7);     break;
                case KEYPAD_8: Display_SetValue(8);     break;
                case KEYPAD_9: Display_SetValue(9);     break;
                case KEYPAD_A: Display_SetValue(10);    break;
                case KEYPAD_B: Display_SetValue(11);    break;
                case KEYPAD_C: Display_SetValue(12);    break;
                case KEYPAD_D: Display_SetValue(13);    break;
                case KEYPAD_E: Display_SetValue(14);    break;
                case KEYPAD_F: Display_SetValue(15);    break;
                default:
                    // do nothing
                    break;
            }
        }
    }
}

