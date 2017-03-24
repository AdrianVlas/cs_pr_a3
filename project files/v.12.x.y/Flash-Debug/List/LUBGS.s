///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:56
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUBGS.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\LUBGS.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
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
//        files\v.12.x.y\Flash-Debug\List\LUBGS.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN PushTmrNode
        EXTERN _ZN7CLUBaseC2Ev
        EXTERN _ZN7CLUBaseD2Ev
        EXTERN chGlSem
        EXTERN measurement

        PUBLIC _Z8BGSig_OpPv
        PUBLIC _ZN6CBGSig10EvalNNC_CHEl
        PUBLIC _ZN6CBGSig10EvalNNP_CHEl
        PUBLIC _ZN6CBGSig11EvalNNC_NCHEl
        PUBLIC _ZN6CBGSig11EvalNNP_NCHEl
        PUBLIC _ZN6CBGSig12UpdateCBGSigEv
        PUBLIC _ZN6CBGSig13EvalDeltaIbusEv
        PUBLIC _ZN6CBGSig15LinkBGSigTimersEv
        PUBLIC _ZN6CBGSig16EvalDeltaIbusFixElll
        PUBLIC _ZN6CBGSig21CalcBusGrSigSchematicEv
        PUBLIC _ZN6CBGSig6EvalCEEl
        PUBLIC _ZN6CBGSig6EvalOCEv
        PUBLIC _ZN6CBGSig6lTWaitEl
        PUBLIC _ZN6CBGSig7EvalNCCEl
        PUBLIC _ZN6CBGSig7EvalNNMEll
        PUBLIC _ZN6CBGSig7EvalNNPEll
        PUBLIC _ZN6CBGSig7lTResetEl
        PUBLIC _ZN6CBGSig8EvalIctcElll
        PUBLIC _ZN6CBGSig8EvalIptpElll
        PUBLIC _ZN6CBGSigC1Ecc
        PUBLIC _ZN6CBGSigC1Ev
        PUBLIC _ZN6CBGSigC2Ecc
        PUBLIC _ZN6CBGSigC2Ev
        PUBLIC _ZN6CBGSigD1Ev
        PUBLIC _ZN6CBGSigD2Ev

// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\LUBGS.cpp
//    1 
//    2 #include "LUBGS.hpp"
//    3 #include "../inc/constants.h"
//    4 
//    5 #include <stdbool.h>
//    6 #include <math.h>
//    7 //#include <arm_math.h>
//    8 #include <stdlib.h>
//    9 #include "stm32f2xx.h"
//   10 #include "hw_config.h"
//   11 #include "../inc/macroses.h"
//   12 #include "../inc/type_definition.h"
//   13 #include "../inc/variables_external.h"//
//   14 
//   15 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CBGSig::subobject CBGSig()
_ZN6CBGSigC2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN6CBGSigC1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CBGSig::subobject ~CBGSig()
_ZN6CBGSigD2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN6CBGSigD1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CBGSig::subobject CBGSig(char, char)
_ZN6CBGSigC2Ecc:
        PUSH     {R4,LR}
        MOVS     R4,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        BL       _ZN6CBGSigC1Ecc
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   16 CBGSig::CBGSig(void):CLUBase()  {
_ZN6CBGSigC1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   17 m_NodeTWait.lTmrVal  = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+48]
//   18 m_NodeTWait.next     = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+52]
//   19 m_NodeTReset.lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+56]
//   20 m_NodeTReset.next    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+60]
//   21 
//   22 m_BGSigSuit.chStateGS  = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+32]
//   23 m_BGSigSuit.chCheckBgs = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+33]
//   24 m_BGSigSuit.lTWait     = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+36]
//   25 m_BGSigSuit.lTReset    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+40]
//   26 m_chLinkedTimers = 0; //Field bit
        MOVS     R0,#+0
        STRB     R0,[R4, #+25]
//   27 m_chStateTWait   = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+26]
//   28 m_chStateTReset  = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+27]
//   29 m_lIfix = m_lMeasIti_mn_1 = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+64]
        LDR      R0,[R4, #+64]
        STR      R0,[R4, #+68]
//   30 m_chNumberAnalogChanell = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+28]
//   31 }
        MOVS     R0,R4
        POP      {R4,PC}          ;; return
//   32 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   33 CBGSig::~CBGSig(void) {
_ZN6CBGSigD1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   34 }
        MOVS     R0,R4
        BL       _ZN7CLUBaseD2Ev
        MOVS     R0,R4
        POP      {R4,PC}          ;; return
//   35 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   36 CBGSig::CBGSig(char chM,char chI){
_ZN6CBGSigC1Ecc:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   37 	chMaxIteratoin = chM;
        STRB     R5,[R4, #+4]
//   38 	chIteration = chI;
        STRB     R6,[R4, #+5]
//   39 	
//   40 chNumInput  = static_cast<char>(shCLUBGSig_x_y_AmtIn);//
        MOVS     R0,#+0
        STRB     R0,[R4, #+6]
//   41 chNumOutput = static_cast<char>(shCLUBGSig_x_y_AmtOut);
        MOVS     R0,#+1
        STRB     R0,[R4, #+7]
//   42 m_NodeTWait.lTmrVal  = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+48]
//   43 m_NodeTWait.next     = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+52]
//   44 m_NodeTReset.lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+56]
//   45 m_NodeTReset.next    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+60]
//   46 
//   47 m_BGSigSuit.chStateGS  = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+32]
//   48 m_BGSigSuit.chCheckBgs = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+33]
//   49 m_BGSigSuit.lTWait     = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+36]
//   50 m_BGSigSuit.lTReset    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+40]
//   51 m_chLinkedTimers = 0; //Field bit
        MOVS     R0,#+0
        STRB     R0,[R4, #+25]
//   52 m_chStateTWait   = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+26]
//   53 m_chStateTReset  = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+27]
//   54 
//   55 
//   56 }
        MOVS     R0,R4
        POP      {R4-R6,PC}       ;; return
//   57 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   58 long CBGSig::LinkBGSigTimers(void) {
_ZN6CBGSig15LinkBGSigTimersEv:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
//   59     register long i = 0;
        MOVS     R5,#+0
//   60     //Insert TpauseMft
//   61     chGlSem++;
        LDR.N    R0,??DataTable1
        LDRB     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+0]
//   62     
//   63     if (PushTmrNode(&m_NodeTWait)) {//static_cast<void*>(
        ADDS     R0,R4,#+48
        BL       PushTmrNode
        CMP      R0,#+0
        BEQ.N    ??LinkBGSigTimers_0
//   64         i++;
        ADDS     R5,R5,#+1
//   65         m_chLinkedTimers |= 2;
        LDRB     R0,[R4, #+25]
        ORRS     R0,R0,#0x2
        STRB     R0,[R4, #+25]
//   66     }
//   67     //Insert TdelayMft
//   68     if (PushTmrNode(&m_NodeTReset)) {//static_cast<void*>(
??LinkBGSigTimers_0:
        ADDS     R0,R4,#+56
        BL       PushTmrNode
        CMP      R0,#+0
        BEQ.N    ??LinkBGSigTimers_1
//   69         i++;
        ADDS     R5,R5,#+1
//   70         m_chLinkedTimers |= 4;
        LDRB     R0,[R4, #+25]
        ORRS     R0,R0,#0x4
        STRB     R0,[R4, #+25]
//   71     }
//   72 
//   73     chGlSem--;
??LinkBGSigTimers_1:
        LDR.N    R0,??DataTable1
        LDRB     R0,[R0, #+0]
        SUBS     R0,R0,#+1
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+0]
//   74     return i;
        MOVS     R0,R5
        POP      {R1,R4,R5,PC}    ;; return
//   75 }
//   76 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   77 long CBGSig::lTWait(long lActivKey) {
_ZN6CBGSig6lTWaitEl:
        MOVS     R2,R0
//   78 
//   79     register long *plTmrVal = &m_NodeTWait.lTmrVal;
        ADDS     R3,R2,#+48
//   80     if (lActivKey) {
        CMP      R1,#+0
        BNE.N    ??lTWait_0
//   81 
//   82 
//   83 
//   84 
//   85 
//   86     } else {
//   87         ;
//   88 
//   89         *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R3, #+0]
//   90     }
//   91     return 0;
??lTWait_0:
        MOVS     R0,#+0
        BX       LR               ;; return
//   92 }
//   93 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   94 long CBGSig::lTReset(long lActivKey) {
_ZN6CBGSig7lTResetEl:
        MOVS     R2,R0
//   95     register long *plTmrVal = &m_NodeTReset.lTmrVal;
        ADDS     R3,R2,#+56
//   96     if (lActivKey) {
        CMP      R1,#+0
        BNE.N    ??lTReset_0
//   97 
//   98 
//   99 
//  100 
//  101     } else {
//  102         ;
//  103 
//  104         *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R3, #+0]
//  105     }
//  106     return 0;
??lTReset_0:
        MOVS     R0,#+0
        BX       LR               ;; return
//  107 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  108 void CBGSig::UpdateCBGSig(void) {
//  109 //Set Input parameters
//  110 pIn = static_cast<void*>(arrPchIn);
_ZN6CBGSig12UpdateCBGSigEv:
        ADDS     R1,R0,#+24
        STR      R1,[R0, #+0]
//  111 //Set OutPut parameters
//  112 pOut = static_cast<void*>(arrOut);
        ADDS     R1,R0,#+24
        STR      R1,[R0, #+20]
//  113 //LinkMftTimers();
//  114 //pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_NOT;
//  115 
//  116 //Set Operation
//  117 //Set Type Operation
//  118 }
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//  119 void BGSig_Op(void *pObj) {
_Z8BGSig_OpPv:
        PUSH     {R4,LR}
        MOVS     R4,R0
//  120     CBGSig& rCBGSig = *(static_cast<CBGSig*> (pObj));
//  121     asm(
//  122                 "bkpt 1"
//  123                 );
        bkpt 1
//  124     rCBGSig.CalcBusGrSigSchematic();
        MOVS     R0,R4
        BL       _ZN6CBGSig21CalcBusGrSigSchematicEv
//  125 }
        POP      {R4,PC}          ;; return
//  126 
//  127 #include "LUBgsp1.cpp"
//  128 static char chGLB_DTrg = 0;

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  129 void CBGSig::CalcBusGrSigSchematic(void){
_ZN6CBGSig21CalcBusGrSigSchematicEv:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
//  130 register long rl_Val,i;
//  131 
//  132 #pragma data_alignment=4
//  133 char arChIntermediaResult[(TOTAL_BGS_LU)];
//  134 i = EvalDeltaIbus();
        MOVS     R0,R4
        BL       _ZN6CBGSig13EvalDeltaIbusEv
        MOVS     R5,R0
//  135 //if( i == 1 && (arChIntermediaResult[StoreIfixTimeFix_1]) == 0)
//  136 //m_lIfix = 
//  137 }
        POP      {R0,R4,R5,PC}    ;; return
//  138 //long Ibus, long lTinterval

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  139 long CBGSig::EvalDeltaIbus(void) {
_ZN6CBGSig13EvalDeltaIbusEv:
        PUSH     {R4,R5}
        MOVS     R1,R0
//  140     register long i, j,Iti;
//  141     //Kc = Ucurr_power/Unom_power
//  142     //Num Analog Chanel
//  143     Iti = measurement[m_chNumberAnalogChanell];
        LDR.N    R4,??DataTable1_1
        LDRB     R5,[R1, #+28]
        LDR      R4,[R4, R5, LSL #+2]
        MOVS     R3,R4
//  144     if (Iti > m_lMeasIti_mn_1) {
        LDR      R4,[R1, #+64]
        CMP      R4,R3
        BGE.N    ??EvalDeltaIbus_0
//  145         j = Iti - m_lMeasIti_mn_1;
        LDR      R4,[R1, #+64]
        SUBS     R4,R3,R4
        MOVS     R2,R4
        B.N      ??EvalDeltaIbus_1
//  146     } else {
//  147         j = m_lMeasIti_mn_1 - Iti;
??EvalDeltaIbus_0:
        LDR      R4,[R1, #+64]
        SUBS     R4,R4,R3
        MOVS     R2,R4
//  148     }
//  149     i = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
??EvalDeltaIbus_1:
        LDR      R4,[R1, #+44]
        LDR.N    R5,??DataTable1_1
        LDR      R5,[R5, #+16]
        MULS     R4,R5,R4
        LDR.N    R5,??DataTable1_2  ;; 0x35b60
        UDIV     R4,R4,R5
        MOVS     R0,R4
//  150 	
//  151     if (j > i){
        CMP      R0,R2
        BGE.N    ??EvalDeltaIbus_2
//  152         m_lIfix = m_lMeasIti_mn_1;
        LDR      R4,[R1, #+64]
        STR      R4,[R1, #+68]
//  153         i = 1;
        MOVS     R4,#+1
        MOVS     R0,R4
        B.N      ??EvalDeltaIbus_3
//  154         }
//  155 	else i = 0;
??EvalDeltaIbus_2:
        MOVS     R4,#+0
        MOVS     R0,R4
//  156 	m_lMeasIti_mn_1 = Iti;
??EvalDeltaIbus_3:
        STR      R3,[R1, #+64]
//  157 	
//  158 
//  159     return i;
        POP      {R4,R5}
        BX       LR               ;; return
//  160 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1:
        DC32     chGlSem

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_1:
        DC32     measurement

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_2:
        DC32     0x35b60
//  161 // long CBGSig::StoreIfixTimeFix(long lTime, long lIbus, long lActive) {
//  162 // register long i;
//  163 
//  164 //     return 0;
//  165 // }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  166 long CBGSig::EvalDeltaIbusFix(long Ibus, long Ifix, long lActive){
_ZN6CBGSig16EvalDeltaIbusFixElll:
        PUSH     {R4}
        MOVS     R4,R0
//  167 register long i;
//  168 
//  169     return 0;
        MOVS     R0,#+0
        POP      {R4}
        BX       LR               ;; return
//  170 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  171 long CBGSig::EvalIptp (long lI, long lT, long lActive){
_ZN6CBGSig8EvalIptpElll:
        PUSH     {R4}
        MOVS     R4,R0
//  172 register long i;
//  173 
//  174     return 0;
        MOVS     R0,#+0
        POP      {R4}
        BX       LR               ;; return
//  175 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  176 long CBGSig::EvalIctc (long lI, long lT, long lActive){
_ZN6CBGSig8EvalIctcElll:
        PUSH     {R4}
        MOVS     R4,R0
//  177 register long i;
//  178 
//  179     return 0;
        MOVS     R0,#+0
        POP      {R4}
        BX       LR               ;; return
//  180 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  181 long CBGSig::EvalNNC_NCH(long lActivate){
_ZN6CBGSig11EvalNNC_NCHEl:
        MOVS     R2,R0
//  182 register long i;
//  183 
//  184     return 0;
        MOVS     R0,#+0
        BX       LR               ;; return
//  185 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  186 long CBGSig::EvalNNP_NCH(long lActivate){
_ZN6CBGSig11EvalNNP_NCHEl:
        MOVS     R2,R0
//  187 register long i;
//  188 
//  189     return 0;
        MOVS     R0,#+0
        BX       LR               ;; return
//  190 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  191 long CBGSig::EvalNNC_CH (long lActivate){
_ZN6CBGSig10EvalNNC_CHEl:
        MOVS     R2,R0
//  192 register long i;
//  193 
//  194     return 0;
        MOVS     R0,#+0
        BX       LR               ;; return
//  195 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  196 long CBGSig::EvalNNP_CH (long lActivate){
_ZN6CBGSig10EvalNNP_CHEl:
        MOVS     R2,R0
//  197 register long i;
//  198 
//  199     return 0;
        MOVS     R0,#+0
        BX       LR               ;; return
//  200 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  201 long CBGSig::EvalCE (long lActivate){
_ZN6CBGSig6EvalCEEl:
        MOVS     R2,R0
//  202 register long i;
//  203 
//  204     return 0;
        MOVS     R0,#+0
        BX       LR               ;; return
//  205 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  206 long CBGSig::EvalOC(void){
_ZN6CBGSig6EvalOCEv:
        MOVS     R1,R0
//  207 register long i;
//  208 
//  209     return 0;
        MOVS     R0,#+0
        BX       LR               ;; return
//  210 }
//  211 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  212 long CBGSig::EvalNNP(long lNNC, long lNNP){
_ZN6CBGSig7EvalNNPEll:
        MOVS     R3,R0
//  213 register long i;
//  214 
//  215     return 0;
        MOVS     R0,#+0
        BX       LR               ;; return
//  216 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  217 long CBGSig::EvalNNM(long lNNC, long lNNP){
_ZN6CBGSig7EvalNNMEll:
        MOVS     R3,R0
//  218 register long i;
//  219 
//  220     return 0;
        MOVS     R0,#+0
        BX       LR               ;; return
//  221 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  222 long CBGSig::EvalNCC(long lNCC){
_ZN6CBGSig7EvalNCCEl:
        MOVS     R2,R0
//  223 register long i;
//  224 
//  225     return 0;
        MOVS     R0,#+0
        BX       LR               ;; return
//  226 }

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//  227 
//  228 
//  229 
//  230 
// 
// 528 bytes in section .text
// 
// 528 bytes of CODE memory
//
//Errors: none
//Warnings: 16
