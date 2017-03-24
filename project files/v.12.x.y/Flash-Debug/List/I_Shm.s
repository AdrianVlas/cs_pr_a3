///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\I_Shm.c
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\I_Shm.c" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
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
//        files\v.12.x.y\..\..\SystemView\SEGGER\" -On --use_c++_inline
//        --require_prototypes -I G:\PRG\IAR7_50_2\arm\CMSIS\Include\ -D
//        ARM_MATH_CM3
//    List file    =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\project
//        files\v.12.x.y\Flash-Debug\List\I_Shm.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1



        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\I_Shm.c
//    1 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//    2 //``````````````````````````````````````````````````````````````````````````````````
//    3 //==================================================================================
//    4 //--- 			 Interface function for CPP Schematic     -----------
//    5 //==================================================================================
//    6 //..................................................................................
//    7 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//    8 //~~~  
//    9 //~~~  
//   10 //~~~  
//   11 //~~~  
//   12 //~~~  
//   13 //~~~  
//   14 //~~~  
//   15 //~~~  
//   16 //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//   17 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//   18 
//   19 
//   20 
//   21 
//   22 
//   23 
//   24 
//   25 
//   26 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//   27 //---
//   28 //extern char GetCmdStateVcs(void *p_in_param);
//   29 //..................................................................................
//   30 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//   31 //~~~                             
//   32 //~~~                             
//   33 //``````````````````````````````````````````````````````````````````````````````````
//   34 //~~~   
//   35 //~~~   
//   36 //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//   37 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//   38 ///////////////////////////////////////////////////////////////////////////////////
//   39 //=================================================================================
//   40 //Body func                                                                
//   41 //=================================================================================
//   42 //char GetCmdStateVcs(void *p_in_param)
//   43 //{
//   44 //    register I32 i; 
//   45 //	
//   46 //}
//   47 //----------------------------------------------------------------------------------
// 
//
// 
//
//
//Errors: none
//Warnings: none
