///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUXor_8_1.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUXor_8_1.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
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
//        files\v.12.x.y\Flash-Debug\List\LUXor_8_1.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN _Z6NOT_OpPv
        EXTERN _ZN7CLUBaseC2Ev
        EXTERN _ZN7CLUBaseD2Ev

        PUBLIC _Z10XOR_Op_8_1Pv
        PUBLIC _ZN10CLUXor_8_1C1Ecc
        PUBLIC _ZN10CLUXor_8_1C1Ev
        PUBLIC _ZN10CLUXor_8_1C2Ecc
        PUBLIC _ZN10CLUXor_8_1C2Ev
        PUBLIC _ZN10CLUXor_8_1D1Ev
        PUBLIC _ZN10CLUXor_8_1D2Ev


        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUXor_8_1::subobject CLUXor_8_1()
_ZN10CLUXor_8_1C2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN10CLUXor_8_1C1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUXor_8_1::subobject ~CLUXor_8_1()
_ZN10CLUXor_8_1D2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN10CLUXor_8_1D1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUXor_8_1::subobject CLUXor_8_1(char, char)
_ZN10CLUXor_8_1C2Ecc:
        PUSH     {R4,LR}
        MOVS     R4,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        BL       _ZN10CLUXor_8_1C1Ecc
        POP      {R4,PC}          ;; return
// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\LUXor_8_1.cpp
//    1 #ifdef VISUAL_STUDIO
//    2 #include "StdAfx.h"
//    3 #endif
//    4 #include "LUXor_8_1.h"
//    5 
//    6 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    7 void XOR_Op_8_1    (void *pObj)
//    8 {
//    9 //CLUNot_1_1& refCLUNot_1_1 = pObj;
//   10 //CLUXor_8_1 *pCLUXor_8_1 = (CLUXor_8_1*)pObj;
//   11 
//   12 }
_Z10XOR_Op_8_1Pv:
        BX       LR               ;; return
//   13 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   14 CLUXor_8_1::CLUXor_8_1(void)
_ZN10CLUXor_8_1C1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   15 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   16 }
        MOVS     R0,R4
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   17 CLUXor_8_1::CLUXor_8_1(char chM,char chI)//,LUOutDsc* pLUOutDsc)
_ZN10CLUXor_8_1C1Ecc:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//   18 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   19 	chMaxIteratoin = chM;
        STRB     R5,[R4, #+4]
//   20 	chIteration = chI;
        STRB     R6,[R4, #+5]
//   21 	chNumInput  = static_cast<char>(shCLUXor_2_1_AmtIn );
        MOVS     R0,#+2
        STRB     R0,[R4, #+6]
//   22 	chNumOutput = static_cast<char>(shCLUXor_2_1_AmtOut);
        MOVS     R0,#+1
        STRB     R0,[R4, #+7]
//   23 	chTypeLogicFunction = LU_OP_NOT;
        MOVS     R0,#+5
        STRB     R0,[R4, #+8]
//   24 	LogicFunc  = NOT_Op;//???
        LDR.N    R0,??DataTable0
        STR      R0,[R4, #+16]
//   25 
//   26 	//Set Input parameters
//   27 	pIn  = reinterpret_cast<void*>(arrPchIn);
        ADDS     R0,R4,#+24
        STR      R0,[R4, #+0]
//   28 	pOut = reinterpret_cast<void*>( arrOut );
        ADDS     R0,R4,#+32
        STR      R0,[R4, #+20]
//   29 	//Set OutPut parameters
//   30 
//   31 }
        MOVS     R0,R4
        POP      {R4-R6,PC}       ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0:
        DC32     _Z6NOT_OpPv
//   32 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   33 CLUXor_8_1::~CLUXor_8_1(void)
//   34 {
_ZN10CLUXor_8_1D1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   35 }
        MOVS     R0,R4
        BL       _ZN7CLUBaseD2Ev
        MOVS     R0,R4
        POP      {R4,PC}          ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//   36 
// 
// 124 bytes in section .text
// 
// 124 bytes of CODE memory
//
//Errors: none
//Warnings: none
