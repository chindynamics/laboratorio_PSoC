
#ifndef _PANTILT_H_
#define _PANTILT_H_

#include <cytypes.h>

typedef struct
{
    uint8 x; // 0-180
    uint8 y; // 0-180
} Position;

#define PANTILT_MODE_NONE   0
#define PANTILT_MODE_MANUAL 1
#define PANTILT_MODE_SINGLE 2
#define PANTILT_MODE_AUTO   3

void PanTilt_Start(void);

void PanTilt_SetMode(uint8 mode);
uint8 PanTilt_GetMode(void);

void PanTilt_SetPoint(Position position); // SINGLE
Position PanTilt_GetPoint(void);

void PanTilt_SetAutoPattern(const Position* positions, uint8 size); // AUTO
void PanTilt_AutoStart(void);
void PanTilt_AutoStop(void);

#endif // _PANTILT_H_
