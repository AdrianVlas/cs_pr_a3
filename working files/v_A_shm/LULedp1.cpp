#ifndef LU_LED_SCHEMATIC_DSC_CONST_C
#define LU_LED_SCHEMATIC_DSC_CONST_C

const short arShOffsets[TOTAL_LU_CALC_POINT] = {
OFFSET_OUT_IN_00_LEDIN ,
OFFSET_OUT_IN_01_RESET ,
OFFSET_OUT_IN_02_BL_IMP,
OFFSET_OUT_IN_03_C1_C2_SELECTOR ,
OFFSET_OUT_IN_04_C1  ,
OFFSET_OUT_IN_05_C2  ,
OFFSET_OUT_IN_06_TEST_BL,
OFFSET_OUT_IN_07_TIN   ,
OFFSET_OUT_IN_08_TEST  ,

OFFSET_OUT_LED_NOT_01__1_1, 
OFFSET_OUT_LED_AND_02__2_1, 
OFFSET_OUT_LED_AND_03__2_1, 
OFFSET_OUT_LED_AND_04__2_1, 
OFFSET_OUT_LED_Or_05__2_1, 
OFFSET_OUT_LED_D_TRG_06__4_2, 
OFFSET_OUT_LED_OR_07__2_1, 
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
OFFSET_OUT_IN_MNU_NORMAL_SELECTOR ,
OFFSET_OUT_IN_MNU_TRIGGER_SELECTOR,
OFFSET_OUT_IN_MNU_STABLE_SELECTOR,
OFFSET_OUT_IN_MNU_PULSE_SELECTOR,
OFFSET_OUT_IN_MNU_PULSE_SIMPLE_SELECTOR,
OFFSET_OUT_IN_MNU_PULSE_EXTANDED_SELECTOR,
OFFSET_OUT_IN_LED_VCC,
OFFSET_OUT_IN_LED_GROUND,
TOTAL_PROCESS_LED_LU
};



//IN_00_LEDIN  ,

//IN_01_RESET  ,

//IN_02_BL_IMP ,

//IN_03_C1_C2_SELECTOR,

//IN_04_C1   ,

//IN_05_C2   ,
//LED_NOT_01__1_1, 
const LUShcemasInDataDsc arNot01__1_1InDataDsc[1] = {
IN_00_LEDIN, 0
};
const LedShcemasDscRecord Not01__1_1DscRec = {
1,1,LU_GEN_OP_NOT,LED_NOT_01__1_1,
&arNot01__1_1InDataDsc[0]
};
//LED_And02__2_1, 
const LUShcemasInDataDsc arAnd02__2_1InDataDsc[2] = {
{LED_NOT_01__1_1, 0},{IN_01_RESET,0}
};

const LedShcemasDscRecord And02__2_1DscRec = {
2,1,LU_GEN_OP_AND,LED_AND_02__2_1,
&arAnd02__2_1InDataDsc[0]
};

//LED_And03__2_1, 
const LUShcemasInDataDsc arAnd03__2_1InDataDsc[2] = {
{IN_00_LEDIN, 0},{IN_MNU_NORMAL_SELECTOR,0}
};

const LedShcemasDscRecord And03__2_1DscRec = {
2,1,LU_GEN_OP_AND,LED_AND_03__2_1, 
&arAnd03__2_1InDataDsc[0]
};

//LED_And04__2_1, 
const LUShcemasInDataDsc arAnd04__2_1InDataDsc[2] = {
{IN_00_LEDIN, 0},{IN_MNU_TRIGGER_SELECTOR,0}
};

const LedShcemasDscRecord And04__2_1DscRec = {
2,1,LU_GEN_OP_AND,LED_AND_04__2_1,
&arAnd04__2_1InDataDsc[0]
};

//LED_Or_05__2_1, 
const LUShcemasInDataDsc arOr_05__2_1InDataDsc[2] = {
{IN_MNU_NORMAL_SELECTOR, 0},{LED_AND_02__2_1,0}//not Led In
};
const LedShcemasDscRecord Or_05__2_1DscRec = {
2,1,LU_GEN_OP_OR,LED_Or_05__2_1,
&arOr_05__2_1InDataDsc[0]
}; 
//LED_D_TRG_06__3_2, 
const LUShcemasInDataDsc arD_TRG_06__4_2InDataDsc[4] = {
{IN_LED_GROUND,0},//Set
{LED_Or_05__2_1,0},//Clr
{IN_LED_VCC,0},//D
{LED_AND_04__2_1, 0}//C
//{IN_VCC,0},{IN_VCC,0},{LED_AND_04__2_1,0},{LED_Or_05__2_1, 0}
};
const LedShcemasDscRecord D_TRG_06__4_2DscRec = {
4,2,LU_GEN_OP_D_TRIGGER,LED_D_TRG_06__4_2,
&arD_TRG_06__4_2InDataDsc[0]
};
//LED_Or_07__2_1, 
const LUShcemasInDataDsc arOr_07__2_1InDataDsc[2] = {
{LED_AND_03__2_1, 0},{LED_D_TRG_06__4_2,0}//not Led In
};
const LedShcemasDscRecord Or_07__2_1DscRec = {
2,1,LU_GEN_OP_OR,LED_OR_07__2_1,
&arOr_07__2_1InDataDsc[0]
};
//LED_And08__2_1, 
const LUShcemasInDataDsc arAnd08__2_1InDataDsc[2] = {
{IN_02_BL_IMP, 0},{IN_MNU_PULSE_SELECTOR,0}
};

const LedShcemasDscRecord And08__2_1DscRec = {
2,1,LU_GEN_OP_AND,LED_AND_08__2_1,
&arAnd08__2_1InDataDsc[0]
};
 
//LED_And09__2_1, 
const LUShcemasInDataDsc arAnd09__2_1InDataDsc[2] = {
{IN_MNU_STABLE_SELECTOR, 0},{LED_OR_07__2_1,0}//not Led In
};
const LedShcemasDscRecord And09__2_1DscRec = {
2,1,LU_GEN_OP_AND,LED_AND_09__2_1,
&arAnd09__2_1InDataDsc[0]
};
//LED_And10__2_1, 
const LUShcemasInDataDsc arAnd10__2_1InDataDsc[2] = {
{IN_MNU_PULSE_SELECTOR, 0},{LED_OR_07__2_1,0}//not Led In
};
const LedShcemasDscRecord And10__2_1DscRec = {
2,1,LU_GEN_OP_AND,LED_AND_10__2_1,
&arAnd10__2_1InDataDsc[0]
};
//LED_And13__2_1,
const LUShcemasInDataDsc arAnd13__2_1InDataDsc[2] = {
{IN_MNU_PULSE_EXTANDED_SELECTOR, 0},{IN_03_C1_C2_SELECTOR,0}//not Led In
};
const LedShcemasDscRecord And13__2_1DscRec = {
2,1,LU_GEN_OP_AND,LED_AND_13__2_1,
&arAnd13__2_1InDataDsc[0]
};
//LED_Or_11__2_1,
const LUShcemasInDataDsc arOr_11__2_1InDataDsc[2] = {
{IN_04_C1, 0},{LED_AND_08__2_1,0}//not Led In
};
const LedShcemasDscRecord Or_11__2_1DscRec = {
2,1,LU_GEN_OP_OR,LED_OR_11__2_1,
&arOr_11__2_1InDataDsc[0]
};
//LED_Or_12__2_1,
const LUShcemasInDataDsc arOr_12__2_1InDataDsc[2] = {
{IN_05_C2, 0},{LED_AND_08__2_1,0}//not Led In
};
const LedShcemasDscRecord Or_12__2_1DscRec = {
2,1,LU_GEN_OP_OR,LED_OR_12__2_1,
&arOr_12__2_1InDataDsc[0]
};
//LED_Not14__1_1,
const LUShcemasInDataDsc arNot14__1_1InDataDsc[1] = {
LED_AND_13__2_1, 0
};
const LedShcemasDscRecord Not14__1_1DscRec = {
1,1,LU_GEN_OP_NOT,LED_NOT_14__1_1,
&arNot14__1_1InDataDsc[0]
};
//LED_And15__3_1,
const LUShcemasInDataDsc arAnd15__3_1InDataDsc[3] = {
{LED_AND_10__2_1, 0},{LED_OR_11__2_1,0},{LED_NOT_14__1_1,0}//not Led In
};
const LedShcemasDscRecord And15__3_1DscRec = {
3,1,LU_GEN_OP_AND,LED_AND_15__3_1,
&arAnd15__3_1InDataDsc[0]
};
//LED_And16__3_1,
const LUShcemasInDataDsc arAnd16__3_1InDataDsc[3] = {
{LED_AND_10__2_1, 0},{LED_OR_12__2_1,0},{LED_AND_13__2_1,0}//not Led In
};
const LedShcemasDscRecord And16__3_1DscRec = {
3,1,LU_GEN_OP_AND,LED_AND_16__3_1,
&arAnd16__3_1InDataDsc[0]
};
//LED_Or_17__3_1,
const LUShcemasInDataDsc arOr17__3_1InDataDsc[3] = {
{LED_AND_09__2_1, 0},{LED_AND_15__3_1,0},{LED_AND_16__3_1,0}//not Led In
};
const LedShcemasDscRecord Or17__3_1DscRec = {
3,1,LU_GEN_OP_OR,LED_OR_17__3_1,
&arOr17__3_1InDataDsc[0]
};
/*
//Not06__1_1 ,
const LUShcemasInDataDsc arNot06__1_1InDataDsc[1] = {
IN_00_LEDIN, 0
};
const LedShcemasDscRecord Not06__1_1DscRec = {
1,1,LU_GEN_OP_NOT,Not06__1_1,
&arNot06__1_1InDataDsc[0]
};
//And07__2_1 ,
const LUShcemasInDataDsc arAnd07__2_1InDataDsc[2] = {
{IN_00_LEDIN, 0},{IN_MNU_NORMAL_SELECTOR,0}
};

const LedShcemasDscRecord And07__2_1DscRec = {
2,1,LU_GEN_OP_AND,And07__2_1,
&arAnd07__2_1InDataDsc[0]
};



//And08__2_1 ,
const LUShcemasInDataDsc arAnd08__2_1InDataDsc[2] = {
{IN_00_LEDIN, 0},{IN_MNU_TRIGGER_SELECTOR,0}
};
const LedShcemasDscRecord And08__2_1DscRec = {
2,1,LU_GEN_OP_AND,And08__2_1,
&arAnd08__2_1InDataDsc[0]
};

//And09__2_1 ,
const LUShcemasInDataDsc arAnd09__2_1InDataDsc[2] = {
{IN_01_RESET, 0},{Not06__1_1,0}//not Led In
};
const LedShcemasDscRecord And09__2_1DscRec = {
2,1,LU_GEN_OP_AND,And09__2_1,
&arAnd09__2_1InDataDsc[0]
};
//Or_10__2_1 ,

const LUShcemasInDataDsc arOr_10__2_1InDataDsc[2] = {
{IN_MNU_PULSE_SIMPLE_SELECTOR, 0},{IN_MNU_PULSE_EXTANDED_SELECTOR,0}//not Led In
};
const LedShcemasDscRecord Or_10__2_1DscRec = {
2,1,LU_GEN_OP_OR,Or_10__2_1,
&arOr_10__2_1InDataDsc[0]
}; 

//Or_11__2_1 ,
const LUShcemasInDataDsc arOr_11__2_1InDataDsc[2] = {
{And07__2_1, 0},{RS_12__2_2,0}//not Led In
};
const LedShcemasDscRecord Or_11__2_1DscRec = {
2,1,LU_GEN_OP_OR,Or_11__2_1,
&arOr_11__2_1InDataDsc[0]
}; 

//RS_12__2_2 ,
const LUShcemasInDataDsc arRS_12__2_2InDataDsc[2] = {
{And08__2_1, 0},{And09__2_1,0}//not Led In
};
const LedShcemasDscRecord RS_12__2_2DscRec = {
2,2,LU_GEN_OP_RS_TRIGGER,RS_12__2_2,
&arRS_12__2_2InDataDsc[0]
}; 
//And13__2_1 ,
const LUShcemasInDataDsc arAnd13__2_1InDataDsc[2] = {
{IN_MNU_PULSE_SELECTOR, 0},{IN_02_BL_IMP,0}//not Led In
};
const LedShcemasDscRecord And13__2_1DscRec = {
2,1,LU_GEN_OP_AND,And13__2_1,
&arAnd13__2_1InDataDsc[0]
};
//And14__2_1 ,
const LUShcemasInDataDsc arAnd14__2_1InDataDsc[2] = {
{IN_MNU_PULSE_EXTANDED_SELECTOR, 0},{IN_03_C1_C2_SELECTOR,0}//not Led In
};
const LedShcemasDscRecord And14__2_1DscRec = {
2,1,LU_GEN_OP_AND,And14__2_1,
&arAnd14__2_1InDataDsc[0]
};   
//And15__2_1,
const LUShcemasInDataDsc arAnd15__2_1InDataDsc[2] = {
{IN_MNU_STABLE_SELECTOR, 0},{Or_11__2_1,0}//not Led In
};
const LedShcemasDscRecord And15__2_1DscRec = {
2,1,LU_GEN_OP_AND,And15__2_1,
&arAnd15__2_1InDataDsc[0]
}; 
//And16__2_1,
const LUShcemasInDataDsc arAnd16__2_1InDataDsc[2] = {
{IN_MNU_PULSE_SELECTOR, 0},{Or_11__2_1,0}//not Led In
};
const LedShcemasDscRecord And16__2_1DscRec = {
2,1,LU_GEN_OP_AND,And16__2_1,
&arAnd16__2_1InDataDsc[0]
}; 
//Or_17__2_1,
const LUShcemasInDataDsc arOr_17__2_1InDataDsc[2] = {
{And13__2_1, 0},{IN_04_C1,0}//not Led In
};
const LedShcemasDscRecord Or_17__2_1DscRec = {
2,1,LU_GEN_OP_OR,Or_17__2_1,
&arOr_17__2_1InDataDsc[0]
}; 

//Or_18__2_1,
const LUShcemasInDataDsc arOr_18__2_1InDataDsc[2] = {
{And13__2_1, 0},{IN_05_C2 ,0}//not Led In
};
const LedShcemasDscRecord Or_18__2_1DscRec = {
2,1,LU_GEN_OP_OR,Or_18__2_1,
&arOr_18__2_1InDataDsc[0]
}; 
  
//Not19__1_1,
const LUShcemasInDataDsc arNot19__1_1InDataDsc[1] = {
And14__2_1, 0
};
const LedShcemasDscRecord Not19__1_1DscRec = {
1,1,LU_GEN_OP_NOT,Not19__1_1,
&arNot19__1_1InDataDsc[0]
};
//And20__3_1,
const LUShcemasInDataDsc arAnd20__3_1InDataDsc[3] = {
{And16__2_1, 0},{Or_17__2_1,0},{Not19__1_1,0}//not Led In
};
const LedShcemasDscRecord And20__3_1DscRec = {
3,1,LU_GEN_OP_AND,And20__3_1,
&arAnd20__3_1InDataDsc[0]
};
//And21__3_1,
const LUShcemasInDataDsc arAnd21__3_1InDataDsc[3] = {
{And16__2_1, 0},{Or_18__2_1,0},{And14__2_1,0}//not Led In
};
const LedShcemasDscRecord And21__3_1DscRec = {
3,1,LU_GEN_OP_AND,And21__3_1,
&arAnd21__3_1InDataDsc[0]
};
//Or_22__3_1,
const LUShcemasInDataDsc arOr22__3_1InDataDsc[3] = {
{And15__2_1, 0},{And20__3_1,0},{And21__3_1,0}//not Led In
};
const LedShcemasDscRecord Or22__3_1DscRec = {
3,1,LU_GEN_OP_OR,Or_22__3_1,
&arOr22__3_1InDataDsc[0]
};
//And23__2_1,

//And24__2_1,

//Or_25__2_1,

const LedShcemasDscRecord* const arPLedShcemasDscRecords[] = {
&Not06__1_1DscRec,
&And07__2_1DscRec,
&And08__2_1DscRec,
&And09__2_1DscRec ,
&Or_10__2_1DscRec ,
&RS_12__2_2DscRec ,
&Or_11__2_1DscRec ,
&And13__2_1DscRec ,
&And14__2_1DscRec ,
&And15__2_1DscRec ,
&And16__2_1DscRec ,
&Or_17__2_1DscRec ,
&Or_18__2_1DscRec ,
&Not19__1_1DscRec ,
&And20__3_1DscRec ,
&And21__3_1DscRec ,
&Or22__3_1DscRec
};
*/
const LedShcemasDscRecord* const arPLedShcemasDscRecords[] = {
&Not01__1_1DscRec,
&And02__2_1DscRec,
&And03__2_1DscRec,
&And04__2_1DscRec,
&Or_05__2_1DscRec,
&D_TRG_06__4_2DscRec,
&Or_07__2_1DscRec,
&And08__2_1DscRec,
&And09__2_1DscRec,
&And10__2_1DscRec,
&And13__2_1DscRec,
&Or_11__2_1DscRec,
&Or_12__2_1DscRec,
&Not14__1_1DscRec,
&And15__3_1DscRec,
&And16__3_1DscRec,
&Or17__3_1DscRec 
};

#endif
