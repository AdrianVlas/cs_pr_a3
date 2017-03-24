///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUNot_1_1.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUNot_1_1.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
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
//        files\v.12.x.y\Flash-Debug\List\LUNot_1_1.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN _Z6NOT_OpPv
        EXTERN _ZN7CLUBaseC2Ev
        EXTERN _ZN7CLUBaseD2Ev

        PUBLIC _Z10NOT_Op_1_1Pv
        PUBLIC _ZN10CLUNot_1_1C1Ecc
        PUBLIC _ZN10CLUNot_1_1C1Ev
        PUBLIC _ZN10CLUNot_1_1C2Ecc
        PUBLIC _ZN10CLUNot_1_1C2Ev
        PUBLIC _ZN10CLUNot_1_1D1Ev
        PUBLIC _ZN10CLUNot_1_1D2Ev


        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUNot_1_1::subobject CLUNot_1_1()
_ZN10CLUNot_1_1C2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN10CLUNot_1_1C1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUNot_1_1::subobject ~CLUNot_1_1()
_ZN10CLUNot_1_1D2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN10CLUNot_1_1D1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUNot_1_1::subobject CLUNot_1_1(char, char)
_ZN10CLUNot_1_1C2Ecc:
        PUSH     {R4,LR}
        MOVS     R4,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        BL       _ZN10CLUNot_1_1C1Ecc
        POP      {R4,PC}          ;; return
// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\LUNot_1_1.cpp
//    1 #ifdef VISUAL_STUDIO
//    2 #include "StdAfx.h"
//    3 #endif
//    4 #include "LUNot_1_1.h"
//    5 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    6 void NOT_Op_1_1    (void *pObj)
//    7 {
//    8 //CLUNot_1_1& refCLUNot_1_1 = pObj;
//    9 //CLUNot_1_1 *pCLUNot_1_1 = (CLUNot_1_1*)pObj;
//   10 
//   11 }
_Z10NOT_Op_1_1Pv:
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   12 CLUNot_1_1::CLUNot_1_1(void):CLUBase()
_ZN10CLUNot_1_1C1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   13 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   14 }
        MOVS     R0,R4
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   15 CLUNot_1_1::CLUNot_1_1(char chM,char chI)//,LUOutDsc* pLUOutDsc)
_ZN10CLUNot_1_1C1Ecc:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//   16 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   17 	chMaxIteratoin = chM;
        STRB     R5,[R4, #+4]
//   18 	chIteration = chI;
        STRB     R6,[R4, #+5]
//   19 	chNumInput  = static_cast<char>(shCLUNot_1_1_AmtIn); 
        MOVS     R0,#+1
        STRB     R0,[R4, #+6]
//   20 	chNumOutput = static_cast<char>(shCLUNot_1_1_AmtOut);
        MOVS     R0,#+1
        STRB     R0,[R4, #+7]
//   21 	chTypeLogicFunction = LU_OP_NOT;
        MOVS     R0,#+5
        STRB     R0,[R4, #+8]
//   22 	LogicFunc  = NOT_Op;//???
        LDR.N    R0,??DataTable0
        STR      R0,[R4, #+16]
//   23 
//   24 	//Set Input parameters
//   25 	pIn = reinterpret_cast<void*>(arrPchIn);
        ADDS     R0,R4,#+24
        STR      R0,[R4, #+0]
//   26 
//   27 	//Set OutPut parameters
//   28 	pOut = reinterpret_cast<void*>(arrOut);
        ADDS     R0,R4,#+28
        STR      R0,[R4, #+20]
//   29 
//   30 }
        MOVS     R0,R4
        POP      {R4-R6,PC}       ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0:
        DC32     _Z6NOT_OpPv

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   31 CLUNot_1_1::~CLUNot_1_1(void)
//   32 {
_ZN10CLUNot_1_1D1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   33 }
        MOVS     R0,R4
        BL       _ZN7CLUBaseD2Ev
        MOVS     R0,R4
        POP      {R4,PC}          ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// 
// 124 bytes in section .text
// 
// 124 bytes of CODE memory
//
//Errors: none
//Warnings: none
