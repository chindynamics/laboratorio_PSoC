#include "DualServo.h"

#define SERVO_MIN_PULSE 350    // 0 grados
#define SERVO_MID_PULSE 1300   // 90 grados (Centro exacto)
#define SERVO_MAX_PULSE 2350   // 180 grados

uint16 CalculatePulse(uint8 angle) {
    uint32 pulse;
    
    if (angle > 180) {
        angle = 180;
    }
    
    if (angle <= 90) {
        // TRAMO 1: De 0 a 90 grados
        // Mapeamos el rango 0-90 hacia 350-1300
        uint32 range = SERVO_MID_PULSE - SERVO_MIN_PULSE;
        pulse = SERVO_MIN_PULSE + ((uint32)angle * range) / 90;
    } 
    else {
        // TRAMO 2: De 91 a 180 grados
        // Mapeamos el rango 90-180 hacia 1300-2350
        // Restamos 90 al ángulo para calcular cuánto avanzamos desde el centro
        uint32 range = SERVO_MAX_PULSE - SERVO_MID_PULSE;
        pulse = SERVO_MID_PULSE + ((uint32)(angle - 90) * range) / 90;
    }
    
    return (uint16)pulse;
}

void DualServo_Start(void) {
    PWM_Start();
    PWM2_Start();
}

void DualServo_SetAngleX(uint8 angle) {
    PWM_WriteCompare(CalculatePulse(angle));
}

void DualServo_SetAngleY(uint8 angle) {
    PWM2_WriteCompare(CalculatePulse(angle));
}

void DualServo_SetAngleXY(uint8 angleX, uint8 angleY) {
    DualServo_SetAngleX(angleX);
    DualServo_SetAngleY(angleY);
}