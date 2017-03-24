///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUAlt.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUAlt.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
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
//        files\v.12.x.y\Flash-Debug\List\LUAlt.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN PushTmrNode
        EXTERN _ZN7CLUBaseC2Ev
        EXTERN _ZN7CLUBaseD2Ev
        EXTERN chGlSem

        PUBLIC _Z11PulseAlt_OpPv
        PUBLIC _ZN16CPulseAlternator15UpdateCPulseAltEv
        PUBLIC _ZN16CPulseAlternator17LinkPulseAltTimerEv
        PUBLIC _ZN16CPulseAlternator4TAltEl
        PUBLIC _ZN16CPulseAlternatorC1Ecc
        PUBLIC _ZN16CPulseAlternatorC1Ev
        PUBLIC _ZN16CPulseAlternatorC2Ecc
        PUBLIC _ZN16CPulseAlternatorC2Ev
        PUBLIC _ZN16CPulseAlternatorD1Ev
        PUBLIC _ZN16CPulseAlternatorD2Ev

// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\LUAlt.cpp
//    1 
//    2 #include "LUAlt.hpp"
//    3 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CPulseAlternator::subobject CPulseAlternator()
_ZN16CPulseAlternatorC2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN16CPulseAlternatorC1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CPulseAlternator::subobject CPulseAlternator(char, char)
_ZN16CPulseAlternatorC2Ecc:
        PUSH     {R4,LR}
        MOVS     R4,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        BL       _ZN16CPulseAlternatorC1Ecc
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CPulseAlternator::subobject ~CPulseAlternator()
_ZN16CPulseAlternatorD2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN16CPulseAlternatorD1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    4 CPulseAlternator::CPulseAlternator(void) :CLUBase() {
_ZN16CPulseAlternatorC1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//    5 m_chLinkedTimers = 0; //Field bit
        MOVS     R0,#+0
        STRB     R0,[R4, #+25]
//    6 m_chStateT       = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+26]
//    7 m_PulseAltCfgSuit.shTAlternator = 0;
        MOVS     R0,#+0
        STRH     R0,[R4, #+28]
//    8 m_NodeTicAlt.lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+32]
//    9 m_NodeTicAlt.next    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+36]
//   10 }
        MOVS     R0,R4
        POP      {R4,PC}          ;; return
//   11 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   12 CPulseAlternator::~CPulseAlternator(void) {
_ZN16CPulseAlternatorD1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   13 }
        MOVS     R0,R4
        BL       _ZN7CLUBaseD2Ev
        MOVS     R0,R4
        POP      {R4,PC}          ;; return
//   14 
//   15 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   16 CPulseAlternator::CPulseAlternator(char chM,char chI)  {
_ZN16CPulseAlternatorC1Ecc:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   17 	chMaxIteratoin = chM;
        STRB     R5,[R4, #+4]
//   18 	chIteration = chI;
        STRB     R6,[R4, #+5]
//   19 	
//   20 chNumInput  = static_cast<char>(shCLUPulseAlternator_x_y_AmtIn);//
        MOVS     R0,#+0
        STRB     R0,[R4, #+6]
//   21 chNumOutput = static_cast<char>(shCLUPulseAlternator_x_y_AmtOut);
        MOVS     R0,#+1
        STRB     R0,[R4, #+7]
//   22 	
//   23 }
        MOVS     R0,R4
        POP      {R4-R6,PC}       ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   24 void CPulseAlternator::UpdateCPulseAlt(void){
//   25 //Set Input parameters
//   26 pIn = static_cast<void*>(arrPchIn);
_ZN16CPulseAlternator15UpdateCPulseAltEv:
        ADDS     R1,R0,#+24
        STR      R1,[R0, #+0]
//   27 //Set OutPut parameters
//   28 pOut = static_cast<void*>(arrOut);
        ADDS     R1,R0,#+24
        STR      R1,[R0, #+20]
//   29 //LinkMftTimers();
//   30 //pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_NOT;
//   31 
//   32 //Set Operation
//   33 //Set Type Operation
//   34 }
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   35 long CPulseAlternator::LinkPulseAltTimer(void) {
_ZN16CPulseAlternator17LinkPulseAltTimerEv:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
//   36     register long i = 0;
        MOVS     R5,#+0
//   37     //Insert TpauseMft
//   38     chGlSem++;
        LDR.N    R0,??DataTable0
        LDRB     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.N    R1,??DataTable0
        STRB     R0,[R1, #+0]
//   39     
//   40     if (PushTmrNode(&m_NodeTicAlt)) {//static_cast<void*>(
        ADDS     R0,R4,#+32
        BL       PushTmrNode
        CMP      R0,#+0
        BEQ.N    ??LinkPulseAltTimer_0
//   41         i++;
        ADDS     R5,R5,#+1
//   42         m_chLinkedTimers |= 2;
        LDRB     R0,[R4, #+25]
        ORRS     R0,R0,#0x2
        STRB     R0,[R4, #+25]
//   43     }
//   44 
//   45     
//   46     chGlSem--;
??LinkPulseAltTimer_0:
        LDR.N    R0,??DataTable0
        LDRB     R0,[R0, #+0]
        SUBS     R0,R0,#+1
        LDR.N    R1,??DataTable0
        STRB     R0,[R1, #+0]
//   47     return i;
        MOVS     R0,R5
        POP      {R1,R4,R5,PC}    ;; return
//   48 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0:
        DC32     chGlSem

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   49 long CPulseAlternator::TAlt(long lActivKey){
_ZN16CPulseAlternator4TAltEl:
        MOVS     R2,R0
//   50   
//   51     register long *plTmrVal = &m_NodeTicAlt.lTmrVal;
        ADDS     R3,R2,#+32
//   52     if (lActivKey) {
        CMP      R1,#+0
        BNE.N    ??TAlt_0
//   53 	
//   54 	} else {
//   55         ;
//   56         m_chStateT = 0;
        MOVS     R0,#+0
        STRB     R0,[R2, #+26]
//   57         *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R3, #+0]
//   58     }
//   59     return 0;
??TAlt_0:
        MOVS     R0,#+0
        BX       LR               ;; return
//   60 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   61 void PulseAlt_Op(void *pObj){
_Z11PulseAlt_OpPv:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
//   62 
//   63     register long i, j;
//   64 
//   65 	CPulseAlternator& rPulseAlt = *(static_cast<CPulseAlternator*>(pObj));
//   66 	j = 0;
        MOVS     R0,#+0
        MOVS     R6,R0
//   67 	i = rPulseAlt.TAlt(j);
        MOVS     R1,R6
        MOVS     R0,R4
        BL       _ZN16CPulseAlternator4TAltEl
        MOVS     R5,R0
//   68 	
//   69 rPulseAlt.arrOut[0] = static_cast<char>(i);
        STRB     R5,[R4, #+24]
//   70 
//   71 }
        POP      {R4-R6,PC}       ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// 
// 232 bytes in section .text
// 
// 232 bytes of CODE memory
//
//Errors: none
//Warnings: none
