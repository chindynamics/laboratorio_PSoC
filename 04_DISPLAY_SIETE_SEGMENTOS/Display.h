#ifndef _DISPLAY_H_
#define _DISPLAY_H_
    
#include <cytypes.h>
#include <bool.h>
    
// 0 - Common anode
// 1 - Common cathode
#define DISPLAY_CONFIG 0
    
#define DISPLAY_SEGMENT_NONE    0x00
#define DISPLAY_SEGMENT_A       0x40
#define DISPLAY_SEGMENT_B       0x20
#define DISPLAY_SEGMENT_C       0x10
#define DISPLAY_SEGMENT_D       0x08
#define DISPLAY_SEGMENT_E       0x04
#define DISPLAY_SEGMENT_F       0x02
#define DISPLAY_SEGMENT_G       0x01
#define DISPLAY_SEGMENT_ALL     0x7F
    
    
                    // -abc defg
#define DISPLAY_0   0x7E
#define DISPLAY_1   0x30
#define DISPLAY_2   0x6D
#define DISPLAY_3   0x79
#define DISPLAY_4   0x33
#define DISPLAY_5   0x5B
#define DISPLAY_6   0x5F
#define DISPLAY_7   0x70
#define DISPLAY_8   0x7F
#define DISPLAY_9   0x7B
#define DISPLAY_A   0x77
#define DISPLAY_B   0x1F
#define DISPLAY_C   0x0D
#define DISPLAY_D   0x3D
#define DISPLAY_E   0x4F
#define DISPLAY_F   0x47
    
#define DISPLAY_MODE_NONE           0
#define DISPLAY_MODE_DECIMAL        1
#define DISPLAY_MODE_HEXADECIMAL    2
#define DISPLAY_MODE_PATTERNS       3
    
void Display_Start(void);

uint8 Display_GetMode(void);
void Display_SetMode(uint8 mode);

// Decimal-Hexadecimal mode
uint8 Display_GetValue(void);
void Display_SetValue(uint8 value);

bool Display_IncrementValue(void);
bool Display_DecrementValue(void);

// Patterns mode

void Display_SetPatternsArray(const uint8* patterns, uint8 size);
void Display_ShowPattern(uint8 index);


//DISPLAY -> Implementar
//void 
//uint8 Display_GetPatternIndex(void);
//bool Display_NextPattern(void);
//bool Display_PreviousPattern(void);
    
#endif // _DISPLAY_H_