#ifndef LU_DO_SCHM_DSC_h
#define LU_DO_SCHM_DSC_h

#include "LuGenOp.h"
enum RELE_INPUT_NAMES{
RELEY_IN_NAME__RIN = 1,
RELEY_IN_NAME__RESET,
RELEY_IN_NAME__BL_IMP,
RELEY_IN_NAME__C1_C2,
RELEY_IN_NAME__C1,
RELEY_IN_NAME__C2,
TOTAL_RELE_VISIO_IN = RELEY_IN_NAME__C2
};


enum RELE_OUTPUT_NAMES{
RELE_OUT_NAME__RELE_STATE_OUTPUT = 1,
TOTAL_RELE_VISIO_OUTPUT = RELE_OUT_NAME__RELE_STATE_OUTPUT
};

enum RELE_MNU_SELECTION1{
RELE_SEL1___NORMAL = 0,
RELE_SEL1___TRIGGER
};
enum RELE_MNU_SELECTION2{
RELE_SEL1__STABLE = 0,
RELE_SEL1__PULSE
};
enum RELE_MNU_SELECTION3{
RELE_SEL1__SIMPLE = 0,
RELE_SEL1__EXTENDED
};
enum RELE_MNU_SELECTION4{

};
enum RELE_MNU_SELECTION5{

};

enum RELE_SCHEMATIC_LU_ORDER_NUMS{
RELE_Not01__1_1, 
RELE_And02__2_1, 
RELE_And03__2_1, 
RELE_And04__2_1, 
RELE_Or_05__2_1, 
RELE_D_TRG_06__2_2, 
RELE_Or_07__2_1, 
RELE_And08__2_1, 
RELE_Or_09__2_1, 
RELE_And10__2_1, 
RELE_And11__2_1,
RELE_And12__2_1,
RELE_Or_13__2_1,
RELE_Or_14__2_1,
RELE_Not15__1_1,
RELE_And16__3_1,
RELE_And17__3_1,
RELE_Or_18__3_1,
IN_RELE_NORMAL_SELECTOR,
IN_RELE_TRIGGER_SELECTOR,
IN_RELE_STABLE_SELECTOR,
IN_RELE_PULSE_SELECTOR,
IN_RELE_PULSE_SIMPLE_SELECTOR,
IN_RELE_PULSE_EXTANDED_SELECTOR,
IN_RELE__RIN ,
IN_RELE__RESET,
IN_RELE__BL_IMP,
IN_RELE__C1_C2,
IN_RELE_C1   ,
IN_RELE_C2   ,
IN_RELE_VCC,
IN_RELE_GROUND,
TOTAL_PROCESS_RELE_LU
};
enum RELE_SCH_ORDER_NUM_OFFSET_OUTS{
OFFSET_OUT_RELE_Not01__1_1 = 0, 
OFFSET_OUT_RELE_And02__2_1, 
OFFSET_OUT_RELE_And03__2_1, 
OFFSET_OUT_RELE_And04__2_1, 
OFFSET_OUT_RELE_Or_05__2_1, 
OFFSET_OUT_RELE_D_TRG_06__2_2, 
OFFSET_OUT_RELE_Or_07__2_1 = OFFSET_OUT_RELE_D_TRG_06__2_2 + 2, 
OFFSET_OUT_RELE_And08__2_1, 
OFFSET_OUT_RELE_Or_09__2_1, 
OFFSET_OUT_RELE_And10__2_1, 
OFFSET_OUT_RELE_And11__2_1,
OFFSET_OUT_RELE_And12__2_1,
OFFSET_OUT_RELE_Or_13__2_1,
OFFSET_OUT_RELE_Or_14__2_1,
OFFSET_OUT_RELE_Not15__1_1,
OFFSET_OUT_RELE_And16__3_1,
OFFSET_OUT_RELE_And17__3_1,
OFFSET_OUT_RELE_Or_18__3_1,
OFFSET_OUT_IN_RELE_NORMAL_SELECTOR,
OFFSET_OUT_IN_RELE_TRIGGER_SELECTOR,
OFFSET_OUT_IN_RELE_STABLE_SELECTOR,
OFFSET_OUT_IN_RELE_PULSE_SELECTOR,
OFFSET_OUT_IN_RELE_PULSE_SIMPLE_SELECTOR,
OFFSET_OUT_IN_RELE_PULSE_EXTANDED_SELECTOR,
OFFSET_OUT_IN_RELE__RIN ,
OFFSET_OUT_IN_RELE__RESET,
OFFSET_OUT_IN_RELE__BL_IMP,
OFFSET_OUT_IN_RELE__C1_C2,
OFFSET_OUT_IN_RELE_C1   ,
OFFSET_OUT_IN_RELE_C2   ,
OFFSET_OUT_IN_RELE_VCC,
OFFSET_OUT_IN_RELE_GROUND,
TOTAL_RELE_LU_CALC_POINT  
};


#endif

