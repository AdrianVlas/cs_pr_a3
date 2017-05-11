#ifndef LU_LED_SCHM_DSC_h
#define LU_LED_SCHM_DSC_h

#include "LuGenOp.h"

enum LED_INPUT_NAMES{
LED_IN_NAME__LEDIN = 1,
LED_IN_NAME__RESET,
LED_IN_NAME__BL_IMP,
LED_IN_NAME__C1_C2,
LED_IN_NAME__C1,
LED_IN_NAME__C2,
LED_IN_NAME__TLEDIN ,
LED_IN_NAME__TEST_M,

TOTAL_LED_VISIO_IN = LED_IN_NAME__TEST_M
};


enum LED_OUTPUT_NAMES{
LED_OUT_NAME__LED_STATE_OUTPUT = 1,
TOTAL_LED_VISIO_OUTPUT = LED_OUT_NAME__LED_STATE_OUTPUT
};

enum MNU_SELECTION1{
LED_SEL1___NORMAL = 0,
LED_SEL1___TRIGGER
};
enum MNU_SELECTION2{
LED_SEL1__STABLE = 0,
LED_SEL1__PULSE
};
enum MNU_SELECTION3{
LED_SEL1__SIMPLE = 0,
LED_SEL1__EXTENDED
};
enum MNU_SELECTION4{

};
enum MNU_SELECTION5{

};

enum LED_SCHEMATIC_LU_ORDER_NUMS{
IN_00_LEDIN  ,
IN_01_RESET  ,
IN_02_BL_IMP ,
IN_03_C1_C2_SELECTOR,
IN_04_C1   ,
IN_05_C2   ,
IN_06_TEST_BL,
IN_07_TIN   ,
IN_08_TEST  ,

LED_NOT_01__1_1, 
LED_AND_02__2_1, 
LED_AND_03__2_1, 
LED_AND_04__2_1, 
LED_Or_05__2_1, 
LED_D_TRG_06__4_2, 
LED_OR_07__2_1, 
LED_AND_08__2_1, 
LED_AND_09__2_1, 
LED_AND_10__2_1,
LED_AND_13__2_1,//1
LED_OR_11__2_1,
LED_OR_12__2_1,
LED_NOT_14__1_1,
LED_AND_15__3_1,
LED_AND_16__3_1,
LED_OR_17__3_1,
LED_AND_18__2_1,
LED_AND_19__2_1,
LED_OR_20__2_1,
IN_MNU_NORMAL_SELECTOR,
IN_MNU_TRIGGER_SELECTOR,
IN_MNU_STABLE_SELECTOR,
IN_MNU_PULSE_SELECTOR,
IN_MNU_PULSE_SIMPLE_SELECTOR,
IN_MNU_PULSE_EXTANDED_SELECTOR,
IN_LED_VCC,
IN_LED_GROUND,
TOTAL_PROCESS_LED_LU
};
enum ORDER_NUM_OFFSET_OUTS{
OFFSET_OUT_IN_00_LEDIN   = 0,
OFFSET_OUT_IN_01_RESET   = OFFSET_OUT_IN_00_LEDIN + 1,
OFFSET_OUT_IN_02_BL_IMP  = OFFSET_OUT_IN_01_RESET + 1,
OFFSET_OUT_IN_03_C1_C2_SELECTOR = OFFSET_OUT_IN_02_BL_IMP + 1,
OFFSET_OUT_IN_04_C1     = OFFSET_OUT_IN_03_C1_C2_SELECTOR + 1,
OFFSET_OUT_IN_05_C2     = OFFSET_OUT_IN_04_C1             + 1,
//BE Carefull last number means amount outs in previous Element
OFFSET_OUT_IN_06_TEST_BL,
OFFSET_OUT_IN_07_TIN   ,
OFFSET_OUT_IN_08_TEST  ,

OFFSET_OUT_LED_NOT_01__1_1, 
OFFSET_OUT_LED_AND_02__2_1, 
OFFSET_OUT_LED_AND_03__2_1, 
OFFSET_OUT_LED_AND_04__2_1, 
OFFSET_OUT_LED_Or_05__2_1, 
OFFSET_OUT_LED_D_TRG_06__4_2, 
OFFSET_OUT_LED_OR_07__2_1 = OFFSET_OUT_LED_D_TRG_06__4_2 + 2, 
OFFSET_OUT_LED_AND_08__2_1, 
OFFSET_OUT_LED_AND_09__2_1, 
OFFSET_OUT_LED_AND_10__2_1,
OFFSET_OUT_LED_AND_13__2_1,//1
OFFSET_OUT_LED_OR_11__2_1,
OFFSET_OUT_LED_OR_12__2_1,
OFFSET_OUT_LED_NOT_14__1_1,
OFFSET_OUT_LED_AND_15__3_1,
OFFSET_OUT_LED_AND_16__3_1,
OFFSET_OUT_LED_OR_17__3_1,
OFFSET_OUT_LED_AND_18__2_1,
OFFSET_OUT_LED_AND_19__2_1,
OFFSET_OUT_LED_OR_20__2_1,

OFFSET_OUT_IN_MNU_NORMAL_SELECTOR = OFFSET_OUT_LED_OR_20__2_1 + 1,
OFFSET_OUT_IN_MNU_TRIGGER_SELECTOR,
OFFSET_OUT_IN_MNU_STABLE_SELECTOR,
OFFSET_OUT_IN_MNU_PULSE_SELECTOR,
OFFSET_OUT_IN_MNU_PULSE_SIMPLE_SELECTOR,
OFFSET_OUT_IN_MNU_PULSE_EXTANDED_SELECTOR,
OFFSET_OUT_IN_LED_VCC,
OFFSET_OUT_IN_LED_GROUND,


TOTAL_LU_CALC_POINT = OFFSET_OUT_IN_LED_GROUND + 1
};

////////////////////////////////////////////////////////////// 
/*
enum LED_SCHEMATIC_LU_ORDER_NUMS{                
IN_00_LEDIN  ,                                     00  
IN_01_RESET  ,                                     01  
IN_02_BL_IMP ,                                     02  
IN_03_C1_C2_SELECTOR,                              03  
IN_04_C1   ,                                       04  
IN_05_C2   ,                                       05  
IN_06_TEST_BL,                                     06  
IN_07_TIN   ,                                      07  
IN_08_TEST  ,                                      08  
LED_NOT_01__1_1,                                   09  
LED_AND_02__2_1,                                   10  
LED_AND_03__2_1,                                   11  
LED_AND_04__2_1,                                   12  
LED_Or_05__2_1,                                    13  
LED_D_TRG_06__4_2,                                 14  
LED_OR_07__2_1,                                    15  
LED_AND_08__2_1,                                   16  
LED_AND_09__2_1,                                   17  
LED_AND_10__2_1,                                   18  
LED_AND_13__2_1,//1                                19  
LED_OR_11__2_1,                                    20  
LED_OR_12__2_1,                                    21  
LED_NOT_14__1_1,                                   22  
LED_AND_15__3_1,                                   23  
LED_AND_16__3_1,                                   24  
LED_OR_17__3_1,                                    25  
LED_AND_18__2_1,                                   26  
LED_AND_19__2_1,                                   27  
LED_OR_20__2_1,                                    28  
IN_MNU_NORMAL_SELECTOR,                            29  
IN_MNU_TRIGGER_SELECTOR,                           30  
IN_MNU_STABLE_SELECTOR,                            31  
IN_MNU_PULSE_SELECTOR,                             32  
IN_MNU_PULSE_SIMPLE_SELECTOR,                      33  
IN_MNU_PULSE_EXTANDED_SELECTOR,                    34  
IN_LED_VCC,                                        35  
IN_LED_GROUND,                                     36  
TOTAL_PROCESS_LED_LU                               37  
};                                                 38  39
                                                   39
enum ORDER_NUM_OFFSET_OUTS{                                               
OFFSET_OUT_IN_00_LEDIN   = 0,                                   00            
OFFSET_OUT_IN_01_RESET   = OFFSET_OUT_IN_00_LEDIN + 1,          01
OFFSET_OUT_IN_02_BL_IMP  = OFFSET_OUT_IN_01_RESET + 1,          02
OFFSET_OUT_IN_03_C1_C2_SELECTOR = OFFSET_OUT_IN_02_BL_IMP + 1,  03
OFFSET_OUT_IN_04_C1     = OFFSET_OUT_IN_03_C1_C2_SELECTOR + 1,  04
OFFSET_OUT_IN_05_C2     = OFFSET_OUT_IN_04_C1             + 1,  05
OFFSET_OUT_IN_06_TEST_BL,                                       06
OFFSET_OUT_IN_07_TIN   ,                                        07
OFFSET_OUT_IN_08_TEST  ,                                        08
OFFSET_OUT_LED_NOT_01__1_1,                                     09
OFFSET_OUT_LED_AND_02__2_1,                                     10
OFFSET_OUT_LED_AND_03__2_1,                                     11
OFFSET_OUT_LED_AND_04__2_1,                                     12
OFFSET_OUT_LED_Or_05__2_1,                                      13
OFFSET_OUT_LED_D_TRG_06__4_2,                                   14
                                                                15
OFFSET_OUT_LED_OR_07__2_1 = OFFSET_OUT_LED_D_TRG_06__4_2 + 2,   16
OFFSET_OUT_LED_AND_08__2_1,                                     17
OFFSET_OUT_LED_AND_09__2_1,                                     18
OFFSET_OUT_LED_AND_10__2_1,                                     19
OFFSET_OUT_LED_AND_13__2_1,//1                                  20
OFFSET_OUT_LED_OR_11__2_1,                                      21
OFFSET_OUT_LED_OR_12__2_1,                                      22
OFFSET_OUT_LED_NOT_14__1_1,                                     23
OFFSET_OUT_LED_AND_15__3_1,                                     24
OFFSET_OUT_LED_AND_16__3_1,                                     25
OFFSET_OUT_LED_OR_17__3_1,                                      26
OFFSET_OUT_LED_AND_18__2_1,                                     27
OFFSET_OUT_LED_AND_19__2_1,                                     28
OFFSET_OUT_LED_OR_20__2_1,                                      29
OFFSET_OUT_IN_MNU_NORMAL_SELECTOR = OFFSET_OUT_LED_OR_20__2_1 + 301,
OFFSET_OUT_IN_MNU_TRIGGER_SELECTOR,                             31
OFFSET_OUT_IN_MNU_STABLE_SELECTOR,                              32
OFFSET_OUT_IN_MNU_PULSE_SELECTOR,                               33
OFFSET_OUT_IN_MNU_PULSE_SIMPLE_SELECTOR,                        34
OFFSET_OUT_IN_MNU_PULSE_EXTANDED_SELECTOR,                      35
OFFSET_OUT_IN_LED_VCC,                                          36
OFFSET_OUT_IN_LED_GROUND,                                       37
                                                                38
                                                                39
TOTAL_LU_CALC_POINT = OFFSET_OUT_IN_LED_GROUND + 1              40
};                                                              41

*/

#endif

