#include "Joystick.h"
#include "project.h"

void Joystick_Start(void) {
    ADC_Start();
    ADC_StartConvert();
}

uint16 Joystick_GetX(void) {
    return ADC_GetResult16(0);
}

uint16 Joystick_GetY(void) {
    return ADC_GetResult16(1);
}