#include "PanTilt.h"
#include "DualServo.h"
#include "Joystick.h"
#include "project.h"

static uint8 _currentMode = PANTILT_MODE_NONE;
static Position _currentPosition = {90, 90};

static const Position *_autoSequence = NULL;
static uint8 _autoSize = 0;
static uint8 _autoIndex = 0;

#define ADC_MAX 4065

static void isr(void) {
    
    if(_autoSequence != NULL && _autoSize > 0) {
        Position target = _autoSequence[_autoIndex];
        DualServo_SetAngleXY(target.x, target.y);
        _autoIndex++;
        
        if(_autoIndex >= _autoSize) {
            _autoIndex = 0;   
        }
    }
    
    Timer_Seq_ClearInterrupt(Timer_Seq_INTR_MASK_TC);
}

void PanTilt_Start(void) {
    DualServo_Start();
    Joystick_Start();
    
    isr_Seq_StartEx(isr);
    Timer_Seq_Start();
    Timer_Seq_Stop();
    
    DualServo_SetAngleXY(90, 90);
    _currentMode = PANTILT_MODE_MANUAL;
}

void PanTilt_SetMode(uint8 mode) {
   
    switch(mode) {
        case PANTILT_MODE_AUTO:
            _currentMode = mode;
            PanTilt_AutoStart();
            break;
        case PANTILT_MODE_MANUAL:
            _currentMode = mode;
            PanTilt_AutoStop();   
            break;
        case PANTILT_MODE_SINGLE:
            _currentMode = mode;
            PanTilt_AutoStop();   
            break;
        case PANTILT_MODE_NONE:
            _currentMode = mode;
            PanTilt_AutoStop();   
            break;
        default:
            PanTilt_AutoStop(); 
            // do nothing
            break;
    }
}

uint8 PanTilt_GetMode() {
    return _currentMode;   
}

void PanTilt_SetPoint(Position position) {
    _currentPosition = position;
    DualServo_SetAngleXY(position.x, position.y);
}

Position PanTilt_GetPoint(void) {
    return _currentPosition;   
}

void PanTilt_SetAutoPattern(const Position* positions, uint8 size) {
    _autoSequence = positions;
    _autoSize = size;
    _autoIndex = 0;
}

void PanTilt_AutoStart(void) {
    Timer_Seq_Start();
}

void PanTilt_AutoStop(void) {
    Timer_Seq_Stop();   
}

void PanTilt_Process() {
    if(_currentMode == PANTILT_MODE_MANUAL) {
        uint32 rawX = Joystick_GetX();
        uint32 rawY = Joystick_GetY();
        
        // mapeo
        uint8 angleX = (uint8)((rawX * 180) / ADC_MAX);
        uint8 angleY = (uint8)((rawY * 180) / ADC_MAX);
        
        DualServo_SetAngleXY(angleX, angleY);
        
        _currentPosition.x = angleX;
        _currentPosition.y = angleY;
    }
}