#include "project.h"
#include "keypad.h"

static volatile uint8 _lastKey = KEYPAD_NONE;

static void isr(void) {
    
    uint8 keyFound = KEYPAD_NONE;
    uint8 start = 0x01;
    
    for(int i = 0; i < 4; i++) {
        uint8 pattern_row = (~start) & 0x0F;    // máscara, ir moviendo los 1
        Rows_Write(pattern_row);
        
        uint8 colsValue = Columns_Read() & 0x0F;    // máscara, solo nos interesan los 4 bits menos significativos
        
        if(colsValue != 0x0F) { // si la columna es diferente al nibble menos significativo, no nos interesa
            keyFound = (pattern_row << 4) | colsValue;
            break;
        }
        
        start = start << 1;     // mover el 1 a la siguiente posición para comprobar
    }
    
    if(_lastKey == KEYPAD_NONE) {_lastKey = keyFound;}
    
    Rows_Write(0x00);
    Columns_ClearInterrupt();
}

void Keypad_Start(void) {
    
    _lastKey = KEYPAD_NONE;
    Rows_Write(0x00);   // esperar falling edge
    isrKeypad_StartEx(isr);
    
}

bool Keypad_HasKey(void) {
    
    return _lastKey != KEYPAD_NONE;
    
}

uint8 Keypad_GetKey(void) {
    
    uint8 key = _lastKey;
    _lastKey = KEYPAD_NONE;
    return key;
    
}