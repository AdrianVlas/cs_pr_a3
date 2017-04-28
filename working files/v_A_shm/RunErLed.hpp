#pragma once
#include "lubase.h"
const short shCLULURunErrorLed_x_y_AmtOut = 0;
const short shCLULURunErrorLed_x_y_AmtIn  = 3;

enum RUN_ERROR_LED_COLORS{
RUN_ERROR_LED_HIDE,
RUN_ERROR_LED_GREEN,
RUN_ERROR_LED_RED,
RUN_ERROR_LED_YELLOW
};







class CLURunErrorLed :
public CLUBase {
public:
    CLURunErrorLed(void);
    ~CLURunErrorLed(void);
    char* arrPchIn[shCLULURunErrorLed_x_y_AmtIn ];//
    void UpdateRunErrorLed(void);
    void EvalRunErrorLed(void);
};

