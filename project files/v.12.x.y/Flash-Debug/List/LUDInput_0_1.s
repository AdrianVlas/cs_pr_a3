///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUDInput_0_1.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUDInput_0_1.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX
//        -D USE_USB_OTG_FS -D SYSTEM_VIEWER_ENABLE -lc
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
//        files\v.12.x.y\Flash-Debug\List\LUDInput_0_1.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN _ZN7CLUBaseC2Ev
        EXTERN _ZN7CLUBaseD2Ev

        PUBLIC _Z10READ_DI_OpPv
        PUBLIC _Z11READ_Op_0_1Pv
        PUBLIC _ZN13CLUDInput_0_1C1Ecc
        PUBLIC _ZN13CLUDInput_0_1C1Ev
        PUBLIC _ZN13CLUDInput_0_1C2Ecc
        PUBLIC _ZN13CLUDInput_0_1C2Ev
        PUBLIC _ZN13CLUDInput_0_1D1Ev
        PUBLIC _ZN13CLUDInput_0_1D2Ev


        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUDInput_0_1::subobject CLUDInput_0_1()
_ZN13CLUDInput_0_1C2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN13CLUDInput_0_1C1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUDInput_0_1::subobject ~CLUDInput_0_1()
_ZN13CLUDInput_0_1D2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN13CLUDInput_0_1D1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUDInput_0_1::subobject CLUDInput_0_1(char, char)
_ZN13CLUDInput_0_1C2Ecc:
        PUSH     {R4,LR}
        MOVS     R4,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        BL       _ZN13CLUDInput_0_1C1Ecc
        POP      {R4,PC}          ;; return
// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\LUDInput_0_1.cpp
//    1 #ifdef VISUAL_STUDIO
//    2 #include "StdAfx.h"
//    3 #endif
//    4 #include "LUDInput_0_1.h"

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    5 void READ_Op_0_1(void *pObj)
//    6 {
//    7 	//CLUNot_1_1& refCLUNot_1_1 = pObj;
//    8 //	CLUDInput_0_1 *pCLUDInput_0_1 = (CLUDInput_0_1*)pObj;
//    9 
//   10 }
_Z11READ_Op_0_1Pv:
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   11 void READ_DI_Op(void *pObj)
//   12 {
//   13 	//CLUNot_1_1& refCLUNot_1_1 = pObj;
//   14 	CLUDInput_0_1 *pCLUDInput_0_1 = reinterpret_cast<CLUDInput_0_1 *>(pObj);
//   15 	pCLUDInput_0_1->arrOut[0] = 
//   16 	static_cast<char>(pCLUDInput_0_1->shLUBieldOrdNum);//Any value from Input
_Z10READ_DI_OpPv:
        LDRH     R1,[R0, #+14]
        STRB     R1,[R0, #+24]
//   17 
//   18 }
        BX       LR               ;; return
//   19 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   20 CLUDInput_0_1::CLUDInput_0_1(void)
_ZN13CLUDInput_0_1C1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   21 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   22 }
        MOVS     R0,R4
        POP      {R4,PC}          ;; return
//   23 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   24 CLUDInput_0_1::CLUDInput_0_1(char chM,char chI)//,LUOutDsc* pLUOutDsc)
_ZN13CLUDInput_0_1C1Ecc:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//   25 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   26 	chMaxIteratoin = chM;
        STRB     R5,[R4, #+4]
//   27 	chIteration = chI;
        STRB     R6,[R4, #+5]
//   28 	chNumInput  = static_cast<char>(shCLUDInput_0_1_AmtIn );
        MOVS     R0,#+0
        STRB     R0,[R4, #+6]
//   29 	chNumOutput = static_cast<char>(shCLUDInput_0_1_AmtOut);
        MOVS     R0,#+1
        STRB     R0,[R4, #+7]
//   30 	//chTypeLogicFunction = LU_OP_READ_DI;
//   31 	//LogicFunc  = READ_DI_Op;//???
//   32 
//   33 	//Set Input parameters
//   34 
//   35 
//   36 
//   37 	//Set OutPut parameters
//   38 	//pOut = (void*)arrOut;
//   39 }
        MOVS     R0,R4
        POP      {R4-R6,PC}       ;; return
//   40 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   41 CLUDInput_0_1::~CLUDInput_0_1(void)
//   42 {
_ZN13CLUDInput_0_1D1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   43 }
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
// 106 bytes in section .text
// 
// 106 bytes of CODE memory
//
//Errors: none
//Warnings: none
