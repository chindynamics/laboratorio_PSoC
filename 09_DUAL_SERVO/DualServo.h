#ifndef DUALSERVO_H
#define DUALSERVO_H

#include "cytypes.h"
#include "project.h"

void DualServo_Start(void);

void DualServo_SetAngleX(uint8 angle);

void DualServo_SetAngleY(uint8 angle);

void DualServo_SetAngleXY(uint8 angleX, uint8 angleY);

#endif
