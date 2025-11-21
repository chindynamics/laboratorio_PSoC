#include "project.h"
#include "Display.h"

static uint8 _mode = DISPLAY_MODE_NONE;
static uint8 _status = DISPLAY_SEGMENT_NONE;

static uint8 _value = 0;
static const uint8 _num_patterns[] = { //CONST LLEVA A LA ROM Y LIBERA RAM
    DISPLAY_0,
    DISPLAY_1,
    DISPLAY_2,
    DISPLAY_3,
    DISPLAY_4,
    DISPLAY_5,
    DISPLAY_6,
    DISPLAY_7,
    DISPLAY_8,
    DISPLAY_9,
    DISPLAY_A,
    DISPLAY_B,
    DISPLAY_C,
    DISPLAY_D,
    DISPLAY_E,
    DISPLAY_F
};

static const uint8* _patterns = NULL;
static uint8 _size = -1;

// REINICIO, RESET DEL MODO, APAGA DISPLAY
void Display_Start(void) {
    _mode = DISPLAY_MODE_NONE;
    _status = DISPLAY_SEGMENT_NONE;
    _value = 0;
    _patterns = NULL;
    _size = -1;
    
    DisplayPin_Write(_status);
}

uint8 Display_GetMode(void) {
    return _mode;
}
void Display_SetMode(uint8 mode) {
    switch (mode) {
        case DISPLAY_MODE_NONE:
            Display_Start();
            break;
        case DISPLAY_MODE_DECIMAL:
        case DISPLAY_MODE_HEXADECIMAL:
            _value = 0;
            _status = _num_patterns[_value];
            DisplayPin_Write(_status);
            _mode = mode; // ACEPTAR MODO Y GUARDARLO COMO GLOBAL
            break;
        case DISPLAY_MODE_PATTERNS: // PENDIENTE
            _patterns = NULL;
            _size = -1;
            _status = DISPLAY_SEGMENT_NONE;
            DisplayPin_Write(_status);
            _mode = mode;
            break;
        
        default: // NO HAGAS NADA
            break;
    }
}

uint8 Display_GetValue(void) {
    return _value;
}
void Display_SetValue(uint8 value) {
    switch (_mode) {
        case DISPLAY_MODE_DECIMAL:
            if (value < 10) {
                _value = value;
                _status = _num_patterns[_value];
                DisplayPin_Write(_status);
            }
            
            break;
            
        case DISPLAY_MODE_HEXADECIMAL:
            if (value < 16) {
                _value = value;
                _status = _num_patterns[_value];
                DisplayPin_Write(_status);
            }
            break;
        
        default: // NO HAGAS NADA
            break;
    }
}

bool Display_IncrementValue(void) {
    
    bool result = FALSE;
    
    
    switch (_mode) {
        case DISPLAY_MODE_DECIMAL:
            if (_value < 9) {
                _value++;
                _status = _num_patterns[_value];
                DisplayPin_Write(_status);
                result = TRUE;
            }
            break;
        case DISPLAY_MODE_HEXADECIMAL:
            if (_value < 15) {
                _value++;
                _status = _num_patterns[_value];
                DisplayPin_Write(_status);
                result = TRUE;
            }
            break;
        
        default: //NO HAGAS NADA
            break;
    }
    
    return result;
}
bool Display_DecrementValue(void) {
    bool result = FALSE;
    
    
    switch (_mode) {
        case DISPLAY_MODE_DECIMAL:
        case DISPLAY_MODE_HEXADECIMAL:
            if (_value > 0) {
                _value--;
                _status = _num_patterns[_value];
                DisplayPin_Write(_status);
                result = TRUE;
            }
            break;
        
        default: //NO HAGAS NADA
            break;
    }
    
    return result;
}

void Display_SetPatternsArray(const uint8* patterns, uint8 size) {
    
    switch(_mode) {
        case DISPLAY_MODE_PATTERNS:
            if(patterns != NULL && size > 0) {
                _patterns = patterns;
                _size = size;
            }
            
            break;
        
        default: //do nothing
            break;
    }
}

void Display_ShowPattern(uint8 index) {
    switch(_mode) {
        case DISPLAY_MODE_PATTERNS:
            if(_patterns != NULL && index < _size) {
                _status = _patterns[index];
                DisplayPin_Write(_status);
            }
            break;
        
        default: //do nothing
            break;
    }
}
