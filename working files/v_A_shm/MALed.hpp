#pragma once
#include "lubase.h"
const short shCLUMuteAlarmLed_x_y_AmtOut = 0;
const short shCLUMuteAlarmLed_x_y_AmtIn  = 3;
enum MUTE_ALARM_LED_INPUT_NAMES{
MUTE_ALARM_LED_IN_NAME__BLOCK = 1,
MUTE_ALARM_LED_IN_NAME__ALARM ,
MUTE_ALARM_LED_IN_NAME__MUTE  ,
TOTAL_MUTE_ALARM_LED_IN = MUTE_ALARM_LED_IN_NAME__MUTE
};
enum MUTE_ALARM_COLORS{
MUTE_ALARM_HIDE,
MUTE_ALARM_GREEN,
MUTE_ALARM_RED,
MUTE_ALARM_YELLOW
};


typedef struct MuteAlarmInOutParam_t{
    long lIndexLss;
    char* pChBlock;
    char* pChAlarm;
    char* pChMute;
}MuteAlarmInOutParam;


class CMuteAlarmLed :
public CLUBase {
public:
    CMuteAlarmLed(void);
    ~CMuteAlarmLed(void);
    char* arrPchIn[shCLUMuteAlarmLed_x_y_AmtIn ];//
//    char  arrOut  [shCLUMFT_x_y_AmtOut];//
    void UpdateMuteAlarmLed(void);
    void EvalMuteAlarmLed(void);
};



