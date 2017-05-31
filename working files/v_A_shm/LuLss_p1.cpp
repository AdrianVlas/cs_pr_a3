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
/*
Normal
  Or27,Or28
  And23,And24
 And23(NormalSelector, LSSIN, Block-Inv, Mute-Inv) 
 NormalSelector -> End
 LSSIN -> Input-> End
Block-Inv ->Not8
Mute-Inv ->Trg29

Not8
Trg29

Not8 ->Block-I Signal
Trg29(Or21,Or22);
Or21(And15==0,And16==0,And17)
And17(NormalSelector, LSSIN, MUTE-I)
Or22(And18,And19==0,And20 == 0)
And18(Not2,NormalSelector)
Not2(LSSIN)

And24(NormalSelector, LSSIN, Block-Inv, Mute-Dir) 
 NormalSelector -> End
 LSSIN -> Input-> End
 Block-Inv ->Not8
Mute-Dir ->Trg29
Not8 ->Block-I Signal
Trg29(Or21,Or22);
Calculated List
======================================================
LSSIN^,Mute-I^,Block-I^,
Not8,
 And17,And18
Or21,Or22 
Trg29
And23,And24
Or27,Or28
*/
const LedShcemasDscRecord* const arPLssShcemasSimpleModeDscRecords[] = {
&Not08__1_1DscRec   ,
&And17__3_1DscRec   ,
&And18__2_1DscRec   ,
&Or_21__3_1DscRec   ,
&Or_22__3_1DscRec   ,
&D_TRG_29__4_2DscRec,
&And23__4_1DscRec   ,
&And24__4_1DscRec   ,
&Or_27__2_1DscRec   ,
&Or_28__2_1DscRec   

};
const short shPLssShcemasSimpleModeDscRecords = 
sizeof(arPLssShcemasSimpleModeDscRecords)
/sizeof(LedShcemasDscRecord*);
/*
TriggerMode
Alarm Link
Or27
Mute Link
TriggerMode
Alarm Link
Or27->(And23==0<-Ign),And25->Or7,Trg11-1,Not8,Trg29-2,OnTimesignal^,
TriggerSignal^,Delay05__1_1,Or14,Block-I Signal^,Or21,Or22,LSSIN,
TCs13,NormalSelector^,Reset-I^,And15,And16,(And17==0<-Ign)^,
(And18==0<-Ign)^,And19,And20,And12,Delay06__1_1,XOr7X,XLSSINX,
XTrg11-1X,XOr7X,MUTE-I^,XDelay05__1_1X,XOr7X,Not3,Not4,XOr7X,
XTrg11-1X,Not9,OnTimesignal^,>>Not1<<,XLSSINX,XLSSINX,XTrg11-1X,
XDelay05__1_1X,XTrg11-1X.

Mute Link
Or28->(And24==0<-Ign),And26,Or7,Or10,Not8,Trg29-2,OnTimesignal^,
TriggerSignal^,Trg11-1,LSSIN^,Block-I Signal^,Or21,Or22,Delay05__1_1,
Or14,And15,And16,(And17==0<-Ign)^,(And18==0<-Ign)^,And19,And20,
XLSSINX,>>TCs13<<,NormalSelector^,Reset-I^,Delay06__1_1,XOr7X,XLSSINX,
XTrg11-1X,XOr7X,MUTE-I^,XDelay05__1_1X,XOr7X,Not3,Not4,XOr7X,And12,
Not1,XLSSINX,XTrg11-1X,
XTrg11-1X,>>Not9<<,XOnTimesignalX,XTrg11-1X,XDelay05__1_1X.

Mute Link -- После изъятия элементов
Or28->(And24==0<-Ign),And26,


And16--,(And17==0<-Ign)^,(And18==0<-Ign)^,
XLSSINX,>><<,XOr7X,

XLSSINX,
XTrg11-1X,XOr7X,XOr7X,Not4--,XOr7X,And12--,
Not1--
,XLSSINX,XTrg11-1X,
XTrg11-1X,XOnTimesignalX,XTrg11-1X,XDelay05__1_1X.
MUTE-I^
Reset-I^,
NormalSelector^,
Block-I Signal^,
LSSIN^,
TriggerSignal^,
OnTimesignal^,
Not3,
Delay05__1_1,
Not8,
Or7,
And19,
Not9,
//---------------------------------
Not1 And12 Not4 And16 - зависят от Trg11-1, а они от Trg11-1 это петли
Остальные элементы зависят от находящихся перед ними 
Поэтому есть смысл брать старое значение Trg11-1
//```````````````````````````````````````````````````
//Разрезание петель особая тема к-я требует своего
//подхода пока рекомендация производить разрезание
//по принципу первым изымается тот кто ближе к началу
//иерархии
//Взагалі то краще елементи петель виділити в окремий блок 
//і всі елементи, які належать до петель виділи в окремий список
//аналізу, і його(список) потім перераховувати цей список окремо. 
//відповідно це все має включатись в лічильник ресурсів. Тобто час
//на аналіз(ресурси) петель потрібно закладати в розрахунок схем
//Відповідно, якщо стан петель на 2-й ітерації не змінився, схема 
//в стабільному стані.

//елементи петлі--
<Loop> = And12, TCs13,Or14,Trg11-1,
//------------------------------------------------------------------
Not1
And12<<--Loop
Not4
And16

Delay06__1_1,
TCs13<<-Loop
And20,
And15,
Or14,<<-Loop
Or21,
Or22,
Trg11-1,<<--Loop
Trg29-2,
Or10,
And26,

  Or27,Or28
  And25,And26
 And25( TimeTriggerSelector, LSS-D, Block-Inv, Mute-Inv) 
 TimeTriggerSelector -> End
 LSS-D -> Trg11
 Block-Inv ->Not8
 Mute-Inv ->Trg29
Or7
Trg11
Not8
Trg29

  Or7(OnTimesignal,TriggerSignal)->
  Not8(Block-I Signal)
  Trg11(Delay5,Or14);
  Trg29(Or21,Or22);

    Trg11
      Delay5(LSSIN);
      Or14(TCs13,NormalSelector,Reset-I)
        TCs13(And12)
          And12(Trg11-0Out,Not9,OnTimesignal)
            Trg11-0Out->End
          Not9(Delay5(LSSIN)) ->Calculated
           
Trg29(Or21,Or22);
Or21(And15==0,And16==0,And17)
And17(NormalSelector, LSSIN, MUTE-I)
Or22(And18,And19==0,And20 == 0)
And18(Not2,NormalSelector)
Not2(LSSIN)

And26(TimeTriggerSelector, OR10, Block-Inv, Mute-Dir) 
 NormalSelector -> End
 LSSIN -> Input-> End
 Block-Inv ->Not8
Mute-Dir ->Trg29
Not8 ->Block-I Signal
Trg29(Or21,Or22);
*/
const LedShcemasDscRecord* const arPLssShcemasTriggerModeDscRecords[] = {
&Not03__1_1DscRec   ,
&Delay05__1_1DscRec ,
&Not08__1_1DscRec   ,
&Or_07__2_1DscRec   ,
&And19__2_1DscRec   ,
&Not09__1_1DscRec   ,

&And12__3_1DscRec   ,//Loop
&Delay13__1_1DscRec ,//Loop
&Or_14__3_1DscRec   ,//Loop
&D_TRG_11__3_2DscRec,//Loop
//Fix Loop State Operation
&Not01__1_1DscRec,
&Not04__1_1DscRec   ,
&And16__3_1DscRec   ,
&Delay06__1_1DscRec ,
&And20__3_1DscRec   ,
&And15__3_1DscRec   ,
&Or_21__3_1DscRec   ,
&Or_22__3_1DscRec   ,
&D_TRG_29__4_2DscRec,
&Or_10__2_1DscRec   ,
&And26__4_1DscRec   ,
&And25__4_1DscRec   ,

&Or_27__2_1DscRec   ,
&Or_28__2_1DscRec   

};
const short shPLssShcemasTriggerModeDscRecords = 
//PLssShcemasTriggerModeDscRecords
sizeof(arPLssShcemasTriggerModeDscRecords)
/sizeof(LedShcemasDscRecord*);
/*
const LedShcemasDscRecord* const arPLssShcemasOnTimeModeDscRecords[] = {
&Not03__1_1DscRec   ,
&Delay05__1_1DscRec ,
&Not08__1_1DscRec   ,
&Or_07__2_1DscRec   ,
&And19__2_1DscRec   ,
&Not09__1_1DscRec   ,

&And12__3_1DscRec   ,//Loop
&Delay13__1_1DscRec ,//Loop
&Or_14__3_1DscRec   ,//Loop
&D_TRG_11__3_2DscRec,//Loop
//Fix Loop State Operation
&Not01__1_1DscRec,
&Not04__1_1DscRec   ,
&And16__3_1DscRec   ,
&Delay06__1_1DscRec ,
&And20__3_1DscRec   ,
&And15__3_1DscRec   ,
&Or_21__3_1DscRec   ,
&Or_22__3_1DscRec   ,
&D_TRG_29__4_2DscRec,
&Or_10__2_1DscRec   ,
&And26__4_1DscRec   ,
&And25__4_1DscRec   ,

&Or_27__2_1DscRec   ,
&Or_28__2_1DscRec   


};
*/

#endif

