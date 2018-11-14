#ifndef LU_BGS_SCHEMATIC_DSC_CONST_C
#define LU_BGS_SCHEMATIC_DSC_CONST_C
enum BGS_OrderEvaluation{
PO_DeltaIbus             ,
Menu_Ctrl_BGS_State      ,
Menu_Ctrl_BGS_State_Inv  ,
DTrg                     ,
Imp1Ms                   ,
And4                     ,
PO_Ifix                  ,
PO_DeltaIbusFix          ,
PO_DeltaIbusFixInv       ,
And8                     ,
OR9                      ,
Delay1ms                 ,
DelayWait                ,
Imp6ms                   ,
PoIp                     ,
PoIc                     ,
And14                    ,
And15                    ,
And16                    ,
And17                    ,
PO_NNC_NCH               ,
PO_NNP_NCH               ,
PO_NNC_CH                ,
PO_NNP_CH                ,
PO_CE                    ,
PO_OC                    ,
Mux24                    ,
Mux25                    ,
Not26                    ,
PO_NNP                   ,
PO_NNM                   ,
PO_NCC                   ,
And30                    ,
And31                    ,
And32                    ,
iMP100msNNP              ,
iMP100msNNM              ,
And35,
And36,
And37

};

/*
const short arShOffsets[TOTAL_BGS_LU_CALC_POINT] = {

OFFSET_OUT_BGS_EvalDeltaIbus_1,
OFFSET_OUT_BGS_StoreIfixTimeFix_1,
OFFSET_OUT_BGS_D_TRG_03__3_2,
OFFSET_OUT_BGS_TIMER_04_1_1,
OFFSET_OUT_BGS_OR_05__2_1,
OFFSET_OUT_BGS_And06__2_1,
OFFSET_OUT_BGS_Not07__1_1,
OFFSET_OUT_BGS_EvalDeltaIbusFix_3_1,
OFFSET_OUT_BGS_TDELAY_1_1,
OFFSET_OUT_BGS_Not10__1_1,
OFFSET_OUT_BGS_And11__2_1,
OFFSET_OUT_BGS_And12__2_1,
OFFSET_OUT_BGS_And13__2_1,
OFFSET_OUT_BGS_And14__2_1,
OFFSET_OUT_BGS_EvalNNC_NCH_1,
OFFSET_OUT_BGS_EvalNNP_NCH_1,
OFFSET_OUT_BGS_EvalNNC_CH_1 ,
OFFSET_OUT_BGS_EvalNNP_CH_1 ,
OFFSET_OUT_BGS_EvalCE_1,
OFFSET_OUT_BGS_EvalOC_1,
OFFSET_OUT_BGS_EvalIptp_1, 
OFFSET_OUT_BGS_EvalIctc_1,
OFFSET_OUT_BGS_MUX21_3_1,
OFFSET_OUT_BGS_MUX22_3_1,
OFFSET_OUT_BGS_EvalNNP_1,
OFFSET_OUT_BGS_EvalNNM_1,
OFFSET_OUT_BGS_EvalNCC_1,
TOTAL_BGS_LU_CALC_POINT
};


//RS_12__2_2 ,
const LUShcemasInDataDsc arDTrg_03__3_2InDataDsc[3] = {
{BGS_VCC, 0},{EvalDeltaIbus_1, 0},{BGS_TIMER_04_1_1,0}//not Led In
};
const LUShcemasDscRecord DTrg_03__3_2DscRec = {
3,2,LU_GEN_OP_D_TRIGGER_TYPE3,
&arDTrg_03__3_2InDataDsc[0]
}; 

//OR_05__2_1 ,
const LUShcemasInDataDsc arOr_05__2_1InDataDsc[2] = {
{BGS_And06__2_1, 0},{BGS_TDELAY_1_1,0}//not Led In
};
const LUShcemasDscRecord Or_05__2_1DscRec = {
2,1,LU_GEN_OP_OR,
&arOr_05__2_1InDataDsc[0]
}; 
//And06__2_1 ,
const LUShcemasInDataDsc arAnd06__2_1InDataDsc[2] = {
{BGS_Not07__1_1, 0},{BGS_Not07__1_1,0}
};
const LUShcemasDscRecord And06__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd06__2_1InDataDsc[0]
};

const LUShcemasInDataDsc arNot07__1_1InDataDsc[1] = {
BGS_EvalDeltaIbusFix_3_1, 0
};
const LUShcemasDscRecord Not07__1_1DscRec = {
1,1,LU_GEN_OP_NOT,
&arNot07__1_1InDataDsc[0]
};

const LUShcemasInDataDsc EvDeltaIbusFix_3_1InDataDsc[1] = {
BGS_D_TRG_03__3_2, 0
};
const LUShcemasDscRecord EvDeltaIbusFix_3_1DscRec = {
1,1,LU_GEN_OP_EV_FIX_IBUS,
&arNot07__1_1InDataDsc[0]
};

//Not10__1_1,
const LUShcemasInDataDsc arNot10__1_1InDataDsc[1] = {
IN_BGS_MNU_STATE_CHECK_BGS_SELECTOR, 0
};
const LUShcemasDscRecord Not10__1_1DscRec = {
1,1,LU_GEN_OP_NOT,
&arNot10__1_1InDataDsc[0]
};


//And11__2_1 ,
const LUShcemasInDataDsc arAnd11__2_1InDataDsc[2] = {
{BGS_Not10__1_1, 0},{BGS_TDELAY_1_1,0}//not Led In
};
const LUShcemasDscRecord And11__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd11__2_1InDataDsc[0]
};
//And12__2_1 ,
const LUShcemasInDataDsc arAnd12__2_1InDataDsc[2] = {
{BGS_TDELAY_1_1, 0},{BGS_Not10__1_1,0}//not Led In
};
const LUShcemasDscRecord And12__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd12__2_1InDataDsc[0]
};  

//And13__2_1 ,
const LUShcemasInDataDsc arAnd13__2_1InDataDsc[2] = {
{BGS_TDELAY_1_1, 0},{BGS_Not10__1_1,0}//not Led In
};
const LUShcemasDscRecord And13__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd13__2_1InDataDsc[0]
};
//And14__2_1 ,
const LUShcemasInDataDsc arAnd14__2_1InDataDsc[2] = {
{BGS_TDELAY_1_1, 0},{BGS_Not10__1_1,0}//not Led In
};
const LUShcemasDscRecord And14__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd14__2_1InDataDsc[0]
};  

Фиксирую состояние всех входов всех компонентов схемы.
Создаю список всех элементов
Создаю список входов состояние которых определено.
Анализирую входы каждого элемента.
Если все они из списка состояние которых определено заношу элемент в список
просчета.
Выход этого элемента заношу в список входов состояние которых определено.
Попадаю на обратную связь. Т.е.Вход элемента зависит от состояния другого.
Тот в свою очередь может зависить от состояния уже рассматриваемого.
Тогда заношу выход этого элемента в список повторных.А сам выход заношу 
в список уже просчитанных элементов. И элемент добавляю в 
список всех элементов. И в список повторно просчитываемых.
Формирую битовую цепочку всех выходов состояния просчитан/непросчитан.
На итерации просто сначала определяю состояние всех "константных" входов
На основе предыдущего состояния Просчитываю состояние всех зависимых
Затем повторяю линейный просчет.Можно провести просчет 2р для анализа
наличия неустановившегося состояния(генераторной схемы)
Нужен ли просчет более 2р?
На эту идею составь возможную схему реализации
*/

#endif

