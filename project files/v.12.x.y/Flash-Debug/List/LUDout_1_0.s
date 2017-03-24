///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUDout_1_0.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUDout_1_0.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
//        USE_USB_OTG_FS -D SYSTEM_VIEWER_ENABLE -lc
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\Flash-Debug\List" -lB
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\Flash-Debug\List" --remarks -o
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\Flash-Debug\Obj" --no_cse --no_unroll --no_inline
//        --no_code_motion --no_tbaa --no_clustering --no_scheduling --debug
//        --endian=little --cpu=Cortex-M3 -e --enable_multibytes --fpu=None
//        --dlib_config G:\PRG\IAR7_50_2\arm\INC\c\DLib_Config_Full.h -I
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\..\..\working files\inc\" -I
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\..\..\working files\usb\" -I
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\..\..\Libraries\CMSIS\Device\ST\STM32F2xx\Include\" -I
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\..\..\Libraries\STM32F2xx_StdPeriph_Driver\inc\" -I
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\..\..\Libraries\STM32_USB_OTG_Driver\inc\" -I
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\..\..\Libraries\STM32_USB_Device_Library\Core\inc\" -I
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\..\..\Libraries\STM32_USB_Device_Library\Class\cdc\inc\"
//        -I "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\..\..\SystemView\Config\" -I
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\..\..\SystemView\OS\" -I
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\..\..\SystemView\SEGGER\" -On --eec++ -I
//        G:\PRG\IAR7_50_2\arm\CMSIS\Include\ -D ARM_MATH_CM3
//    List file    =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\Flash-Debug\List\LUDout_1_0.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN _ZN7CLUBaseC2Ev
        EXTERN _ZN7CLUBaseD2Ev

        PUBLIC _Z10PUT_Op_1_0Pv
        PUBLIC _Z10SET_OUT_OpPv
        PUBLIC _ZN11CLUDout_1_018CalcReleySchematicEv
        PUBLIC _ZN11CLUDout_1_0C1Ecc
        PUBLIC _ZN11CLUDout_1_0C1Ev
        PUBLIC _ZN11CLUDout_1_0C2Ecc
        PUBLIC _ZN11CLUDout_1_0C2Ev
        PUBLIC _ZN11CLUDout_1_0D1Ev
        PUBLIC _ZN11CLUDout_1_0D2Ev


        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUDout_1_0::subobject CLUDout_1_0()
_ZN11CLUDout_1_0C2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN11CLUDout_1_0C1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUDout_1_0::subobject ~CLUDout_1_0()
_ZN11CLUDout_1_0D2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN11CLUDout_1_0D1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUDout_1_0::subobject CLUDout_1_0(char, char)
_ZN11CLUDout_1_0C2Ecc:
        PUSH     {R4,LR}
        MOVS     R4,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        BL       _ZN11CLUDout_1_0C1Ecc
        POP      {R4,PC}          ;; return
// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\LUDout_1_0.cpp
//    1 #ifdef VISUAL_STUDIO
//    2 #include "StdAfx.h"
//    3 #endif
//    4 #include "LUDout_1_0.h"
//    5 
//    6 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    7 void PUT_Op_1_0    (void *pObj)
//    8 {
_Z10PUT_Op_1_0Pv:
        PUSH     {R4,LR}
        MOVS     R4,R0
//    9 CLUDout_1_0& refCLUDout_1_0 = *(static_cast<CLUDout_1_0*>(pObj));
//   10 //CLUDout_1_0 *pCLUDout_1_0 = (CLUDout_1_0*)pObj;
//   11 refCLUDout_1_0.CalcReleySchematic();
        MOVS     R0,R4
        BL       _ZN11CLUDout_1_018CalcReleySchematicEv
//   12 }
        POP      {R4,PC}          ;; return
//   13 
//   14 
//   15 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   16 CLUDout_1_0::CLUDout_1_0(void)
_ZN11CLUDout_1_0C1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   17 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   18 }
        MOVS     R0,R4
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   19 CLUDout_1_0::CLUDout_1_0(char chM,char chI)//,LUOutDsc* pLUOutDsc)
_ZN11CLUDout_1_0C1Ecc:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//   20 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   21     chMaxIteratoin = chM;
        STRB     R5,[R4, #+4]
//   22     chIteration = chI;
        STRB     R6,[R4, #+5]
//   23     chNumInput  = static_cast<char>(shCLUDout_1_0_AmtIn );
        MOVS     R0,#+1
        STRB     R0,[R4, #+6]
//   24     chNumOutput = static_cast<char>(shCLUDout_1_0_AmtOut);
        MOVS     R0,#+0
        STRB     R0,[R4, #+7]
//   25     //chTypeLogicFunction = LU_OP_SET_OUT;
//   26     //LogicFunc  = SET_OUT_Op;//???
//   27 
//   28     //Set Input parameters
//   29     //pIn = (void*)arrPchIn;
//   30     //pOut = (void*)arrOut;
//   31     //Set OutPut parameters
//   32 
//   33 }
        MOVS     R0,R4
        POP      {R4-R6,PC}       ;; return
//   34 
//   35 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   36 CLUDout_1_0::~CLUDout_1_0(void)
//   37 {
_ZN11CLUDout_1_0D1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   38 }
        MOVS     R0,R4
        BL       _ZN7CLUBaseD2Ev
        MOVS     R0,R4
        POP      {R4,PC}          ;; return
//   39 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   40 void SET_OUT_Op(void *pObj)
//   41 {
//   42     //CLUDout_1_0 *pCLUDout_1_0 = reinterpret_cast<CLUDout_1_0 *>(pObj);
//   43     CLUDout_1_0& rCLUDout_1_0 = *(static_cast<CLUDout_1_0*> (pObj));
//   44 /*    asm(
//   45                 "bkpt 1"
//   46                 );
//   47     rCLUDout_1_0.CalcReleySchematic();   */
//   48 }
_Z10SET_OUT_OpPv:
        BX       LR               ;; return
//   49 #include "Rele_p1.cpp"

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute short const arReleShOffsets[30]
arReleShOffsets:
        DC16 0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
        DC16 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arNot01__1_1InDataDsc[1]
arNot01__1_1InDataDsc:
        DC16 23, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Not01__1_1DscRec
Not01__1_1DscRec:
        DC8 1, 1, 4, 0
        DC32 arNot01__1_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd02__2_1InDataDsc[2]
arAnd02__2_1InDataDsc:
        DC16 23, 0, 17, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And02__2_1DscRec
And02__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd02__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd03__2_1InDataDsc[2]
arAnd03__2_1InDataDsc:
        DC16 23, 0, 18, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And03__2_1DscRec
And03__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd03__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd04__2_1InDataDsc[2]
arAnd04__2_1InDataDsc:
        DC16 24, 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And04__2_1DscRec
And04__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd04__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arOr_05__2_1InDataDsc[2]
arOr_05__2_1InDataDsc:
        DC16 21, 0, 22, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Or_05__2_1DscRec
Or_05__2_1DscRec:
        DC8 2, 1, 2, 0
        DC32 arOr_05__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arRS_06__2_2InDataDsc[2]
arRS_06__2_2InDataDsc:
        DC16 2, 0, 3, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const RS_06__2_2DscRec
RS_06__2_2DscRec:
        DC8 2, 2, 5, 0
        DC32 arRS_06__2_2InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd07__2_1InDataDsc[2]
arAnd07__2_1InDataDsc:
        DC16 25, 0, 20, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And07__2_1DscRec
And07__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd07__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arOr_08__2_1InDataDsc[2]
arOr_08__2_1InDataDsc:
        DC16 1, 0, 5, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Or_08__2_1DscRec
Or_08__2_1DscRec:
        DC8 2, 1, 2, 0
        DC32 arOr_08__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd09__2_1InDataDsc[2]
arAnd09__2_1InDataDsc:
        DC16 26, 0, 22, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And09__2_1DscRec
And09__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd09__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd10__2_1InDataDsc[2]
arAnd10__2_1InDataDsc:
        DC16 19, 0, 7, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And10__2_1DscRec
And10__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd10__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd11__2_1InDataDsc[2]
arAnd11__2_1InDataDsc:
        DC16 20, 0, 7, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And11__2_1DscRec
And11__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd11__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arOr_12__2_1InDataDsc[2]
arOr_12__2_1InDataDsc:
        DC16 27, 0, 6, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Or_12__2_1DscRec
Or_12__2_1DscRec:
        DC8 2, 1, 2, 0
        DC32 arOr_12__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arOr_13__2_1InDataDsc[2]
arOr_13__2_1InDataDsc:
        DC16 28, 0, 6, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Or_13__2_1DscRec
Or_13__2_1DscRec:
        DC8 2, 1, 2, 0
        DC32 arOr_13__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arNot14__1_1InDataDsc[1]
arNot14__1_1InDataDsc:
        DC16 8, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Not14__1_1DscRec
Not14__1_1DscRec:
        DC8 1, 1, 4, 0
        DC32 arNot14__1_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd15__3_1InDataDsc[3]
arAnd15__3_1InDataDsc:
        DC16 10, 0, 11, 0, 13, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And15__3_1DscRec
And15__3_1DscRec:
        DC8 3, 1, 1, 0
        DC32 arAnd15__3_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd16__3_1InDataDsc[3]
arAnd16__3_1InDataDsc:
        DC16 10, 0, 12, 0, 8, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And16__3_1DscRec
And16__3_1DscRec:
        DC8 3, 1, 1, 0
        DC32 arAnd16__3_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arOr17__3_1InDataDsc[3]
arOr17__3_1InDataDsc:
        DC16 9, 0, 14, 0, 15, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Or17__3_1DscRec
Or17__3_1DscRec:
        DC8 3, 1, 2, 0
        DC32 arOr17__3_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const *const arPReleShcemasDscRecords[17]
arPReleShcemasDscRecords:
        DC32 Not01__1_1DscRec, And02__2_1DscRec, And03__2_1DscRec
        DC32 And04__2_1DscRec, Or_05__2_1DscRec, RS_06__2_2DscRec
        DC32 And07__2_1DscRec, Or_08__2_1DscRec, And09__2_1DscRec
        DC32 And10__2_1DscRec, And11__2_1DscRec, Or_12__2_1DscRec
        DC32 Or_13__2_1DscRec, Not14__1_1DscRec, And15__3_1DscRec
        DC32 And16__3_1DscRec, Or17__3_1DscRec

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//   50 static char chGLB_QTrg = 0;
chGLB_QTrg:
        DS8 1

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   51 void CLUDout_1_0::CalcReleySchematic(void){
_ZN11CLUDout_1_018CalcReleySchematicEv:
        PUSH     {R4-R9,LR}
        SUB      SP,SP,#+32
//   52 register long rl_Val,i;
//   53 
//   54 #pragma data_alignment=4
//   55 char arChIntermediaResult[(TOTAL_RELE_LU_CALC_POINT)];
//   56 const LedShcemasDscRecord* pLUShcemasDscRec;// = &arPLedShcemasDscRecords;
//   57 arChIntermediaResult[OFFSET_OUT_IN_RELE_TRIGGER_SELECTOR         ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+19]
//   58 arChIntermediaResult[OFFSET_OUT_IN_RELE_STABLE_SELECTOR          ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+20]
//   59 arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_SELECTOR           ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+21]
//   60 arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_SIMPLE_SELECTOR    ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+22]
//   61 arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_EXTANDED_SELECTOR  ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+23]
//   62 arChIntermediaResult[OFFSET_OUT_IN_RELE__RIN                     ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+24]
//   63 arChIntermediaResult[OFFSET_OUT_IN_RELE__RESET                   ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+25]
//   64 arChIntermediaResult[OFFSET_OUT_IN_RELE__BL_IMP                  ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+26]
//   65 arChIntermediaResult[OFFSET_OUT_IN_RELE__C1_C2                   ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+27]
//   66 arChIntermediaResult[OFFSET_OUT_IN_RELE_C1                       ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+28]
//   67 arChIntermediaResult[OFFSET_OUT_IN_RELE_C2                       ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+29]
//   68 
//   69 rl_Val = 0;
        MOVS     R5,#+0
        MOVS     R2,R5
//   70 long k, j, l;
//   71 short shCounterProcessedRec = RELE_Not01__1_1;
        MOVS     R12,#+0
//   72   do {
//   73     pLUShcemasDscRec = arPReleShcemasDscRecords[shCounterProcessedRec - RELE_Not01__1_1];
??CalcReleySchematic_0:
        LDR.W    LR,??DataTable0
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        LDR      LR,[LR, R12, LSL #+2]
        MOV      R4,LR
//   74     i = pLUShcemasDscRec->chTypeOperation;
        LDRB     LR,[R4, #+2]
        MOV      R3,LR
//   75     switch (i) {
        CMP      R3,#+1
        BEQ.N    ??CalcReleySchematic_1
        BCC.W    ??CalcReleySchematic_2
        CMP      R3,#+3
        BEQ.N    ??CalcReleySchematic_3
        BCC.N    ??CalcReleySchematic_4
        CMP      R3,#+5
        BEQ.W    ??CalcReleySchematic_5
        BCC.W    ??CalcReleySchematic_6
        B.N      ??CalcReleySchematic_2
//   76         case LU_GEN_OP_AND:
//   77             rl_Val = 1;
??CalcReleySchematic_1:
        MOVS     LR,#+1
        MOV      R2,LR
//   78             for (i = 0; (i < pLUShcemasDscRec->chAmtOut) &&(rl_Val == 1); i++) {
        MOVS     LR,#+0
        MOV      R3,LR
??CalcReleySchematic_7:
        LDRB     LR,[R4, #+1]
        CMP      R3,LR
        BGE.N    ??CalcReleySchematic_8
        CMP      R2,#+1
        BNE.N    ??CalcReleySchematic_8
//   79                 k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, R3, LSL #+2]
        MOV      R5,LR
//   80                 l = arReleShOffsets[k];
        LDR.W    LR,??DataTable0_1
        LDRSH    LR,[LR, R5, LSL #+1]
        MOV      R7,LR
//   81                 j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
        LDR      LR,[R4, #+4]
        ADDS     LR,LR,R3, LSL #+2
        LDRSH    LR,[LR, #+2]
        ADDS     LR,LR,R7
        MOV      R6,LR
//   82                 rl_Val &= arChIntermediaResult[j];
        MOV      LR,SP
        LDRB     LR,[R6, LR]
        ANDS     R2,LR,R2
//   83             }
        ADDS     R3,R3,#+1
        B.N      ??CalcReleySchematic_7
//   84             arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
??CalcReleySchematic_8:
        MOV      LR,SP
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        STRB     R2,[R12, LR]
        ADDS     R12,R12,#+1
//   85             break;
        B.N      ??CalcReleySchematic_2
//   86         case LU_GEN_OP_OR:
//   87             rl_Val = 0;
??CalcReleySchematic_4:
        MOVS     LR,#+0
        MOV      R2,LR
//   88             for (i = 0; (i < pLUShcemasDscRec->chAmtOut) &&(rl_Val == 0); i++) {
        MOVS     LR,#+0
        MOV      R3,LR
??CalcReleySchematic_9:
        LDRB     LR,[R4, #+1]
        CMP      R3,LR
        BGE.N    ??CalcReleySchematic_10
        CMP      R2,#+0
        BNE.N    ??CalcReleySchematic_10
//   89                 k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, R3, LSL #+2]
        MOV      R5,LR
//   90                 l = arReleShOffsets[k];
        LDR.W    LR,??DataTable0_1
        LDRSH    LR,[LR, R5, LSL #+1]
        MOV      R7,LR
//   91                 j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
        LDR      LR,[R4, #+4]
        ADDS     LR,LR,R3, LSL #+2
        LDRSH    LR,[LR, #+2]
        ADDS     LR,LR,R7
        MOV      R6,LR
//   92                 rl_Val |= arChIntermediaResult[j];
        MOV      LR,SP
        LDRB     LR,[R6, LR]
        ORRS     R2,LR,R2
//   93             }
        ADDS     R3,R3,#+1
        B.N      ??CalcReleySchematic_9
//   94             arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
??CalcReleySchematic_10:
        MOV      LR,SP
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        STRB     R2,[R12, LR]
        ADDS     R12,R12,#+1
//   95             break;
        B.N      ??CalcReleySchematic_2
//   96         case LU_GEN_OP_XOR:
//   97             i = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
??CalcReleySchematic_3:
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, #+0]
        MOV      R3,LR
//   98             rl_Val = arReleShOffsets[i];
        LDR.W    LR,??DataTable0_1
        LDRSH    LR,[LR, R3, LSL #+1]
        MOV      R2,LR
//   99             i = rl_Val + pLUShcemasDscRec->pInputDscData[0].shIndexOut;
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, #+2]
        ADDS     LR,LR,R2
        MOV      R3,LR
//  100             j = arChIntermediaResult[i];
        MOV      LR,SP
        LDRB     LR,[R3, LR]
        MOV      R6,LR
//  101             i = pLUShcemasDscRec->pInputDscData[1].shOrderNumLU;
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, #+4]
        MOV      R3,LR
//  102             rl_Val = arReleShOffsets[i];
        LDR.W    LR,??DataTable0_1
        LDRSH    LR,[LR, R3, LSL #+1]
        MOV      R2,LR
//  103             i = rl_Val + pLUShcemasDscRec->pInputDscData[1].shIndexOut;
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, #+6]
        ADDS     LR,LR,R2
        MOV      R3,LR
//  104             rl_Val = j^arChIntermediaResult[i];
        MOV      LR,SP
        LDRB     LR,[R3, LR]
        EORS     LR,LR,R6
        MOV      R2,LR
//  105             arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
        MOV      LR,SP
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        STRB     R2,[R12, LR]
        ADDS     R12,R12,#+1
//  106             break;
        B.N      ??CalcReleySchematic_2
//  107         case LU_GEN_OP_NOT:
//  108             LUShcemasInDataDsc const *pLUShcemasInDataDsc;
//  109             rl_Val = 0;
??CalcReleySchematic_6:
        MOVS     LR,#+0
        MOV      R2,LR
//  110             pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
        LDR      LR,[R4, #+4]
        MOV      R1,LR
//  111             i = pLUShcemasInDataDsc[0].shOrderNumLU;
        LDRSH    LR,[R1, #+0]
        MOV      R3,LR
//  112             rl_Val = arReleShOffsets[i];
        LDR.W    LR,??DataTable0_1
        LDRSH    LR,[LR, R3, LSL #+1]
        MOV      R2,LR
//  113             i = rl_Val + pLUShcemasInDataDsc[0].shIndexOut;
        LDRSH    LR,[R1, #+2]
        ADDS     LR,LR,R2
        MOV      R3,LR
//  114             rl_Val = arChIntermediaResult[i];
        MOV      LR,SP
        LDRB     LR,[R3, LR]
        MOV      R2,LR
//  115 
//  116             arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
        MOV      LR,SP
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        STRB     R2,[R12, LR]
        ADDS     R12,R12,#+1
//  117             break;
        B.N      ??CalcReleySchematic_2
//  118         case LU_GEN_OP_RS_TRIGGER:
//  119             rl_Val = 0;
??CalcReleySchematic_5:
        MOVS     LR,#+0
        MOV      R2,LR
//  120             rl_Val = chGLB_QTrg;
        LDR.W    LR,??DataTable0_2
        LDRB     LR,[LR, #+0]
        MOV      R2,LR
//  121             arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
        MOV      LR,SP
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        STRB     R2,[R12, LR]
        ADDS     R12,R12,#+1
//  122             arChIntermediaResult[shCounterProcessedRec++] = !rl_Val;
        MOV      LR,R12
        ADDS     R12,LR,#+1
        CMP      R2,#+0
        BNE.N    ??CalcReleySchematic_11
        MOVS     R8,#+1
        B.N      ??CalcReleySchematic_12
??CalcReleySchematic_11:
        MOVS     R8,#+0
??CalcReleySchematic_12:
        MOV      R9,SP
        SXTH     LR,LR            ;; SignExt  LR,LR,#+16,#+16
        STRB     R8,[LR, R9]
//  123             break;
//  124             //Read Input Data
//  125 
//  126             //Eval Function
//  127             //Put Result
//  128 
//  129         default:
//  130             ;
//  131     }
//  132 
//  133   } while (shCounterProcessedRec < IN_RELE_NORMAL_SELECTOR);
??CalcReleySchematic_2:
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        CMP      R12,#+17
        BLT.W    ??CalcReleySchematic_0
//  134 
//  135 }
        ADD      SP,SP,#+32
        POP      {R4-R9,PC}       ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0:
        DC32     arPReleShcemasDscRecords

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_1:
        DC32     arReleShOffsets

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_2:
        DC32     chGLB_QTrg

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// 
//   1 byte  in section .bss
// 404 bytes in section .rodata
// 678 bytes in section .text
// 
// 678 bytes of CODE  memory
// 404 bytes of CONST memory
//   1 byte  of DATA  memory
//
//Errors: none
//Warnings: 1
