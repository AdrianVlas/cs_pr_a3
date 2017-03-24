///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:59
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\Mft.cpp
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\Mft.cpp" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
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
//        files\v.12.x.y\Flash-Debug\List\Mft.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN PushTmrNode
        EXTERN _ZN7CLUBaseC2Ev
        EXTERN _ZN7CLUBaseD2Ev
        EXTERN chGlSem

        PUBLIC _Z6Mft_OpPv
        PUBLIC _ZN4CMft10UpdateCMftEv
        PUBLIC _ZN4CMft13LinkMftTimersEv
        PUBLIC _ZN4CMft8TWorkMftEll
        PUBLIC _ZN4CMft9TdelayMftEll
        PUBLIC _ZN4CMft9TpauseMftEl
        PUBLIC _ZN4CMftC1Ecc
        PUBLIC _ZN4CMftC1Ev
        PUBLIC _ZN4CMftC2Ecc
        PUBLIC _ZN4CMftC2Ev
        PUBLIC _ZN4CMftD1Ev
        PUBLIC _ZN4CMftD2Ev

// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\Mft.cpp
//    1 
//    2 #include "Mft.h"
//    3 
//    4 
//    5 
//    6 
//    7 
//    8 
//    9 
//   10 
//   11 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CMft::subobject CMft()
_ZN4CMftC2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN4CMftC1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CMft::subobject ~CMft()
_ZN4CMftD2Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN4CMftD1Ev
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// __code __interwork __softfp CMft::subobject CMft(char, char)
_ZN4CMftC2Ecc:
        PUSH     {R4,LR}
        MOVS     R4,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        BL       _ZN4CMftC1Ecc
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   12 CMft::CMft(void):CLUBase() {
_ZN4CMftC1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   13 m_NodeTpause.lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+56]
//   14 m_NodeTpause.next    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+60]
//   15 m_NodeTdelay.lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+64]
//   16 m_NodeTdelay.next    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+68]
//   17 m_NodeTWork .lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+72]
//   18 m_NodeTWork .next    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+76]
//   19 m_MftSuit.chTypeMft = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+40]
//   20 m_MftSuit.lTpause   = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+44]
//   21 m_MftSuit.lTdelay   = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+48]
//   22 m_MftSuit.lTWork    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+52]
//   23 m_chLinkedTimers    = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+33]
//   24 m_chStateTpause     = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+34]
//   25 m_chStateTdelay     = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+35]
//   26 m_chStateTWork      = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+36]
//   27 
//   28 
//   29 }
        MOVS     R0,R4
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   30 CMft::CMft(char chM,char chI){
_ZN4CMftC1Ecc:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
        MOVS     R0,R4
        BL       _ZN7CLUBaseC2Ev
//   31 	chMaxIteratoin = chM;
        STRB     R5,[R4, #+4]
//   32 	chIteration = chI;
        STRB     R6,[R4, #+5]
//   33 	
//   34 chNumInput  = static_cast<char>(shCLUMFT_x_y_AmtIn);//
        MOVS     R0,#+2
        STRB     R0,[R4, #+6]
//   35 chNumOutput = static_cast<char>(shCLUMFT_x_y_AmtOut);
        MOVS     R0,#+1
        STRB     R0,[R4, #+7]
//   36 	
//   37 	
//   38 
//   39 m_NodeTpause.lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+56]
//   40 m_NodeTpause.next    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+60]
//   41 m_NodeTdelay.lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+64]
//   42 m_NodeTdelay.next    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+68]
//   43 m_NodeTWork .lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+72]
//   44 m_NodeTWork .next    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+76]
//   45 m_MftSuit.chTypeMft = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+40]
//   46 m_MftSuit.lTpause   = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+44]
//   47 m_MftSuit.lTdelay   = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+48]
//   48 m_MftSuit.lTWork    = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+52]
//   49 m_chLinkedTimers    = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+33]
//   50 m_chStateTpause     = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+34]
//   51 m_chStateTdelay     = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+35]
//   52 m_chStateTWork      = 0;
        MOVS     R0,#+0
        STRB     R0,[R4, #+36]
//   53 
//   54 }
        MOVS     R0,R4
        POP      {R4-R6,PC}       ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   55 CMft::~CMft(void) {
_ZN4CMftD1Ev:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   56 }
        MOVS     R0,R4
        BL       _ZN7CLUBaseD2Ev
        MOVS     R0,R4
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   57 void CMft::UpdateCMft(void) {
//   58 //Set Input parameters
//   59 pIn = static_cast<void*>(arrPchIn);
_ZN4CMft10UpdateCMftEv:
        ADDS     R1,R0,#+24
        STR      R1,[R0, #+0]
//   60 //Set OutPut parameters
//   61 pOut = static_cast<void*>(arrOut);
        ADDS     R1,R0,#+32
        STR      R1,[R0, #+20]
//   62 //LinkMftTimers();
//   63 //pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_NOT;
//   64 
//   65 //Set Operation
//   66 //Set Type Operation
//   67 }
        BX       LR               ;; return
//   68 
//   69 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   70 long CMft::TpauseMft(long lActivKey) {
_ZN4CMft9TpauseMftEl:
        MOVS     R2,R0
//   71     
//   72     register long *plTmrVal = &m_NodeTpause.lTmrVal;
        ADDS     R3,R2,#+56
//   73     if (lActivKey) {
        CMP      R1,#+0
        BEQ.N    ??TpauseMft_0
//   74         if (m_chStateTpause == 0) {
        LDRB     R0,[R2, #+34]
        CMP      R0,#+0
        BNE.N    ??TpauseMft_1
//   75             lActivKey = m_MftSuit.lTpause; //Load Timer
        LDR      R0,[R2, #+44]
        MOVS     R1,R0
//   76             *plTmrVal = lActivKey;
        STR      R1,[R3, #+0]
//   77             if (*plTmrVal != lActivKey)
        LDR      R0,[R3, #+0]
        CMP      R0,R1
        BEQ.N    ??TpauseMft_2
//   78                 *plTmrVal = lActivKey; //Possible Clear in Int
        STR      R1,[R3, #+0]
//   79             m_chStateTpause = 1;
??TpauseMft_2:
        MOVS     R0,#+1
        STRB     R0,[R2, #+34]
        B.N      ??TpauseMft_3
//   80         } else {
//   81             lActivKey = *plTmrVal;
??TpauseMft_1:
        LDR      R0,[R3, #+0]
        MOVS     R1,R0
//   82             if (lActivKey == 0) {
        CMP      R1,#+0
        BNE.N    ??TpauseMft_3
//   83                 return 1; //End of Interval
        MOVS     R0,#+1
        B.N      ??TpauseMft_4
//   84             }
//   85         }
//   86         
//   87     } else {
//   88         ;
//   89         m_chStateTpause = 0;
??TpauseMft_0:
        MOVS     R0,#+0
        STRB     R0,[R2, #+34]
//   90         *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R3, #+0]
//   91     }
//   92     return 0;
??TpauseMft_3:
        MOVS     R0,#+0
??TpauseMft_4:
        BX       LR               ;; return
//   93 }
//   94 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   95 long CMft::TdelayMft(long lResetKey, long lInKey) {
_ZN4CMft9TdelayMftEll:
        PUSH     {R4}
        MOVS     R3,R0
//   96     register long *plTmrVal = &m_NodeTdelay.lTmrVal;
        ADDS     R4,R3,#+64
//   97 	
//   98     if (lResetKey == 0) {
        CMP      R1,#+0
        BNE.N    ??TdelayMft_0
//   99         if (lInKey) {
        CMP      R2,#+0
        BEQ.N    ??TdelayMft_1
//  100             lInKey = m_MftSuit.lTdelay;
        LDR      R0,[R3, #+48]
        MOVS     R2,R0
//  101             *plTmrVal = lInKey;
        STR      R2,[R4, #+0]
//  102             if (*plTmrVal != lInKey)
        LDR      R0,[R4, #+0]
        CMP      R0,R2
        BEQ.N    ??TdelayMft_2
//  103                 *plTmrVal = lInKey; //lResetKey == 0!
        STR      R2,[R4, #+0]
//  104 			m_chStateTdelay = 1;//Activated
??TdelayMft_2:
        MOVS     R0,#+1
        STRB     R0,[R3, #+35]
//  105             return 1;
        MOVS     R0,#+1
        B.N      ??TdelayMft_3
//  106        	
//  107         } else {
//  108             if (m_chStateTdelay == 1) {//Activated
??TdelayMft_1:
        LDRB     R0,[R3, #+35]
        CMP      R0,#+1
        BNE.N    ??TdelayMft_0
//  109                 lInKey = *plTmrVal;
        LDR      R0,[R4, #+0]
        MOVS     R2,R0
//  110                 if (lInKey != 0)
        CMP      R2,#+0
        BEQ.N    ??TdelayMft_4
//  111                     return 1; //
        MOVS     R0,#+1
        B.N      ??TdelayMft_3
//  112                 else {
//  113                     lResetKey = 1;
??TdelayMft_4:
        MOVS     R0,#+1
        MOVS     R1,R0
//  114                 }
//  115             }
//  116 
//  117         }
//  118     }
//  119     if (lResetKey) {
??TdelayMft_0:
        CMP      R1,#+0
        BEQ.N    ??TdelayMft_5
//  120         m_chStateTdelay = 0;
        MOVS     R0,#+0
        STRB     R0,[R3, #+35]
//  121         *plTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+0]
//  122     }
//  123     return 0;
??TdelayMft_5:
        MOVS     R0,#+0
??TdelayMft_3:
        POP      {R4}
        BX       LR               ;; return
//  124 }
//  125 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  126 long CMft::TWorkMft(long lResetKey, long lInKey) {
_ZN4CMft8TWorkMftEll:
        PUSH     {R4}
        MOVS     R3,R0
//  127     register long *plTmrVal = &m_NodeTWork .lTmrVal;
        ADDS     R4,R3,#+72
//  128 	
//  129     if (lResetKey == 0) {
        CMP      R1,#+0
        BNE.N    ??TWorkMft_0
//  130         if (lInKey) {
        CMP      R2,#+0
        BEQ.N    ??TWorkMft_1
//  131             if (m_chStateTWork == 0) {
        LDRB     R0,[R3, #+36]
        CMP      R0,#+0
        BNE.N    ??TWorkMft_2
//  132                 lInKey = m_MftSuit.lTWork;
        LDR      R0,[R3, #+52]
        MOVS     R2,R0
//  133                 *plTmrVal = lInKey;
        STR      R2,[R4, #+0]
//  134                 if (*plTmrVal != lInKey)
        LDR      R0,[R4, #+0]
        CMP      R0,R2
        BEQ.N    ??TWorkMft_3
//  135                     *plTmrVal = lInKey;
        STR      R2,[R4, #+0]
//  136                 m_chStateTWork = 1;
??TWorkMft_3:
        MOVS     R0,#+1
        STRB     R0,[R3, #+36]
//  137                 return 1;
        MOVS     R0,#+1
        B.N      ??TWorkMft_4
//  138             } else {
//  139                 lInKey = *plTmrVal;
??TWorkMft_2:
        LDR      R0,[R4, #+0]
        MOVS     R2,R0
//  140                 if (lInKey != 0)
        CMP      R2,#+0
        BEQ.N    ??TWorkMft_0
//  141                     return 1; //
        MOVS     R0,#+1
        B.N      ??TWorkMft_4
//  142             }
//  143         } else {
//  144             if (m_chStateTWork == 1) {//Activated
??TWorkMft_1:
        LDRB     R0,[R3, #+36]
        CMP      R0,#+1
        BNE.N    ??TWorkMft_0
//  145                 lInKey = *plTmrVal;
        LDR      R0,[R4, #+0]
        MOVS     R2,R0
//  146                 if (lInKey != 0)
        CMP      R2,#+0
        BEQ.N    ??TWorkMft_5
//  147                     return 1; //
        MOVS     R0,#+1
        B.N      ??TWorkMft_4
//  148                 else
//  149                     lResetKey = 1;
??TWorkMft_5:
        MOVS     R0,#+1
        MOVS     R1,R0
//  150             }
//  151         }
//  152     }
//  153     if (lResetKey) {
??TWorkMft_0:
        CMP      R1,#+0
        BEQ.N    ??TWorkMft_6
//  154         m_chStateTWork = 0;
        MOVS     R0,#+0
        STRB     R0,[R3, #+36]
//  155         *plTmrVal = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+0]
//  156     }    
//  157     return 0;
??TWorkMft_6:
        MOVS     R0,#+0
??TWorkMft_4:
        POP      {R4}
        BX       LR               ;; return
//  158 }
//  159 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  160 long CMft::LinkMftTimers(void) {
_ZN4CMft13LinkMftTimersEv:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
//  161     register long i = 0;
        MOVS     R5,#+0
//  162     //Insert TpauseMft
//  163     chGlSem++;
        LDR.N    R0,??DataTable0
        LDRB     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.N    R1,??DataTable0
        STRB     R0,[R1, #+0]
//  164     
//  165     if (PushTmrNode(&m_NodeTpause)) {//static_cast<void*>(
        ADDS     R0,R4,#+56
        BL       PushTmrNode
        CMP      R0,#+0
        BEQ.N    ??LinkMftTimers_0
//  166         i++;
        ADDS     R5,R5,#+1
//  167         m_chLinkedTimers |= 2;
        LDRB     R0,[R4, #+33]
        ORRS     R0,R0,#0x2
        STRB     R0,[R4, #+33]
//  168     }
//  169     //Insert TdelayMft
//  170     if (PushTmrNode(&m_NodeTdelay)) {//static_cast<void*>(
??LinkMftTimers_0:
        ADDS     R0,R4,#+64
        BL       PushTmrNode
        CMP      R0,#+0
        BEQ.N    ??LinkMftTimers_1
//  171         i++;
        ADDS     R5,R5,#+1
//  172         m_chLinkedTimers |= 4;
        LDRB     R0,[R4, #+33]
        ORRS     R0,R0,#0x4
        STRB     R0,[R4, #+33]
//  173     }
//  174     //Insert TWorkMft 
//  175     if (PushTmrNode(&m_NodeTWork)) {//static_cast<void*>(
??LinkMftTimers_1:
        ADDS     R0,R4,#+72
        BL       PushTmrNode
        CMP      R0,#+0
        BEQ.N    ??LinkMftTimers_2
//  176         i++;
        ADDS     R5,R5,#+1
//  177         m_chLinkedTimers |= 8;
        LDRB     R0,[R4, #+33]
        ORRS     R0,R0,#0x8
        STRB     R0,[R4, #+33]
//  178     }
//  179     chGlSem--;
??LinkMftTimers_2:
        LDR.N    R0,??DataTable0
        LDRB     R0,[R0, #+0]
        SUBS     R0,R0,#+1
        LDR.N    R1,??DataTable0
        STRB     R0,[R1, #+0]
//  180     return i;
        MOVS     R0,R5
        POP      {R1,R4,R5,PC}    ;; return
//  181 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0:
        DC32     chGlSem
//  182 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  183 void Mft_Op(void *pObj){
_Z6Mft_OpPv:
        PUSH     {R3-R7,LR}
        MOVS     R4,R0
//  184 
//  185     register long i, j;
//  186     //register char* pCh;
//  187 	CMft& rCMft = *(static_cast<CMft*>(pObj));
        MOVS     R7,R4
//  188 	i = static_cast<long>(*(rCMft.arrPchIn[0]));
        LDR      R0,[R7, #+24]
        LDRB     R0,[R0, #+0]
        MOVS     R5,R0
//  189 	j = rCMft.TpauseMft(i);
        MOVS     R1,R5
        MOVS     R0,R7
        BL       _ZN4CMft9TpauseMftEl
        MOVS     R6,R0
//  190 	i = static_cast<long>(*(rCMft.arrPchIn[1]));//Reset
        LDR      R0,[R7, #+28]
        LDRB     R0,[R0, #+0]
        MOVS     R5,R0
//  191 	if(rCMft.m_MftSuit.chTypeMft == 1){
        LDRB     R0,[R7, #+40]
        CMP      R0,#+1
        BNE.N    ??Mft_Op_0
//  192 		
//  193 		i = rCMft.TWorkMft(i,j);
        MOVS     R2,R6
        MOVS     R1,R5
        MOVS     R0,R7
        BL       _ZN4CMft8TWorkMftEll
        MOVS     R5,R0
        B.N      ??Mft_Op_1
//  194 	}
//  195 	else{
//  196 		i = rCMft.TdelayMft(i,j);
??Mft_Op_0:
        MOVS     R2,R6
        MOVS     R1,R5
        MOVS     R0,R7
        BL       _ZN4CMft9TdelayMftEll
        MOVS     R5,R0
//  197 	}
//  198 rCMft.arrOut[0] = static_cast<char>(i);
??Mft_Op_1:
        STRB     R5,[R7, #+32]
//  199 }
        POP      {R0,R4-R7,PC}    ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//  200 
//  201 
//  202 
// 
// 678 bytes in section .text
// 
// 678 bytes of CODE memory
//
//Errors: none
//Warnings: none
