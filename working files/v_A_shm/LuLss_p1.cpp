#ifndef LU_LED_SCHEMATIC_DSC_CONST_C
#define LU_LED_SCHEMATIC_DSC_CONST_C

const short arShLssOffsets[TOTAL_LSS_LU_CALC_POINT] = {
OFFSET_OUT_LSS_NOT_01__1_1,
OFFSET_OUT_LSS_NOT_02__1_1,
OFFSET_OUT_LSS_NOT_03__1_1,
OFFSET_OUT_LSS_NOT_04__1_1,
OFFSET_OUT_LSS_DELAY_05_1_1,
OFFSET_OUT_LSS_DELAY_06_1_1,
OFFSET_OUT_LSS_OR_07__2_1,
OFFSET_OUT_LSS_NOT_08__1_1,
OFFSET_OUT_LSS_NOT_09__1_1,
OFFSET_OUT_LSS_OR_10__2_1,
OFFSET_OUT_LSS_D_TRG_11__4_2 ,
OFFSET_OUT_LSS_AND_12__3_1, 
OFFSET_OUT_LSS_DELAY_13__1_1,
OFFSET_OUT_LSS_OR_14__3_1,
OFFSET_OUT_LSS_AND_15__3_1,
OFFSET_OUT_LSS_AND_16__3_1,
OFFSET_OUT_LSS_AND_17__3_1,
OFFSET_OUT_LSS_AND_18__2_1,
OFFSET_OUT_LSS_AND_19__2_1,
OFFSET_OUT_LSS_AND_20__3_1,
OFFSET_OUT_LSS_OR_21__3_1,
OFFSET_OUT_LSS_OR_22__3_1,
OFFSET_OUT_LSS_AND_23__4_1,
OFFSET_OUT_LSS_AND_24__4_1,
OFFSET_OUT_LSS_AND_25__4_1,
OFFSET_OUT_LSS_AND_26__4_1,
OFFSET_OUT_LSS_OR_27__2_1,
OFFSET_OUT_LSS_OR_28__2_1,
OFFSET_OUT_LSS_D_TRG_29__4_2, 
OFFSET_OUT_IN_LSS_NORMAL,
OFFSET_OUT_IN_LSS_TRIGGER  ,
OFFSET_OUT_IN_LSS_TIMELIMITED, 
OFFSET_OUT_IN_LSS_LSSIN1  ,
OFFSET_OUT_IN_LSS_MUTE_I  ,
OFFSET_OUT_IN_LSS_RESET_I ,
OFFSET_OUT_IN_LSS_BLOCK_I ,
OFFSET_OUT_OUT_LSS_ALARM  ,
OFFSET_OUT_OUT_LSS_MUTE,
OFFSET_OUT_IN_LSS_VCC,
OFFSET_OUT_IN_LSS_GROUND,
TOTAL_LSS_LU_CALC_POINT
};

//Not01__1_1 ,
const LUShcemasInDataDsc arNot01__1_1InDataDsc[1] = {
LSS_NAME_LSS_D, 0
};
const LedShcemasDscRecord Not01__1_1DscRec = {
1,1,LU_GEN_OP_NOT,LSS_NOT_01__1_1,
&arNot01__1_1InDataDsc[0]
};
//Not02__1_1 ,
const LUShcemasInDataDsc arNot02__1_1InDataDsc[1] = {
LSS_NAME_LSSIN, 0
};
const LedShcemasDscRecord Not02__1_1DscRec = {
1,1,LU_GEN_OP_NOT,LSS_NOT_02__1_1,
&arNot02__1_1InDataDsc[0]
};
//Not03__1_1 ,
const LUShcemasInDataDsc arNot03__1_1InDataDsc[1] = {
LSS_NAME_LSSIN, 0
};
const LedShcemasDscRecord Not03__1_1DscRec = {
1,1,LU_GEN_OP_NOT,LSS_NOT_03__1_1,
&arNot03__1_1InDataDsc[0]
};
//Not04__1_1 ,
const LUShcemasInDataDsc arNot04__1_1InDataDsc[1] = {
LSS_NAME_LSS_D, 0
};
const LedShcemasDscRecord Not04__1_1DscRec = {
1,1,LU_GEN_OP_NOT,LSS_NOT_04__1_1,
&arNot04__1_1InDataDsc[0]
};
//Delay05__1_1 ,
const LUShcemasInDataDsc arDelay05__1_1InDataDsc[1] = {
IN_LSS_LSSIN1, 0
};
const LedShcemasDscRecord Delay05__1_1DscRec = {
1,1,LU_GEN_OP_PULSE,LSS_DELAY_05_1_1,
&arDelay05__1_1InDataDsc[0]
};
//Delay06__1_1 ,
const LUShcemasInDataDsc arDelay06__1_1InDataDsc[1] = {
LSS_NOT_01__1_1, 0
};
const LedShcemasDscRecord Delay06__1_1DscRec = {
1,1,LU_GEN_OP_PULSE,LSS_DELAY_06_1_1,
&arDelay06__1_1InDataDsc[0]
};
const LUShcemasInDataDsc arOr_07__2_1InDataDsc[2] = {
{IN_TRIGGER_SELECTOR, 0},{IN_PERIOD_SELECTOR,0}//not Led In
};
const LedShcemasDscRecord Or_07__2_1DscRec = {
2,1,LU_GEN_OP_OR,LSS_OR_07__2_1,
&arOr_07__2_1InDataDsc[0]
};
//Not08__1_1 ,
const LUShcemasInDataDsc arNot08__1_1InDataDsc[1] = {
IN_LSS_BLOCK_I, 0
};
const LedShcemasDscRecord Not08__1_1DscRec = {
1,1,LU_GEN_OP_NOT,LSS_NOT_08__1_1,
&arNot08__1_1InDataDsc[0]
};
//Not09__1_1 ,
const LUShcemasInDataDsc arNot09__1_1InDataDsc[1] = {
LSS_NAME_LSSIN_IMP, 0
};
const LedShcemasDscRecord Not09__1_1DscRec = {
1,1,LU_GEN_OP_NOT,LSS_NOT_09__1_1,
&arNot09__1_1InDataDsc[0]
};
const LUShcemasInDataDsc arOr_10__2_1InDataDsc[2] = {
{LSS_NAME_LSS_D, 0},{LSS_NAME_LSSIN,0}//not Led In
};
const LedShcemasDscRecord Or_10__2_1DscRec = {
2,1,LU_GEN_OP_OR,LSS_OR_10__2_1,
&arOr_10__2_1InDataDsc[0]
};
//LSS_D_TRG_11__4_2, 
const LUShcemasInDataDsc arD_TRG_11__4_2InDataDsc[4] = {
{IN_LSS_GROUND,0},//Set
{LSS_OR_14__3_1,0},//Clr
{IN_LSS_VCC,0},//D
{LSS_NAME_LSSIN_IMP, 0}//C
};
const LedShcemasDscRecord D_TRG_11__3_2DscRec = {
4,2,LU_GEN_OP_D_TRIGGER,LSS_D_TRG_11__4_2,
&arD_TRG_11__4_2InDataDsc[0]
}; 
//And12__3_1 ,
const LUShcemasInDataDsc arAnd12__3_1InDataDsc[3] = {
{LSS_NAME_LSS_D, 0},{LSS_NOT_09__1_1,0},{IN_PERIOD_SELECTOR,0}
};

const LedShcemasDscRecord And12__3_1DscRec = {
3,1,LU_GEN_OP_AND,LSS_AND_12__3_1,
&arAnd12__3_1InDataDsc[0]
};
//Delay13__1_1 ,
const LUShcemasInDataDsc arDelay13__1_1InDataDsc[1] = {
LSS_AND_12__3_1, 0
};
const LedShcemasDscRecord Delay13__1_1DscRec = {
1,1,LU_GEN_OP_DELAY1,LSS_DELAY_13__1_1,
&arDelay13__1_1InDataDsc[0]
};
const LUShcemasInDataDsc arOr_14__3_1InDataDsc[3] = {
{LSS_DELAY_13__1_1, 0},{IN_LSS_RESET_I,0},{LSS_NAME_NORMAL,0}
};
const LedShcemasDscRecord Or_14__3_1DscRec = {
3,1,LU_GEN_OP_OR,LSS_OR_14__3_1,
&arOr_14__3_1InDataDsc[0]
};
//And15__3_1 ,
const LUShcemasInDataDsc arAnd15__3_1InDataDsc[3] = {
{LSS_DELAY_06_1_1, 0},{LSS_NAME_TIME_TR,0},{LSS_NAME_LSSIN,0}
};

const LedShcemasDscRecord And15__3_1DscRec = {
3,1,LU_GEN_OP_AND,LSS_AND_15__3_1,
&arAnd15__3_1InDataDsc[0]
};
//And16__3_1 ,
const LUShcemasInDataDsc arAnd16__3_1InDataDsc[3] = {
{LSS_NAME_LSS_D, 0},{LSS_NAME_TIME_TR,0},{IN_LSS_MUTE_I,0}
};

const LedShcemasDscRecord And16__3_1DscRec = {
3,1,LU_GEN_OP_AND,LSS_AND_16__3_1,
&arAnd16__3_1InDataDsc[0]
};
//And17__3_1 ,
const LUShcemasInDataDsc arAnd17__3_1InDataDsc[3] = {
{LSS_NAME_LSSIN, 0},{LSS_NAME_NORMAL,0},{IN_LSS_MUTE_I,0}
};

const LedShcemasDscRecord And17__3_1DscRec = {
3,1,LU_GEN_OP_AND,LSS_AND_17__3_1,
&arAnd17__3_1InDataDsc[0]
};
//And18__2_1 ,
const LUShcemasInDataDsc arAnd18__2_1InDataDsc[2] = {
{LSS_NOT_02__1_1, 0},{LSS_NAME_NORMAL,0}
};

const LedShcemasDscRecord And18__2_1DscRec = {
2,1,LU_GEN_OP_AND,LSS_AND_18__2_1,
&arAnd18__2_1InDataDsc[0]
};
//And19__2_1 ,
const LUShcemasInDataDsc arAnd19__2_1InDataDsc[2] = {
{LSS_NAME_LSSIN_IMP, 0},{LSS_NAME_TIME_TR,0}
};

const LedShcemasDscRecord And19__2_1DscRec = {
2,1,LU_GEN_OP_AND,LSS_AND_19__2_1,
&arAnd19__2_1InDataDsc[0]
};
//And20__3_1 ,
const LUShcemasInDataDsc arAnd20__3_1InDataDsc[3] = {
{LSS_NOT_03__1_1, 0},{LSS_NOT_04__1_1,0},{LSS_NAME_TIME_TR,0}
};

const LedShcemasDscRecord And20__3_1DscRec = {
3,1,LU_GEN_OP_AND,LSS_AND_20__3_1,
&arAnd20__3_1InDataDsc[0]
}; 
//Or21__3_1
const LUShcemasInDataDsc arOr_21__3_1InDataDsc[3] = {
{LSS_AND_15__3_1, 0},{LSS_AND_16__3_1,0},{LSS_AND_17__3_1,0}
};
const LedShcemasDscRecord Or_21__3_1DscRec = {
3,1,LU_GEN_OP_OR,LSS_OR_21__3_1,
&arOr_21__3_1InDataDsc[0]
};
//Or22__3_1
const LUShcemasInDataDsc arOr_22__3_1InDataDsc[3] = {
{LSS_AND_18__2_1, 0},{LSS_AND_19__2_1,0},{LSS_AND_20__3_1,0}
};
const LedShcemasDscRecord Or_22__3_1DscRec = {
3,1,LU_GEN_OP_OR,LSS_OR_22__3_1,
&arOr_22__3_1InDataDsc[0]
};
//And23__4_1 ,
const LUShcemasInDataDsc arAnd23__4_1InDataDsc[4] = {
{LSS_NAME_NORMAL, 0},{LSS_NAME_LSSIN,0},
{LSS_NAME_BLOCK_INV,0},{LSS_NAME_MUTE_INV,1}
};

const LedShcemasDscRecord And23__4_1DscRec = {
4,1,LU_GEN_OP_AND,LSS_AND_23__4_1,
&arAnd23__4_1InDataDsc[0]
};
//And24__4_1 ,
const LUShcemasInDataDsc arAnd24__4_1InDataDsc[4] = {
{LSS_NAME_NORMAL, 0},{LSS_NAME_LSSIN,0},
{LSS_NAME_BLOCK_INV,0},{LSS_NAME_MUTE_DIR,0}
};

const LedShcemasDscRecord And24__4_1DscRec = {
4,1,LU_GEN_OP_AND,LSS_AND_24__4_1,
&arAnd24__4_1InDataDsc[0]
};
//And25__4_1 ,
const LUShcemasInDataDsc arAnd25__4_1InDataDsc[4] = {
{LSS_OR_07__2_1, 0},{LSS_NAME_LSS_D,0},
{LSS_NAME_BLOCK_INV,0},{LSS_NAME_MUTE_INV,1}
};

const LedShcemasDscRecord And25__4_1DscRec = {
4,1,LU_GEN_OP_AND,LSS_AND_25__4_1,
&arAnd25__4_1InDataDsc[0]
};
//And26__4_1 ,
const LUShcemasInDataDsc arAnd26__4_1InDataDsc[4] = {
{LSS_OR_07__2_1, 0},{LSS_OR_10__2_1,0},
{LSS_NAME_BLOCK_INV,0},{LSS_NAME_MUTE_DIR,0}
};

const LedShcemasDscRecord And26__4_1DscRec = {
4,1,LU_GEN_OP_AND,LSS_AND_26__4_1,
&arAnd26__4_1InDataDsc[0]
};

//----
const LUShcemasInDataDsc arOr_27__2_1InDataDsc[2] = {
{LSS_AND_23__4_1, 0},{LSS_AND_25__4_1,0}//not Led In
};
const LedShcemasDscRecord Or_27__2_1DscRec = {
2,1,LU_GEN_OP_OR,LSS_OR_27__2_1,
&arOr_27__2_1InDataDsc[0]
};
const LUShcemasInDataDsc arOr_28__2_1InDataDsc[2] = {
{LSS_AND_24__4_1, 0},{LSS_AND_26__4_1,0}//not Led In
};
const LedShcemasDscRecord Or_28__2_1DscRec = {
2,1,LU_GEN_OP_OR,LSS_OR_28__2_1,
&arOr_28__2_1InDataDsc[0]
};
//LSS_D_TRG_29__4_2, 
const LUShcemasInDataDsc arD_TRG_29__4_2InDataDsc[4] = {
{IN_LSS_GROUND,0},//Set
{LSS_OR_22__3_1,0},//Clr
{IN_LSS_VCC,0},//D
{LSS_OR_21__3_1, 0}//C
};
const LedShcemasDscRecord D_TRG_29__4_2DscRec = {
4,2,LU_GEN_OP_D_TRIGGER,LSS_D_TRG_29__4_2,
&arD_TRG_29__4_2InDataDsc[0]
}; 

const LedShcemasDscRecord* const arPLssShcemasDscRecords[] = {
&Or_07__2_1DscRec   ,
&Delay05__1_1DscRec ,
&Not09__1_1DscRec   ,
&And12__3_1DscRec   ,
&Delay13__1_1DscRec ,
&Or_14__3_1DscRec   ,
&D_TRG_11__3_2DscRec,
&Not01__1_1DscRec,
&Not02__1_1DscRec   ,
&Not03__1_1DscRec   ,
&Not04__1_1DscRec   ,

&Delay06__1_1DscRec ,

&Not08__1_1DscRec   ,

&Or_10__2_1DscRec   ,




&And15__3_1DscRec   ,
&And16__3_1DscRec   ,
&And17__3_1DscRec   ,
&And18__2_1DscRec   ,
&And19__2_1DscRec   ,
&And20__3_1DscRec   ,
&Or_21__3_1DscRec   ,
&Or_22__3_1DscRec   ,
&D_TRG_29__4_2DscRec,
&And23__4_1DscRec   ,
&And24__4_1DscRec   ,
&And25__4_1DscRec   ,
&And26__4_1DscRec   ,
&Or_27__2_1DscRec   ,
&Or_28__2_1DscRec   

};

#endif

