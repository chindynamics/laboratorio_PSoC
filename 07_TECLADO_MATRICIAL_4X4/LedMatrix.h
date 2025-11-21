#ifndef _LEDMATRIX_H_
#define _LEDMATRIX_H_

#include <cytypes.h>
#include <bool.h>

#define LEDMATRIX_MODE_NONE   0
#define LEDMATRIX_MODE_LED    1
#define LEDMATRIX_MODE_SINGLE 2
#define LEDMATRIX_MODE_MULTI  3

void LedMatrix_Start(void);

void LedMatrix_SetMode(uint8 mode);
uint8 LedMatrix_GetMode(void);

// LEDMATRIX_MODE_LED
void LedMatrix_SetLed(uint8 x, uint8 y, bool state);

// LEDMATRIX_MODE_SINGLE
void LedMatrix_SetSinglePattern(const uint8* pattern);

// LEDMATRIX_MODE_MULTI
void LedMatrix_SetMultiPattern(const uint8 (*pattern)[8], uint8 size);
void LedMatrixShowPatternAtIndex(uint8 index);

#endif // _LEDMATRIX_H_