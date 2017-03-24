///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUBase.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUBase.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
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
//        files\v.12.x.y\Flash-Debug\List\LUBase.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN gblLUAreaAuxVar

        PUBLIC _Z6AND_OpPv
        PUBLIC _Z6NOT_OpPv
        PUBLIC _Z6OR__OpPv
        PUBLIC _Z6XOR_OpPv
        PUBLIC _Z7Null_OPPv
        PUBLIC _Z9Meandr_OpPv
        PUBLIC _ZN7CLUBase14SetOrderNumberEv
        PUBLIC _ZN7CLUBaseC1Ev
        PUBLIC _ZN7CLUBaseC2Ev
        PUBLIC _ZN7CLUBaseD1Ev
        PUBLIC _ZN7CLUBaseD2Ev

// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\LUBase.cpp
//    1 #ifdef VISUAL_STUDIO
//    2 #include "StdAfx.h"
//    3 #endif
//    4 #include "LUBase.h"
//    5 #include "BaseInPoint.h"
//    6 #include "InPoint.h"
//    7 #include "ExtPoint.h"
//    8 #include "Shematic.h"
//    9 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUBase::subobject CLUBase()
_ZN7CLUBaseC2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN7CLUBaseC1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUBase::subobject ~CLUBase()
_ZN7CLUBaseD2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN7CLUBaseD1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   10 CLUBase::CLUBase(void)
//   11 {
//   12 	chMaxIteratoin = 10;
_ZN7CLUBaseC1Ev:
        MOVS     R1,#+10
        STRB     R1,[R0, #+4]
//   13 	chIteration = 0;
        MOVS     R1,#+0
        STRB     R1,[R0, #+5]
//   14 	chNumInput  = static_cast<char>(0);
        MOVS     R1,#+0
        STRB     R1,[R0, #+6]
//   15 	chNumOutput = 0;
        MOVS     R1,#+0
        STRB     R1,[R0, #+7]
//   16 	chTypeLogicFunction = LU_OP_NULL;
        MOVS     R1,#+1
        STRB     R1,[R0, #+8]
//   17 	shShemasIdLUStng   = 0;
        MOVS     R1,#+0
        STRH     R1,[R0, #+10]
//   18 	shShemasOrdNumStng = 0;
        MOVS     R1,#+0
        STRH     R1,[R0, #+12]
//   19 	shLUBieldOrdNum    = 0;
        MOVS     R1,#+0
        STRH     R1,[R0, #+14]
//   20 	chLinkSetOn = 0;
        MOVS     R1,#+0
        STRB     R1,[R0, #+9]
//   21 	LogicFunc  = Null_OP;
        ADR.W    R1,_Z7Null_OPPv
        STR      R1,[R0, #+16]
//   22 	//shOrderNumberCLUBase
//   23 	pOut = static_cast<void*>(0);//(void*)0;
        MOVS     R1,#+0
        STR      R1,[R0, #+20]
//   24 	pIn  = static_cast<void*>(0);//(void*)0;
        MOVS     R1,#+0
        STR      R1,[R0, #+0]
//   25 } 
        BX       LR               ;; return
//   26 extern LUAreaAuxVar gblLUAreaAuxVar;

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   27 void CLUBase::SetOrderNumber(void){
//   28 	shLUBieldOrdNum = static_cast<short>(++gblLUAreaAuxVar.shAmountPlacedLogicUnit);
_ZN7CLUBase14SetOrderNumberEv:
        LDR.N    R1,??DataTable0
        LDRH     R1,[R1, #+0]
        ADDS     R1,R1,#+1
        LDR.N    R2,??DataTable0
        STRH     R1,[R2, #+0]
        LDR.N    R1,??DataTable0
        LDRH     R1,[R1, #+0]
        STRH     R1,[R0, #+14]
//   29 	
//   30 }
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0:
        DC32     gblLUAreaAuxVar
//   31 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   32 CLUBase::~CLUBase(void)
//   33 {
//   34 
//   35 }
_ZN7CLUBaseD1Ev:
        BX       LR               ;; return
//   36 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   37 void AND_Op(void *pObj)
//   38 {
//   39 
//   40 }
_Z6AND_OpPv:
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   41 void OR__Op(void *pObj)
//   42 {
//   43 
//   44 }
_Z6OR__OpPv:
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   45 void XOR_Op(void *pObj)
//   46 {
//   47 
//   48 }
_Z6XOR_OpPv:
        BX       LR               ;; return
//   49 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   50 void Meandr_Op(void *pObj)
//   51 {
//   52 
//   53 }
_Z9Meandr_OpPv:
        BX       LR               ;; return
//   54 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//   55 void Null_OP(void *pObj)
//   56 {
//   57 
//   58 }
_Z7Null_OPPv:
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   59 void NOT_Op(void *pObj)
//   60 {
//   61 
//   62 }
_Z6NOT_OpPv:
        BX       LR               ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// 
// 112 bytes in section .text
// 
// 112 bytes of CODE memory
//
//Errors: none
//Warnings: none
