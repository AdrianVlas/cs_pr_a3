///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUAnd_8_1.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUAnd_8_1.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
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
//        files\v.12.x.y\Flash-Debug\List\LUAnd_8_1.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN _ZN7CLUBaseC2Ev
        EXTERN _ZN7CLUBaseD2Ev

        PUBLIC _Z10AND_Op_8_1Pv
        PUBLIC _ZN10CLUAnd_8_1C1Ecc
        PUBLIC _ZN10CLUAnd_8_1C1Ev
        PUBLIC _ZN10CLUAnd_8_1C2Ecc
        PUBLIC _ZN10CLUAnd_8_1C2Ev
        PUBLIC _ZN10CLUAnd_8_1D1Ev
        PUBLIC _ZN10CLUAnd_8_1D2Ev


        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUAnd_8_1::subobject CLUAnd_8_1()
_ZN10CLUAnd_8_1C2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN10CLUAnd_8_1C1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUAnd_8_1::subobject ~CLUAnd_8_1()
_ZN10CLUAnd_8_1D2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN10CLUAnd_8_1D1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CLUAnd_8_1::subobject CLUAnd_8_1(char, char)
_ZN10CLUAnd_8_1C2Ecc:
        PUSH     {R4,LR}
        MOVS     R4,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        BL       _ZN10CLUAnd_8_1C1Ecc
        POP      {R4,PC}          ;; return
// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\LUAnd_8_1.cpp
//    1 #ifdef VISUAL_STUDIO
//    2 #include "StdAfx.h"
//    3 #endif
//    4 #include "LUAnd_8_1.h"
//    5 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    6 void AND_Op_8_1    (void *pObj)
//    7 {
_Z10AND_Op_8_1Pv:
        PUSH     {R4}
//    8 	register long i,j;
//    9 	register char* pCh;
//   10 	
//   11 //CLUNot_1_1& refCLUNot_1_1 ;
//   12 //CLUAnd_8_1 *pCLUAnd_8_1 = (CLUAnd_8_1*)pObj;
//   13 	for(i = 0,pCh = (static_cast<CLUAnd_8_1*>(pObj))->arrPchIn[0],j = 1;i < 8; i++){
        MOVS     R4,#+0
        MOVS     R1,R4
        LDR      R4,[R0, #+24]
        MOVS     R3,R4
        MOVS     R4,#+1
        MOVS     R2,R4
??AND_Op_8_1_0:
        CMP      R1,#+8
        BGE.N    ??AND_Op_8_1_1
//   14 		if(pCh[i] == 0){
        LDRB     R4,[R1, R3]
        CMP      R4,#+0
        BNE.N    ??AND_Op_8_1_2
//   15 			j = 0;
        MOVS     R4,#+0
        MOVS     R2,R4
//   16 			break;
        B.N      ??AND_Op_8_1_1
//   17 		}
//   18 	}
??AND_Op_8_1_2:
        ADDS     R1,R1,#+1
        B.N      ??AND_Op_8_1_0
//   19 	//((CLUAnd_8_1*)pObj)->arrOut[0] = static_cast<char>(j);//(char)j;
//   20 	(reinterpret_cast<CLUAnd_8_1 *>(pObj))->arrOut[0] = static_cast<char>(j);
??AND_Op_8_1_1:
        STRB     R2,[R0, #+56]
//   21 	//((CLUAnd_8_1*)pObj)->arrOut[0] = static_cast<char>(j);
//   22 }
        POP      {R4}
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   23 CLUAnd_8_1::CLUAnd_8_1(void):CLUBase()
_ZN10CLUAnd_8_1C1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   24 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   25 }
        MOVS     R0,R4
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   26 CLUAnd_8_1::CLUAnd_8_1(char chM,char chI)//,LUOutDsc* pLUOutDsc)
_ZN10CLUAnd_8_1C1Ecc:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//   27 {
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   28 	chMaxIteratoin = chM;
        STRB     R5,[R4, #+4]
//   29 	chIteration = chI;
        STRB     R6,[R4, #+5]
//   30 	chNumInput  = static_cast<char>(shCLUAnd_8_1_AmtIn);//(char)8;
        MOVS     R0,#+8
        STRB     R0,[R4, #+6]
//   31 	chNumOutput = static_cast<char>(shCLUAnd_8_1_AmtOut);
        MOVS     R0,#+1
        STRB     R0,[R4, #+7]
//   32 	
//   33 	
//   34 	//Set Input parameters
//   35 	 //pIn =arrPchIn;
//   36 
//   37 	//Set OutPut parameters
//   38 	 //pOut =arrOut;
//   39 }
        MOVS     R0,R4
        POP      {R4-R6,PC}       ;; return
//   40 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   41 CLUAnd_8_1::~CLUAnd_8_1(void)
//   42 {
_ZN10CLUAnd_8_1D1Ev:
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
// 140 bytes in section .text
// 
// 140 bytes of CODE memory
//
//Errors: none
//Warnings: none
