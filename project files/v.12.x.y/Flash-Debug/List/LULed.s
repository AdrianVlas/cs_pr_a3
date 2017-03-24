///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:56
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LULed.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LULed.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
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
//        files\v.12.x.y\Flash-Debug\List\LULed.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN _ZN7CLUBaseC2Ev
        EXTERN _ZN7CLUBaseD2Ev

        PUBLIC _Z10SET_LED_OpPv
        PUBLIC _Z11PUT_Op_1_0_Pv
        PUBLIC _ZN6CLULed16CalcLedSchematicEv
        PUBLIC _ZN6CLULedC1Ecc
        PUBLIC _ZN6CLULedC1Ev
        PUBLIC _ZN6CLULedC2Ecc
        PUBLIC _ZN6CLULedC2Ev
        PUBLIC _ZN6CLULedD1Ev
        PUBLIC _ZN6CLULedD2Ev
        PUBLIC chGLBIn1_5
        PUBLIC chGLBIn6_12
        PUBLIC lGLBInChek_6_12
        PUBLIC lGLBInChek_8_72


        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLULed::subobject CLULed()
_ZN6CLULedC2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN6CLULedC1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLULed::subobject ~CLULed()
_ZN6CLULedD2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN6CLULedD1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLULed::subobject CLULed(char, char)
_ZN6CLULedC2Ecc:
        PUSH     {R4,LR}
        MOVS     R4,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        BL       _ZN6CLULedC1Ecc
        POP      {R4,PC}          ;; return
// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\LULed.cpp
//    1 #ifdef VISUAL_STUDIO
//    2 #include "StdAfx.h"
//    3 #endif
//    4 #include "LULed.h"
//    5 //#include "libraries.h"
//    6 
//    7 #include "stm32f2xx.h"
//    8 #include "stm32f2xx_it.h"
//    9 #include "Ereg.h"
//   10 
//   11 
//   12 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   13 void PUT_Op_1_0_    (void *pObj)
//   14 {
//   15 //CLUNot_1_1& refCLUNot_1_1 = pObj;
//   16 //CLULed *pCLULed = (CLULed*)pObj;
//   17 
//   18 }
_Z11PUT_Op_1_0_Pv:
        BX       LR               ;; return
//   19 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   20 CLULed::CLULed(void)
_ZN6CLULedC1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   21 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   22 }
        MOVS     R0,R4
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   23 CLULed::CLULed(char chM,char chI)//,LUOutDsc* pLUOutDsc)
_ZN6CLULedC1Ecc:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//   24 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   25 	chMaxIteratoin = chM;
        STRB     R5,[R4, #+4]
//   26 	chIteration = chI;
        STRB     R6,[R4, #+5]
//   27 	chNumInput  = static_cast<char>(shCLULed_1_0_AmtIn);
        MOVS     R0,#+1
        STRB     R0,[R4, #+6]
//   28 	chNumOutput = static_cast<char>(shCLULed_1_0_AmtOut);
        MOVS     R0,#+0
        STRB     R0,[R4, #+7]
//   29 	
//   30 	
//   31 
//   32 	//Set Input parameters
//   33 	//pIn = (void*)arrPchIn;
//   34 	//pOut = (void*)arrOut;
//   35 	//Set OutPut parameters
//   36 
//   37 }
        MOVS     R0,R4
        POP      {R4-R6,PC}       ;; return
//   38 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   39 CLULed::~CLULed(void)
//   40 {
_ZN6CLULedD1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   41 }
        MOVS     R0,R4
        BL       _ZN7CLUBaseD2Ev
        MOVS     R0,R4
        POP      {R4,PC}          ;; return

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//   42 char chGLBIn1_5 = 0;
chGLBIn1_5:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//   43 char chGLBIn6_12 = 0;
chGLBIn6_12:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   44 long lGLBInChek_6_12 = 0;
lGLBInChek_6_12:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   45 long lGLBInChek_8_72 = 0;
lGLBInChek_8_72:
        DS8 4

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   46 void SET_LED_Op(void *pObj)
//   47 {
//   48 	//CLUNot_1_1& refCLUNot_1_1 = pObj;
//   49 //	CLULed *pCLULed = (CLULed*)pObj;
//   50 CLULed& rCLULed = *(static_cast<CLULed*>(pObj));
//   51 struct {
//   52 char *pLAdr1;
//   53 char *pLAdr2;
//   54 char *pLAdr3;
//   55 char *pLAdr4;
//   56 short*pLASh;
//   57 long L_Vl;
//   58 char chVal;
//   59 short shVal;
//   60 } sLV;
//   61  /* asm(
//   62        "bkpt 1"
//   63        );/*
//   64 rCLULed.CalcLedSchematic();*/
//   65 return;
_Z10SET_LED_OpPv:
        BX       LR               ;; return
//   66 sLV.pLAdr1 = reinterpret_cast<char*>(NOR_PSRAM_BANK2);
//   67 sLV.pLAdr1 += ADR_WRITE_RI_COLUMNS01__06;//reinterpret_cast<char*>(NOR_PSRAM_BANK2+ADR_WRITE_RI_COLUMNS01__06 );
//   68 sLV.pLAdr2 = reinterpret_cast<char*>( NOR_PSRAM_BANK2);
//   69 sLV.pLAdr2 += ADR_WRITE_RDO__REL_1_6__ROWS_A__D;
//   70 sLV.chVal = 0xff;
//   71 *(sLV.pLAdr1) = sLV.chVal;
//   72 *(sLV.pLAdr2) = sLV.chVal;
//   73 
//   74 sLV.pLAdr1 = reinterpret_cast<char*>(NOR_PSRAM_BANK2);
//   75 sLV.pLAdr1 += ADR_WRITE_RI_COLUMNS01__06<<1;//reinterpret_cast<char*>(NOR_PSRAM_BANK2+ADR_WRITE_RI_COLUMNS01__06 );
//   76 sLV.pLAdr2 = reinterpret_cast<char*>( NOR_PSRAM_BANK2);
//   77 sLV.pLAdr2 += ADR_WRITE_RDO__REL_1_6__ROWS_A__D<<1;
//   78 sLV.chVal = 0xff;
//   79 *(sLV.pLAdr1) = sLV.chVal;
//   80 *(sLV.pLAdr2) = sLV.chVal;
//   81 
//   82 sLV.pLAdr3 = reinterpret_cast<char*>(NOR_PSRAM_BANK2);
//   83 sLV.pLAdr3 +=ADR_WRITE_RDO_REL7_REL14;//reinterpret_cast<char*>(NOR_PSRAM_BANK2+ADR_WRITE_RI_COLUMNS01__06 );
//   84 sLV.pLAdr4 = reinterpret_cast<char*>( NOR_PSRAM_BANK2);
//   85 sLV.pLAdr4 += ADR_WRITE_RDO_REL7_REL14;
//   86 sLV.chVal = 0xff;
//   87 *(sLV.pLAdr3) = sLV.chVal;
//   88 *(sLV.pLAdr4) = sLV.chVal;
//   89 
//   90 sLV.pLAdr3 = reinterpret_cast<char*>(NOR_PSRAM_BANK2);
//   91 sLV.pLAdr3 += ADR_READ_DIN01__05<<1;//
//   92 sLV.pLAdr4 = reinterpret_cast<char*>( NOR_PSRAM_BANK2);
//   93 sLV.pLAdr4 += ADR_READ_DIN06__12<<1;
//   94 sLV.chVal = *(sLV.pLAdr3);
//   95 chGLBIn1_5  |= sLV.chVal;
//   96 sLV.chVal = *(sLV.pLAdr4);
//   97 chGLBIn6_12 |= sLV.chVal;
//   98 
//   99 sLV.chVal = 0;
//  100 sLV.L_Vl = NOR_PSRAM_BANK2+(ADR_READ_CHECK_RDO__REL_1_6<<1);
//  101 sLV.pLASh = reinterpret_cast<short*>(sLV.L_Vl);
//  102 //sLV.pLASh += ADR_READ_CHECK_RDO__REL_1_6<<1;//
//  103 sLV.shVal = *(sLV.pLASh);
//  104 lGLBInChek_6_12  |= sLV.shVal;
//  105 
//  106 sLV.chVal = 0;
//  107 sLV.L_Vl = NOR_PSRAM_BANK2+(ADR_READ_CHECK_RDO_REL7_REL14<<1);
//  108 sLV.pLASh = reinterpret_cast<short*>(sLV.L_Vl);
//  109 //sLV.pLASh += ADR_READ_CHECK_RDO__REL_1_6<<1;//
//  110 sLV.shVal = *(sLV.pLASh);
//  111 lGLBInChek_8_72  |= sLV.shVal;
//  112 
//  113 
//  114 
//  115 //sLV.pLAdr3 = reinterpret_cast<long*>( );
//  116 //sLV.pLAdr4 = reinterpret_cast<long*>( );
//  117 //Set PD3 In O-state
//  118 //GPIO_ResetBits(CON_L, CON_L_PIN);
//  119 //GPIO_SetBits  (CON_L, CON_L_PIN);
//  120 
//  121 //GPIO_SetBits(CON_L, CON_L_PIN);GPIO_ResetBits(CON_L, CON_L_PIN);
//  122 
//  123 
//  124 }
//  125 
//  126 #include "LULedp1.cpp"

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute short const arShOffsets[33]
arShOffsets:
        DC16 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18, 19
        DC16 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arNot06__1_1InDataDsc[1]
arNot06__1_1InDataDsc:
        DC16 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Not06__1_1DscRec
Not06__1_1DscRec:
        DC8 1, 1, 4, 0
        DC32 arNot06__1_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd07__2_1InDataDsc[2]
arAnd07__2_1InDataDsc:
        DC16 0, 0, 26, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And07__2_1DscRec
And07__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd07__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd08__2_1InDataDsc[2]
arAnd08__2_1InDataDsc:
        DC16 0, 0, 27, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And08__2_1DscRec
And08__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd08__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd09__2_1InDataDsc[2]
arAnd09__2_1InDataDsc:
        DC16 1, 0, 6, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And09__2_1DscRec
And09__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd09__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arOr_10__2_1InDataDsc[2]
arOr_10__2_1InDataDsc:
        DC16 30, 0, 31, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Or_10__2_1DscRec
Or_10__2_1DscRec:
        DC8 2, 1, 2, 0
        DC32 arOr_10__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arOr_11__2_1InDataDsc[2]
arOr_11__2_1InDataDsc:
        DC16 7, 0, 12, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Or_11__2_1DscRec
Or_11__2_1DscRec:
        DC8 2, 1, 2, 0
        DC32 arOr_11__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arRS_12__2_2InDataDsc[2]
arRS_12__2_2InDataDsc:
        DC16 8, 0, 9, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const RS_12__2_2DscRec
RS_12__2_2DscRec:
        DC8 2, 2, 5, 0
        DC32 arRS_12__2_2InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd13__2_1InDataDsc[2]
arAnd13__2_1InDataDsc:
        DC16 29, 0, 2, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And13__2_1DscRec
And13__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd13__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd14__2_1InDataDsc[2]
arAnd14__2_1InDataDsc:
        DC16 31, 0, 3, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And14__2_1DscRec
And14__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd14__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd15__2_1InDataDsc[2]
arAnd15__2_1InDataDsc:
        DC16 28, 0, 11, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And15__2_1DscRec
And15__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd15__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd16__2_1InDataDsc[2]
arAnd16__2_1InDataDsc:
        DC16 29, 0, 11, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And16__2_1DscRec
And16__2_1DscRec:
        DC8 2, 1, 1, 0
        DC32 arAnd16__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arOr_17__2_1InDataDsc[2]
arOr_17__2_1InDataDsc:
        DC16 13, 0, 4, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Or_17__2_1DscRec
Or_17__2_1DscRec:
        DC8 2, 1, 2, 0
        DC32 arOr_17__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arOr_18__2_1InDataDsc[2]
arOr_18__2_1InDataDsc:
        DC16 13, 0, 5, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Or_18__2_1DscRec
Or_18__2_1DscRec:
        DC8 2, 1, 2, 0
        DC32 arOr_18__2_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arNot19__1_1InDataDsc[1]
arNot19__1_1InDataDsc:
        DC16 14, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Not19__1_1DscRec
Not19__1_1DscRec:
        DC8 1, 1, 4, 0
        DC32 arNot19__1_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd20__3_1InDataDsc[3]
arAnd20__3_1InDataDsc:
        DC16 16, 0, 17, 0, 19, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And20__3_1DscRec
And20__3_1DscRec:
        DC8 3, 1, 1, 0
        DC32 arAnd20__3_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arAnd21__3_1InDataDsc[3]
arAnd21__3_1InDataDsc:
        DC16 16, 0, 18, 0, 14, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const And21__3_1DscRec
And21__3_1DscRec:
        DC8 3, 1, 1, 0
        DC32 arAnd21__3_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LUShcemasInDataDsc const arOr22__3_1InDataDsc[3]
arOr22__3_1InDataDsc:
        DC16 15, 0, 20, 0, 21, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const Or22__3_1DscRec
Or22__3_1DscRec:
        DC8 3, 1, 2, 0
        DC32 arOr22__3_1InDataDsc

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// static __absolute LedShcemasDscRecord const *const arPLedShcemasDscRecords[17]
arPLedShcemasDscRecords:
        DC32 Not06__1_1DscRec, And07__2_1DscRec, And08__2_1DscRec
        DC32 And09__2_1DscRec, Or_10__2_1DscRec, Or_11__2_1DscRec
        DC32 RS_12__2_2DscRec, And13__2_1DscRec, And14__2_1DscRec
        DC32 And15__2_1DscRec, And16__2_1DscRec, Or_17__2_1DscRec
        DC32 Or_18__2_1DscRec, Not19__1_1DscRec, And20__3_1DscRec
        DC32 And21__3_1DscRec, Or22__3_1DscRec

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  127 static char chGLB_QTrg = 0;
chGLB_QTrg:
        DS8 1

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  128 void CLULed::CalcLedSchematic(void){
_ZN6CLULed16CalcLedSchematicEv:
        PUSH     {R4-R9,LR}
        SUB      SP,SP,#+36
//  129 register long rl_Val,i;
//  130 
//  131 #pragma data_alignment=4
//  132 char arChIntermediaResult[(TOTAL_LU_CALC_POINT)];
//  133 const LedShcemasDscRecord* pLUShcemasDscRec;// = &arPLedShcemasDscRecords;
//  134 
//  135 
//  136 arChIntermediaResult[OFFSET_OUT_IN_00_LEDIN                   ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+0]
//  137 arChIntermediaResult[OFFSET_OUT_IN_01_RESET                   ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+1]
//  138 arChIntermediaResult[OFFSET_OUT_IN_02_BL_IMP                  ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+2]
//  139 arChIntermediaResult[OFFSET_OUT_IN_03_C1_C2_SELECTOR          ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+3]
//  140 arChIntermediaResult[OFFSET_OUT_IN_04_C1                      ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+4]
//  141 arChIntermediaResult[OFFSET_OUT_IN_05_C2                      ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+5]
//  142 arChIntermediaResult[OFFSET_OUT_IN_MNU_NORMAL_SELECTOR        ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+27]
//  143 arChIntermediaResult[OFFSET_OUT_IN_MNU_TRIGGER_SELECTOR       ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+28]
//  144 arChIntermediaResult[OFFSET_OUT_IN_MNU_STABLE_SELECTOR        ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+29]
//  145 arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_SELECTOR         ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+30]
//  146 arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_SIMPLE_SELECTOR  ] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+31]
//  147 arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_EXTANDED_SELECTOR] = 0;//Now Default
        MOVS     R5,#+0
        STRB     R5,[SP, #+32]
//  148     rl_Val = 0;
        MOVS     R5,#+0
        MOVS     R2,R5
//  149 	long k, j, l;
//  150     short shCounterProcessedRec = Not06__1_1;
        MOVS     R12,#+6
//  151     do {
//  152 pLUShcemasDscRec = arPLedShcemasDscRecords[shCounterProcessedRec - Not06__1_1];
??CalcLedSchematic_0:
        LDR.W    LR,??DataTable0
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        ADDS     LR,LR,R12, LSL #+2
        LDR      LR,[LR, #-24]
        MOV      R4,LR
//  153         i = pLUShcemasDscRec->chTypeOperation;
        LDRB     LR,[R4, #+2]
        MOV      R3,LR
//  154         switch (i) {
        CMP      R3,#+1
        BEQ.N    ??CalcLedSchematic_1
        BCC.W    ??CalcLedSchematic_2
        CMP      R3,#+3
        BEQ.N    ??CalcLedSchematic_3
        BCC.N    ??CalcLedSchematic_4
        CMP      R3,#+5
        BEQ.W    ??CalcLedSchematic_5
        BCC.W    ??CalcLedSchematic_6
        B.N      ??CalcLedSchematic_2
//  155             case LU_GEN_OP_AND:
//  156                 rl_Val = 1;
??CalcLedSchematic_1:
        MOVS     LR,#+1
        MOV      R2,LR
//  157                 for (i = 0; (i < pLUShcemasDscRec->chAmtOut)&&(rl_Val == 1); i++) {
        MOVS     LR,#+0
        MOV      R3,LR
??CalcLedSchematic_7:
        LDRB     LR,[R4, #+1]
        CMP      R3,LR
        BGE.N    ??CalcLedSchematic_8
        CMP      R2,#+1
        BNE.N    ??CalcLedSchematic_8
//  158                     k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, R3, LSL #+2]
        MOV      R5,LR
//  159                     l = arShOffsets[k];
        LDR.W    LR,??DataTable0_1
        LDRSH    LR,[LR, R5, LSL #+1]
        MOV      R7,LR
//  160                     j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
        LDR      LR,[R4, #+4]
        ADDS     LR,LR,R3, LSL #+2
        LDRSH    LR,[LR, #+2]
        ADDS     LR,LR,R7
        MOV      R6,LR
//  161                     rl_Val &= arChIntermediaResult[j];
        MOV      LR,SP
        LDRB     LR,[R6, LR]
        ANDS     R2,LR,R2
//  162                 }
        ADDS     R3,R3,#+1
        B.N      ??CalcLedSchematic_7
//  163                 arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
??CalcLedSchematic_8:
        MOV      LR,SP
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        STRB     R2,[R12, LR]
        ADDS     R12,R12,#+1
//  164                 break;
        B.N      ??CalcLedSchematic_2
//  165             case LU_GEN_OP_OR:
//  166                 rl_Val = 0;
??CalcLedSchematic_4:
        MOVS     LR,#+0
        MOV      R2,LR
//  167                 for (i = 0; (i < pLUShcemasDscRec->chAmtOut)&&( rl_Val == 0); i++) {
        MOVS     LR,#+0
        MOV      R3,LR
??CalcLedSchematic_9:
        LDRB     LR,[R4, #+1]
        CMP      R3,LR
        BGE.N    ??CalcLedSchematic_10
        CMP      R2,#+0
        BNE.N    ??CalcLedSchematic_10
//  168                     k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, R3, LSL #+2]
        MOV      R5,LR
//  169                     l = arShOffsets[k];
        LDR.W    LR,??DataTable0_1
        LDRSH    LR,[LR, R5, LSL #+1]
        MOV      R7,LR
//  170                     j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
        LDR      LR,[R4, #+4]
        ADDS     LR,LR,R3, LSL #+2
        LDRSH    LR,[LR, #+2]
        ADDS     LR,LR,R7
        MOV      R6,LR
//  171                     rl_Val |= arChIntermediaResult[j];
        MOV      LR,SP
        LDRB     LR,[R6, LR]
        ORRS     R2,LR,R2
//  172                 }
        ADDS     R3,R3,#+1
        B.N      ??CalcLedSchematic_9
//  173                 arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
??CalcLedSchematic_10:
        MOV      LR,SP
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        STRB     R2,[R12, LR]
        ADDS     R12,R12,#+1
//  174                 break;
        B.N      ??CalcLedSchematic_2
//  175             case LU_GEN_OP_XOR:
//  176                 i = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
??CalcLedSchematic_3:
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, #+0]
        MOV      R3,LR
//  177                 rl_Val = arShOffsets[i];
        LDR.W    LR,??DataTable0_1
        LDRSH    LR,[LR, R3, LSL #+1]
        MOV      R2,LR
//  178                 i = rl_Val + pLUShcemasDscRec->pInputDscData[0].shIndexOut;
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, #+2]
        ADDS     LR,LR,R2
        MOV      R3,LR
//  179                 j = arChIntermediaResult[i];
        MOV      LR,SP
        LDRB     LR,[R3, LR]
        MOV      R6,LR
//  180                 i = pLUShcemasDscRec->pInputDscData[1].shOrderNumLU;
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, #+4]
        MOV      R3,LR
//  181                 rl_Val = arShOffsets[i];
        LDR.W    LR,??DataTable0_1
        LDRSH    LR,[LR, R3, LSL #+1]
        MOV      R2,LR
//  182                 i = rl_Val + pLUShcemasDscRec->pInputDscData[1].shIndexOut;
        LDR      LR,[R4, #+4]
        LDRSH    LR,[LR, #+6]
        ADDS     LR,LR,R2
        MOV      R3,LR
//  183                 rl_Val = j^arChIntermediaResult[i];
        MOV      LR,SP
        LDRB     LR,[R3, LR]
        EORS     LR,LR,R6
        MOV      R2,LR
//  184                 arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
        MOV      LR,SP
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        STRB     R2,[R12, LR]
        ADDS     R12,R12,#+1
//  185                 break;
        B.N      ??CalcLedSchematic_2
//  186             case LU_GEN_OP_NOT:
//  187                 LUShcemasInDataDsc const *pLUShcemasInDataDsc;
//  188                 rl_Val = 0;
??CalcLedSchematic_6:
        MOVS     LR,#+0
        MOV      R2,LR
//  189                 pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
        LDR      LR,[R4, #+4]
        MOV      R1,LR
//  190                 i = pLUShcemasInDataDsc[0].shOrderNumLU;
        LDRSH    LR,[R1, #+0]
        MOV      R3,LR
//  191                 rl_Val = arShOffsets[i];
        LDR.W    LR,??DataTable0_1
        LDRSH    LR,[LR, R3, LSL #+1]
        MOV      R2,LR
//  192                 i = rl_Val + pLUShcemasInDataDsc[0].shIndexOut;
        LDRSH    LR,[R1, #+2]
        ADDS     LR,LR,R2
        MOV      R3,LR
//  193                 rl_Val = arChIntermediaResult[i];
        MOV      LR,SP
        LDRB     LR,[R3, LR]
        MOV      R2,LR
//  194 
//  195                 arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
        MOV      LR,SP
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        STRB     R2,[R12, LR]
        ADDS     R12,R12,#+1
//  196                 break;
        B.N      ??CalcLedSchematic_2
//  197             case LU_GEN_OP_RS_TRIGGER:
//  198                 rl_Val = 0;
??CalcLedSchematic_5:
        MOVS     LR,#+0
        MOV      R2,LR
//  199                 rl_Val = chGLB_QTrg;
        LDR.W    LR,??DataTable0_2
        LDRB     LR,[LR, #+0]
        MOV      R2,LR
//  200                 arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
        MOV      LR,SP
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        STRB     R2,[R12, LR]
        ADDS     R12,R12,#+1
//  201                 arChIntermediaResult[shCounterProcessedRec++] = !rl_Val;
        MOV      LR,R12
        ADDS     R12,LR,#+1
        CMP      R2,#+0
        BNE.N    ??CalcLedSchematic_11
        MOVS     R8,#+1
        B.N      ??CalcLedSchematic_12
??CalcLedSchematic_11:
        MOVS     R8,#+0
??CalcLedSchematic_12:
        MOV      R9,SP
        SXTH     LR,LR            ;; SignExt  LR,LR,#+16,#+16
        STRB     R8,[LR, R9]
//  202                 break;
//  203                 //Read Input Data
//  204 
//  205                 //Eval Function
//  206                 //Put Result
//  207                 
//  208             default:
//  209                 ;
//  210         }
//  211   
//  212     } while (shCounterProcessedRec < IN_MNU_NORMAL_SELECTOR);
??CalcLedSchematic_2:
        SXTH     R12,R12          ;; SignExt  R12,R12,#+16,#+16
        CMP      R12,#+26
        BLT.W    ??CalcLedSchematic_0
//  213 
//  214 }
        ADD      SP,SP,#+36
        POP      {R4-R9,PC}       ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0:
        DC32     arPLedShcemasDscRecords

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_1:
        DC32     arShOffsets

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_2:
        DC32     chGLB_QTrg

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//  215 
// 
//  11 bytes in section .bss
// 412 bytes in section .rodata
// 678 bytes in section .text
// 
// 678 bytes of CODE  memory
// 412 bytes of CONST memory
//  11 bytes of DATA  memory
//
//Errors: none
//Warnings: 3
