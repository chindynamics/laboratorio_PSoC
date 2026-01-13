#include "project.h"
#include "DualServo.h"

int main(void)
{
    CyGlobalIntEnable;
    DualServo_Start();
    
    // --- VARIABLE A CAMBIAR MANUALMENTE ---
    //uint16 valor_prueba = 1300; 
    
    //PWM_WriteCompare(valor_prueba);  // Canal 1 

    for(;;)
    {
        
        // 1. Ir a 0 grados (Debe ser tu marca 350 exacto)
        DualServo_SetAngleX(0);
        CyDelay(2000);
        
        // 2. Ir a 90 grados (El centro matemático, aprox 1350)
        DualServo_SetAngleX(45);
        CyDelay(2000);
        
        // 3. Ir a 180 grados (Debe ser tu marca 2350 exacto)
        DualServo_SetAngleX(90);
        CyDelay(2000);
        
        DualServo_SetAngleX(135);
        CyDelay(2000);
        
        DualServo_SetAngleX(180);
        CyDelay(2000);
        
    }
}