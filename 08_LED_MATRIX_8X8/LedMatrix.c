#include "LedMatrix.h"
#include "project.h"

static uint8 _mode = LEDMATRIX_MODE_NONE;
static uint8 _current_row = 0;

// un buffer para el modo LED
static uint8 _led_buffer[8];
static const uint8* _single_pattern_ptr = NULL;

static const uint8 (*_multi_pattern_ptr)[8] = NULL;
static uint8 _multi_size = 0;
static uint8 _multi_index = 0;

static void isr(void) {
    Rows_Write(0xFF);
    
    uint8 pattern_to_show = 0x00;
    
    switch(_mode) {
        case LEDMATRIX_MODE_NONE:
            // do nothing
            break;
        case LEDMATRIX_MODE_LED:
            pattern_to_show = _led_buffer[_current_row];
            break;
        case LEDMATRIX_MODE_SINGLE:
            if(_single_pattern_ptr != NULL) {
                pattern_to_show = _single_pattern_ptr[_current_row];
            }
            break;
        case LEDMATRIX_MODE_MULTI:
            if(_multi_pattern_ptr != NULL) {
                pattern_to_show = _multi_pattern_ptr[_multi_index][_current_row];
            }
            break;
        default:
            // do nothing
            break;
    }
    
    Columns_Write(pattern_to_show);
    Rows_Write(~(1 << _current_row) );
    
    _current_row++;
    if(_current_row >= 8) {
        _current_row = 0;   
    }
    
    Timer_ClearInterrupt(Timer_INTR_MASK_TC);
}

void LedMatrix_Start(void) {
    _mode = LEDMATRIX_MODE_NONE;
    _current_row = 0;
    
    memset(_led_buffer, 0, sizeof(_led_buffer)); // iniciar todo con 0
    
    _single_pattern_ptr = NULL;
    _multi_pattern_ptr = NULL;
    _multi_size = 0;
    _multi_index = 0;
    
    Rows_Write(0xFF);       // Con cátodo común, un 1 apaga la fila.
    Columns_Write(0x00);    // Con cátodo común, un 0 apaga las columnas
    
    isrTimer_StartEx(isr);
    Timer_Start();
}

void LedMatrix_SetMode(uint8 mode) {
    switch(mode) {
        case LEDMATRIX_MODE_NONE:
            LedMatrix_Start();
            break;
        case LEDMATRIX_MODE_LED:
            _mode = mode;
            break;
        case LEDMATRIX_MODE_SINGLE:
            _mode = mode;
            break;
        case LEDMATRIX_MODE_MULTI:
            _mode = mode;
            break;
        default:
            //do nothing
            break;
    }
}

uint8 LedMatrix_GetMode(void) {
    return _mode;
}

void LedMatrix_SetLed(uint8 x, uint8 y, bool state) {
    if (x > 7 || y > 7) {
        return;
    }
    
    if(state) {
        _led_buffer[y] |= (1 << x);
    }
    else {
        _led_buffer[y] &= ~(1 << x); 
    }
}

void LedMatrix_SetSinglePattern(const uint8* pattern) {
    switch(_mode) {
        case LEDMATRIX_MODE_SINGLE:
            if(pattern != NULL) {
                _single_pattern_ptr = pattern;
            }
            else {
                _single_pattern_ptr = NULL;
            }
            break;
        default:
            // do nothing
            break;
    }
}

void LedMatrix_SetMultiPattern(const uint8 (*pattern)[8], uint8 size) {
    switch(_mode) {
        case LEDMATRIX_MODE_MULTI:
            if(pattern != NULL && size > 0) {
                _multi_pattern_ptr = pattern;
                _multi_size = size;
                _multi_index = 0;
            }
            else {
                _multi_pattern_ptr = NULL;
                _multi_size = 0;
                _multi_index = 0;
            }
            break;
            
        default:
            // do nothing
            break;
    }
}

void LedMatrixShowPatternAtIndex(uint8 index) {
    switch(_mode) {
        case LEDMATRIX_MODE_MULTI:
            if(_multi_pattern_ptr != NULL && index < _multi_size) {
                _multi_index = index;   
            }
            break;
        default:
            // do nothing
            break;   
    }
}