///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:54
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\BaseInPoint.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\BaseInPoint.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX
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
//        files\v.12.x.y\Flash-Debug\List\BaseInPoint.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        PUBLIC _ZN11BaseInPointC1ERS_
        PUBLIC _ZN11BaseInPointC1Ecccc
        PUBLIC _ZN11BaseInPointC1Ev
        PUBLIC _ZN11BaseInPointC2ERS_
        PUBLIC _ZN11BaseInPointC2Ecccc
        PUBLIC _ZN11BaseInPointC2Ev
        PUBLIC _ZN11BaseInPointD1Ev
        PUBLIC _ZN11BaseInPointD2Ev
        PUBLIC _ZN11BaseInPointaSERKS_
        PUBLIC shOrdNumBaseInPoint

// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\BaseInPoint.cpp
//    1 #ifdef VISUAL_STUDIO
//    2 #include "StdAfx.h"
//    3 #endif
//    4 #include "BaseInPoint.h"
//    5 

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
        DATA
//    6  short shOrdNumBaseInPoint = 0;
shOrdNumBaseInPoint:
        DS8 2

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp BaseInPoint::subobject BaseInPoint()
_ZN11BaseInPointC2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN11BaseInPointC1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp BaseInPoint::subobject ~BaseInPoint()
_ZN11BaseInPointD2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN11BaseInPointD1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp BaseInPoint::subobject BaseInPoint(BaseInPoint &)
_ZN11BaseInPointC2ERS_:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN11BaseInPointC1ERS_
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp BaseInPoint::subobject BaseInPoint(char, char, char, char)
_ZN11BaseInPointC2Ecccc:
        PUSH     {R4,LR}
        SUB      SP,SP,#+8
        MOVS     R4,R0
        LDR      R0,[SP, #+16]
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        STR      R0,[SP, #+0]
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        BL       _ZN11BaseInPointC1Ecccc
        POP      {R1,R2,R4,PC}    ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    7 BaseInPoint::BaseInPoint(void)
//    8 {
//    9 	chMaxIteratoin = 0;
_ZN11BaseInPointC1Ev:
        MOVS     R1,#+0
        STRB     R1,[R0, #+0]
//   10 	chIteration    = 0;
        MOVS     R1,#+0
        STRB     R1,[R0, #+1]
//   11 	chState        = 0;
        MOVS     R1,#+0
        STRB     R1,[R0, #+2]
//   12 	chReqCalc      = 0;
        MOVS     R1,#+0
        STRB     R1,[R0, #+3]
//   13 	shOrderNumber  = 0;
        MOVS     R1,#+0
        STRH     R1,[R0, #+4]
//   14 	
//   15 }
        BX       LR               ;; return
//   16 //Copy constructor

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   17 BaseInPoint::BaseInPoint(BaseInPoint&cl)
//   18 {
//   19 	chMaxIteratoin = cl.chMaxIteratoin;
_ZN11BaseInPointC1ERS_:
        LDRB     R2,[R1, #+0]
        STRB     R2,[R0, #+0]
//   20 	chIteration    = cl.chIteration   ;
        LDRB     R2,[R1, #+1]
        STRB     R2,[R0, #+1]
//   21 	chState        = cl.chState       ;
        LDRB     R2,[R1, #+2]
        STRB     R2,[R0, #+2]
//   22 	chReqCalc      = cl.chReqCalc     ;
        LDRB     R2,[R1, #+3]
        STRB     R2,[R0, #+3]
//   23 	shOrderNumber  = ++shOrdNumBaseInPoint;
        LDR.N    R2,??DataTable2
        LDRH     R2,[R2, #+0]
        ADDS     R2,R2,#+1
        LDR.N    R3,??DataTable2
        STRH     R2,[R3, #+0]
        LDR.N    R2,??DataTable2
        LDRH     R2,[R2, #+0]
        STRH     R2,[R0, #+4]
//   24 }
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   25 BaseInPoint::BaseInPoint(char chM = 0,char chI = 0,char chS = 0,char chR =0)
//   26 {
_ZN11BaseInPointC1Ecccc:
        PUSH     {R4-R6}
        LDR      R4,[SP, #+12]
//   27 	chMaxIteratoin = chM;
        STRB     R1,[R0, #+0]
//   28 	chIteration    = chI;
        STRB     R2,[R0, #+1]
//   29 	chState        = chS;
        STRB     R3,[R0, #+2]
//   30 	chReqCalc      = chR;
        STRB     R4,[R0, #+3]
//   31 	shOrderNumber  = ++shOrdNumBaseInPoint;
        LDR.N    R5,??DataTable2
        LDRH     R5,[R5, #+0]
        ADDS     R5,R5,#+1
        LDR.N    R6,??DataTable2
        STRH     R5,[R6, #+0]
        LDR.N    R5,??DataTable2
        LDRH     R5,[R5, #+0]
        STRH     R5,[R0, #+4]
//   32 }
        POP      {R4-R6}
        BX       LR               ;; return
//   33 //Copy assignment

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   34 BaseInPoint& BaseInPoint::operator= (const BaseInPoint&cl)
//   35 {
//   36 	chMaxIteratoin = cl.chMaxIteratoin;
_ZN11BaseInPointaSERKS_:
        LDRB     R2,[R1, #+0]
        STRB     R2,[R0, #+0]
//   37 	chIteration    = cl.chIteration   ;
        LDRB     R2,[R1, #+1]
        STRB     R2,[R0, #+1]
//   38 	chState        = cl.chState       ;
        LDRB     R2,[R1, #+2]
        STRB     R2,[R0, #+2]
//   39 	chReqCalc      = cl.chReqCalc     ;
        LDRB     R2,[R1, #+3]
        STRB     R2,[R0, #+3]
//   40 	shOrderNumber  = ++shOrdNumBaseInPoint;
        LDR.N    R2,??DataTable2
        LDRH     R2,[R2, #+0]
        ADDS     R2,R2,#+1
        LDR.N    R3,??DataTable2
        STRH     R2,[R3, #+0]
        LDR.N    R2,??DataTable2
        LDRH     R2,[R2, #+0]
        STRH     R2,[R0, #+4]
//   41 	return *this;
        BX       LR               ;; return
//   42 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2:
        DC32     shOrdNumBaseInPoint
//   43 
//   44 //Move constructor
//   45 
//   46 //Move assignment
//   47 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   48 BaseInPoint::~BaseInPoint(void)
//   49 {
//   50 }
_ZN11BaseInPointD1Ev:
        BX       LR               ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// 
//   2 bytes in section .bss
// 190 bytes in section .text
// 
// 190 bytes of CODE memory
//   2 bytes of DATA memory
//
//Errors: none
//Warnings: none
