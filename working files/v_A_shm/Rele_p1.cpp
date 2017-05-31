#ifndef LU_RELE_SCHEMATIC_DSC_CONST_C
#define LU_RELE_SCHEMATIC_DSC_CONST_C


const short arReleShOffsets[TOTAL_RELE_LU_CALC_POINT ] = {
OFFSET_OUT_RELE_Not01__1_1, 
OFFSET_OUT_RELE_And02__2_1, 
OFFSET_OUT_RELE_And03__2_1, 
OFFSET_OUT_RELE_And04__2_1, 
OFFSET_OUT_RELE_Or_05__2_1, 
OFFSET_OUT_RELE_D_TRG_06__2_2,
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

//RELE_Not01__1_1, 
const LUShcemasInDataDsc arNot01__1_1InDataDsc[1] = {
IN_RELE__RIN, 0
};
const LedShcemasDscRecord Not01__1_1DscRec = {
1,1,LU_GEN_OP_NOT,RELE_Not01__1_1,
&arNot01__1_1InDataDsc[0]
};
//RELE_And02__2_1, 
const LUShcemasInDataDsc arAnd02__2_1InDataDsc[2] = {
{RELE_Not01__1_1, 0},{IN_RELE__RESET,0}
};

const LedShcemasDscRecord And02__2_1DscRec = {
2,1,LU_GEN_OP_AND,RELE_And02__2_1,
&arAnd02__2_1InDataDsc[0]
};

//RELE_And03__2_1, 
const LUShcemasInDataDsc arAnd03__2_1InDataDsc[2] = {
{IN_RELE__RIN, 0},{IN_RELE_NORMAL_SELECTOR,0}
};

const LedShcemasDscRecord And03__2_1DscRec = {
2,1,LU_GEN_OP_AND,RELE_And03__2_1, 
&arAnd03__2_1InDataDsc[0]
};

//RELE_And04__2_1, 
const LUShcemasInDataDsc arAnd04__2_1InDataDsc[2] = {
{IN_RELE__RIN, 0},{IN_RELE_TRIGGER_SELECTOR,0}
};

const LedShcemasDscRecord And04__2_1DscRec = {
2,1,LU_GEN_OP_AND,RELE_And04__2_1,
&arAnd04__2_1InDataDsc[0]
};

//RELE_Or_05__2_1, 
const LUShcemasInDataDsc arOr_05__2_1InDataDsc[2] = {
{IN_RELE_NORMAL_SELECTOR, 0},{RELE_And02__2_1,0}//not Led In
};
const LedShcemasDscRecord Or_05__2_1DscRec = {
2,1,LU_GEN_OP_OR,RELE_Or_05__2_1,
&arOr_05__2_1InDataDsc[0]
}; 
//RELE_D_TRG_06__4_2, 
const LUShcemasInDataDsc arD_TRG_06__4_2InDataDsc[4] = {
{IN_RELE_GROUND,0},//Set
{RELE_Or_05__2_1,0},//Clr
{IN_RELE_VCC,0},//D
{RELE_And04__2_1, 0}//C
//{IN_VCC,0},{IN_VCC,0},{RELE_And04__2_1,0},{RELE_Or_05__2_1, 0}
};
const LedShcemasDscRecord D_TRG_06__4_2DscRec = {
4,2,LU_GEN_OP_D_TRIGGER,RELE_D_TRG_06__2_2,
&arD_TRG_06__4_2InDataDsc[0]
};
//RELE_Or_07__2_1, 
const LUShcemasInDataDsc arOr_07__2_1InDataDsc[2] = {
{IN_RELE_PULSE_SIMPLE_SELECTOR, 0},{IN_RELE_PULSE_EXTANDED_SELECTOR,0}//not Led In
};
const LedShcemasDscRecord Or_07__2_1DscRec = {
2,1,LU_GEN_OP_OR,RELE_Or_07__2_1,
&arOr_07__2_1InDataDsc[0]
};
//RELE_And08__2_1, 
const LUShcemasInDataDsc arAnd08__2_1InDataDsc[2] = {
{IN_RELE__BL_IMP, 0},{IN_RELE_PULSE_SELECTOR,0}
};

const LedShcemasDscRecord And08__2_1DscRec = {
2,1,LU_GEN_OP_AND,RELE_And08__2_1,
&arAnd08__2_1InDataDsc[0]
};
 
//RELE_Or_09__2_1, 
const LUShcemasInDataDsc arOr_09__2_1InDataDsc[2] = {
{RELE_And03__2_1, 0},{RELE_D_TRG_06__2_2,0}//not Led In
};
const LedShcemasDscRecord Or_09__2_1DscRec = {
2,1,LU_GEN_OP_OR,RELE_Or_09__2_1,
&arOr_09__2_1InDataDsc[0]
};
//RELE_And10__2_1, 
const LUShcemasInDataDsc arAnd10__2_1InDataDsc[2] = {
{IN_RELE_PULSE_EXTANDED_SELECTOR, 0},{IN_RELE__C1_C2,0}//not Led In
};
const LedShcemasDscRecord And10__2_1DscRec = {
2,1,LU_GEN_OP_AND,RELE_And10__2_1,
&arAnd10__2_1InDataDsc[0]
};
//RELE_And11__2_1,
const LUShcemasInDataDsc arAnd11__2_1InDataDsc[2] = {
{IN_RELE_STABLE_SELECTOR, 0},{RELE_Or_09__2_1,0}//not Led In
};
const LedShcemasDscRecord And11__2_1DscRec = {
2,1,LU_GEN_OP_AND,RELE_And11__2_1,
&arAnd11__2_1InDataDsc[0]
};
//RELE_And12__2_1,
const LUShcemasInDataDsc arAnd12__2_1InDataDsc[2] = {
{IN_RELE_PULSE_SELECTOR, 0},{RELE_Or_09__2_1,0}//not Led In
};
const LedShcemasDscRecord And12__2_1DscRec = {
2,1,LU_GEN_OP_AND,RELE_And12__2_1,
&arAnd12__2_1InDataDsc[0]
};
//RELE_Or_13__2_1,
const LUShcemasInDataDsc arOr_13__2_1InDataDsc[2] = {
{IN_RELE_C1, 0},{RELE_And08__2_1,0}//not Led In
};
const LedShcemasDscRecord Or_13__2_1DscRec = {
2,1,LU_GEN_OP_OR,RELE_Or_13__2_1,
&arOr_13__2_1InDataDsc[0]
};
//RELE_Or_14__2_1,
const LUShcemasInDataDsc arOr_14__2_1InDataDsc[2] = {
{IN_RELE_C2, 0},{RELE_And08__2_1,0}//
};
const LedShcemasDscRecord Or_14__2_1DscRec = {
2,1,LU_GEN_OP_OR,RELE_Or_14__2_1,
&arOr_14__2_1InDataDsc[0]
};
//RELE_Not15__1_1,
const LUShcemasInDataDsc arNot15__1_1InDataDsc[1] = {
{RELE_And10__2_1, 0}
};
const LedShcemasDscRecord Not15__1_1DscRec = {
1,1,LU_GEN_OP_NOT,RELE_Not15__1_1,
&arNot15__1_1InDataDsc[0]
};
//RELE_And16__3_1,
const LUShcemasInDataDsc arAnd16__3_1InDataDsc[3] = {
{RELE_And12__2_1, 0},{RELE_Or_13__2_1,0},{RELE_Not15__1_1,0}//not Led In
};
const LedShcemasDscRecord And16__3_1DscRec = {
3,1,LU_GEN_OP_AND,RELE_And16__3_1,
&arAnd16__3_1InDataDsc[0]
};
//RELE_And17__3_1,
const LUShcemasInDataDsc arAnd17__3_1InDataDsc[3] = {
{RELE_And12__2_1, 0},{RELE_Or_14__2_1,0},{RELE_And10__2_1,0}//not Led In
};
const LedShcemasDscRecord And17__3_1DscRec = {
3,1,LU_GEN_OP_AND,RELE_And17__3_1,
&arAnd17__3_1InDataDsc[0]
};
//RELE_Or18__3_1,
const LUShcemasInDataDsc arOr18__3_1InDataDsc[3] = {
{RELE_And11__2_1, 0},{RELE_And16__3_1,0},{RELE_And17__3_1,0}//not Led In
};
const LedShcemasDscRecord Or18__3_1DscRec = {
3,1,LU_GEN_OP_OR,RELE_Or_18__3_1,
&arOr18__3_1InDataDsc[0]
};
//IN_RELE_NORMAL_SELECTOR,

//IN_RELE_TRIGGER_SELECTOR,

//IN_RELE_STABLE_SELECTOR,

//IN_RELE_PULSE_SELECTOR,

//IN_RELE_PULSE_SIMPLE_SELECTOR,

//IN_RELE_PULSE_EXTANDED_SELECTOR,

//IN_RELE__RIN ,

//IN_RELE__RESET,

//IN_RELE__BL_IMP,

//IN_RELE__C1_C2,
const LedShcemasDscRecord* const arPReleShcemasDscRecords[] = {
&Not01__1_1DscRec,
&And02__2_1DscRec,
&And03__2_1DscRec,
&And04__2_1DscRec,
&Or_05__2_1DscRec,
&D_TRG_06__4_2DscRec,
&Or_07__2_1DscRec,
&And08__2_1DscRec,
&Or_09__2_1DscRec,
&And10__2_1DscRec,
&And11__2_1DscRec,
&And12__2_1DscRec,
&Or_13__2_1DscRec,
&Or_14__2_1DscRec,
&Not15__1_1DscRec,
&And16__3_1DscRec,
&And17__3_1DscRec,
&Or18__3_1DscRec 
};
//
const short shAmtDOShcemasDscRecords  = sizeof(arPReleShcemasDscRecords)
/sizeof(LedShcemasDscRecord*);
const LedShcemasDscRecord* const arPDOShcemasStableDirectDscRecords[] = {
&And03__2_1DscRec,
&Or_09__2_1DscRec,
&And11__2_1DscRec,
&Or18__3_1DscRec 
};
const short shAmtDOShcemasStableSimpleDscRecords  = sizeof(arPDOShcemasStableDirectDscRecords)
/sizeof(LedShcemasDscRecord*); 

const LedShcemasDscRecord* const arPDOShcemasStableTriggerDscRecords[] = {
&Not01__1_1DscRec,
&And02__2_1DscRec,
&And04__2_1DscRec,
&Or_05__2_1DscRec,
&D_TRG_06__4_2DscRec,
&Or_09__2_1DscRec,
&And11__2_1DscRec,
&Or18__3_1DscRec 
}; 
const short shAmtDOShcemasStableTriggerDscRecords  = sizeof(arPDOShcemasStableTriggerDscRecords)
/sizeof(LedShcemasDscRecord*);

const LedShcemasDscRecord* const arPDOShcemasPulseC1SimpleDscRecords[] = {
&And03__2_1DscRec,
&And08__2_1DscRec,
&Or_09__2_1DscRec,
&And12__2_1DscRec,
&Or_13__2_1DscRec,
&And10__2_1DscRec,
&Not15__1_1DscRec,
&And16__3_1DscRec,
&Or18__3_1DscRec 
}; 
const short shAmtDOShcemasPulseC1SimpleModeDscRecords  = sizeof(arPDOShcemasPulseC1SimpleDscRecords)
/sizeof(LedShcemasDscRecord*);

const LedShcemasDscRecord* const arPDOShcemasPulseC1TrigDscRecords[] = {
&Not01__1_1DscRec,
&And02__2_1DscRec,
&And04__2_1DscRec,
&Or_05__2_1DscRec,
&D_TRG_06__4_2DscRec,
&Or_09__2_1DscRec,
&And08__2_1DscRec,

&And12__2_1DscRec,
&Or_13__2_1DscRec,
&And10__2_1DscRec,
&Not15__1_1DscRec,
&And16__3_1DscRec,
&Or18__3_1DscRec 
}; 
const short shAmtDOShcemasPulseC1TrigModeDscRecords  = sizeof(arPDOShcemasPulseC1TrigDscRecords)
/sizeof(LedShcemasDscRecord*);

const LedShcemasDscRecord* const arPDOShcemasPulseC2TrigDscRecords[] = {
&Not01__1_1DscRec,
&And02__2_1DscRec,
&And04__2_1DscRec,
&Or_05__2_1DscRec,
&D_TRG_06__4_2DscRec,
&Or_09__2_1DscRec,
&And08__2_1DscRec,

&And12__2_1DscRec,
&Or_14__2_1DscRec,
&And10__2_1DscRec,

&And17__3_1DscRec,
&Or18__3_1DscRec 
}; 
const short shAmtDOShcemasPulseC2TrigModeDscRecords  = sizeof(arPDOShcemasPulseC2TrigDscRecords)
/sizeof(LedShcemasDscRecord*); 

const LedShcemasDscRecord* const arPDOShcemasPulseC2SimpleDscRecords[] = {
&And03__2_1DscRec,
&And08__2_1DscRec,
&Or_09__2_1DscRec,
&And12__2_1DscRec,
&Or_14__2_1DscRec,
&And10__2_1DscRec,

&And17__3_1DscRec,
&Or18__3_1DscRec 
}; 
const short shAmtDOShcemasPulseC2SimpleModeDscRecords  = sizeof(arPDOShcemasPulseC2SimpleDscRecords)
/sizeof(LedShcemasDscRecord*);
 
#endif
