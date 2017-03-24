///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\InPoint.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\InPoint.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
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
//        files\v.12.x.y\Flash-Debug\List\InPoint.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN _ZN11BaseInPointC2Ev
        EXTERN _ZN11BaseInPointD2Ev

        PUBLIC _ZN7InPointC1Ev
        PUBLIC _ZN7InPointC2Ev
        PUBLIC _ZN7InPointD1Ev
        PUBLIC _ZN7InPointD2Ev

// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\InPoint.cpp
//    1 #ifdef VISUAL_STUDIO
//    2 #include "StdAfx.h"
//    3 #endif
//    4 #include "InPoint.h"
//    5 
//    6 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp InPoint::subobject InPoint()
_ZN7InPointC2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN7InPointC1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp InPoint::subobject ~InPoint()
_ZN7InPointD2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN7InPointD1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    7 InPoint::InPoint(void)
_ZN7InPointC1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//    8 {
        MOVS     R0,R4
        BL       _ZN11BaseInPointC2Ev
//    9 }
        MOVS     R0,R4
        POP      {R4,PC}          ;; return
//   10 
//   11 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   12 InPoint::~InPoint(void)
//   13 {
_ZN7InPointD1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   14 }
        MOVS     R0,R4
        BL       _ZN11BaseInPointD2Ev
        MOVS     R0,R4
        POP      {R4,PC}          ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// 
// 52 bytes in section .text
// 
// 52 bytes of CODE memory
//
//Errors: none
//Warnings: none
