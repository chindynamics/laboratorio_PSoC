#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include <cytypes.h>
#include "bool.h"

#define KEYPAD_NONE     0xFF
#define KEYPAD_0        0xEB
#define KEYPAD_1        0x77
#define KEYPAD_2        0x7B
#define KEYPAD_3        0x7D
#define KEYPAD_4        0xB7
#define KEYPAD_5        0xBB
#define KEYPAD_6        0xBD
#define KEYPAD_7        0xD7
#define KEYPAD_8        0xDB
#define KEYPAD_9        0xDD
#define KEYPAD_A        0x7E
#define KEYPAD_B        0xBE
#define KEYPAD_C        0xDE
#define KEYPAD_D        0xEE
#define KEYPAD_E        0xED    // #
#define KEYPAD_F        0xE7    // *
    
void Keypad_Start(void);

bool Keypad_HasKey(void);
uint8 Keypad_GetKey(void);

#endif // _KEYPAD_H_