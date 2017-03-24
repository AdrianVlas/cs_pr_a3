///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.50.2.10312/W32 for ARM      24/Mar/2017  12:54:59
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\prtTmr.c
//    Command line =  
//        "G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working
//        files\v_A_shm\prtTmr.c" -D USE_STDPERIPH_DRIVER -D STM32F2XX -D
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
//        files\v.12.x.y\Flash-Debug\List\prtTmr.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN __aeabi_memclr4
        EXTERN __aeabi_memcpy4

        PUBLIC CH_AMOUNT_DI
        PUBLIC DiHrdStateUI32Bit
        PUBLIC DoStateUI32Bit
        PUBLIC HLSelectorTable
        PUBLIC IncreaseTmrList
        PUBLIC LedAuxOp1
        PUBLIC LedAuxOp2
        PUBLIC LedAuxOp3
        PUBLIC LedAuxOp4
        PUBLIC LedAuxOp5
        PUBLIC LedRawStateUI32Bit
        PUBLIC LedStateUI32Bit
        PUBLIC PCurrNode
        PUBLIC PopTmrNode
        PUBLIC PushTmrNode
        PUBLIC RdHrdIn
        PUBLIC SetHrdLed
        PUBLIC SetHrdOut
        PUBLIC TallingList
        PUBLIC TmrCalls
        PUBLIC UpdateStateDI
        PUBLIC arTimerDi
        PUBLIC arrFnPtr
        PUBLIC chCounterLedService
        PUBLIC chGbl_REL_1_6__ROWS_A_D__RW_VAL
        PUBLIC chGbl__DIN1_DIN5__RD_VAL
        PUBLIC chGbl__DIN6_DIN12__RD_VAL
        PUBLIC chGbl__LedColumns__RW_VAL
        PUBLIC chGbl__REL7_REL14__RD_VAL
        PUBLIC chGbl__REL7_REL14__RW_VAL
        PUBLIC chGbl__REL_1_6__RD_VAL
        PUBLIC chGlSem
        PUBLIC chNumIndependentParts
        PUBLIC pHeadTmrNode
        PUBLIC pTailTmrNode
        PUBLIC sDiCfg
        PUBLIC sh1MsRegisteredTimers
        PUBLIC uCh_MAX_Amt_1_MS_TMR


        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
?_0:
        DC8 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
        DC32 0, 0, 0, 0
// G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\prtTmr.c
//    1 
//    2 #include "prtTmr.h"

        SECTION `.rodata`:CONST:REORDER:NOROOT(0)
        DATA
//    3 const unsigned char uCh_MAX_Amt_1_MS_TMR  = 200;
uCh_MAX_Amt_1_MS_TMR:
        DC8 200
//    4 
//    5 
//    6 

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//    7 char chGlSem;
chGlSem:
        DS8 1
//    8 //==================================================================================
//    9 //---            Main file for service prt Timers     -----------
//   10 //==================================================================================
//   11 //..................................................................................
//   12 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//   13 //~~~  
//   14 //~~~  
//   15 //~~~  
//   16 //~~~  
//   17 //~~~  
//   18 //~~~  
//   19 //~~~  
//   20 //~~~  
//   21 //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
        DATA
//   22 short  sh1MsRegisteredTimers;
sh1MsRegisteredTimers:
        DS8 2

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   23 TmrNode *pHeadTmrNode = (TmrNode*)0; //Pointer on Firsst
pHeadTmrNode:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   24 TmrNode *pTailTmrNode = (TmrNode*)0;
pTailTmrNode:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   25 TmrNode *PCurrNode    = (TmrNode*)0;
PCurrNode:
        DS8 4
//   26 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   27 void  TmrCalls(void){
//   28    
//   29     register TmrNode *pNode;
//   30     register long i;
//   31     register long lRegTmr = sh1MsRegisteredTimers;
TmrCalls:
        LDR.W    R2,??DataTable13
        LDRSH    R2,[R2, #+0]
//   32 
//   33     //Check Semafor Here
//   34     if (chGlSem == 0 && lRegTmr > 0){//Skip change Value
        LDR.W    R3,??DataTable13_1
        LDRB     R3,[R3, #+0]
        CMP      R3,#+0
        BNE.N    ??TmrCalls_0
        CMP      R2,#+1
        BLT.N    ??TmrCalls_0
//   35         pNode = pHeadTmrNode;
        LDR.W    R3,??DataTable13_2
        LDR      R3,[R3, #+0]
        MOVS     R0,R3
//   36         do{
//   37             //Look In Program
//   38             i = pNode->lTmrVal;
??TmrCalls_1:
        LDR      R3,[R0, #+0]
        MOVS     R1,R3
//   39             if (i)
        CMP      R1,#+0
        BEQ.N    ??TmrCalls_2
//   40                 pNode->lTmrVal = --i;
        SUBS     R1,R1,#+1
        STR      R1,[R0, #+0]
//   41             i = (long) pNode->next;
??TmrCalls_2:
        LDR      R3,[R0, #+4]
        MOVS     R1,R3
//   42             if (i == 0)
        CMP      R1,#+0
        BNE.N    ??TmrCalls_3
//   43                 lRegTmr = 1; //Break
        MOVS     R3,#+1
        MOVS     R2,R3
        B.N      ??TmrCalls_4
//   44             else {
//   45                 pNode = (void*) i;
??TmrCalls_3:
        MOVS     R0,R1
//   46             }
//   47 
//   48         }while (--lRegTmr);
??TmrCalls_4:
        SUBS     R2,R2,#+1
        CMP      R2,#+0
        BNE.N    ??TmrCalls_1
//   49     }
//   50 //counter for 1ms Timers
//   51 //Pointer on Firsst
//   52 
//   53 //counter for 2ms Timers
//   54 //Pointer on Firsst
//   55 
//   56 //counter for 5ms Timers
//   57 //Pointer on Firsst
//   58 
//   59 //counter for 10 ms Timers
//   60 //Pointer on Firsst
//   61 }
??TmrCalls_0:
        BX       LR               ;; return
//   62 
//   63 //counter for 50 ms Timers
//   64 //Pointer on Firsst
//   65 
//   66 //counter for 100 ms Timers
//   67 //Pointer on Firsst
//   68 
//   69 //Adding an item to the end of the list

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   70 long TallingList(TmrNode *pNode) {
TallingList:
        PUSH     {R4}
        MOVS     R1,R0
//   71     register TmrNode *pCurrent;
//   72     //long i;
//   73     //volatile long lRegListNumber;
//   74     if ((sh1MsRegisteredTimers+1)> uCh_MAX_Amt_1_MS_TMR)
        LDR.W    R0,??DataTable13_3
        LDRB     R0,[R0, #+0]
        LDR.W    R3,??DataTable13
        LDRSH    R3,[R3, #+0]
        ADDS     R3,R3,#+1
        CMP      R0,R3
        BGE.N    ??TallingList_0
//   75         return 0;
        MOVS     R0,#+0
        B.N      ??TallingList_1
//   76     if (sh1MsRegisteredTimers++) {//
??TallingList_0:
        LDR.W    R0,??DataTable13
        LDRSH    R0,[R0, #+0]
        ADDS     R3,R0,#+1
        LDR.W    R4,??DataTable13
        STRH     R3,[R4, #+0]
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        CMP      R0,#+0
        BEQ.N    ??TallingList_2
//   77         pCurrent = pTailTmrNode;
        LDR.W    R0,??DataTable13_4
        LDR      R0,[R0, #+0]
        MOVS     R2,R0
//   78         pCurrent-> next = (void*)pNode;
        STR      R1,[R2, #+4]
//   79         pNode-> next = (void*) 0;
        MOVS     R0,#+0
        STR      R0,[R1, #+4]
//   80         pTailTmrNode = pNode;
        LDR.W    R0,??DataTable13_4
        STR      R1,[R0, #+0]
        B.N      ??TallingList_3
//   81     } else {//First Insert
//   82         //?if (pHeadTmrNode == pTailTmrNode == ((void *)0))
//   83         pHeadTmrNode = pTailTmrNode = pNode;
??TallingList_2:
        LDR.W    R0,??DataTable13_4
        STR      R1,[R0, #+0]
        LDR.W    R0,??DataTable13_4
        LDR      R0,[R0, #+0]
        LDR.W    R3,??DataTable13_2
        STR      R0,[R3, #+0]
//   84         pNode->next  = (void *)0;
        MOVS     R0,#+0
        STR      R0,[R1, #+4]
//   85         sh1MsRegisteredTimers++;
        LDR.W    R0,??DataTable13
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R3,??DataTable13
        STRH     R0,[R3, #+0]
//   86     }
//   87     return sh1MsRegisteredTimers;
??TallingList_3:
        LDR.W    R0,??DataTable13
        LDRSH    R0,[R0, #+0]
??TallingList_1:
        POP      {R4}
        BX       LR               ;; return
//   88 }
//   89 //Adding an item to the beginning of the list (pushing to the list)

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   90 long PushTmrNode(TmrNode *pNode){
PushTmrNode:
        MOVS     R1,R0
//   91 
//   92     if ((sh1MsRegisteredTimers+1)> uCh_MAX_Amt_1_MS_TMR)
        LDR.W    R0,??DataTable13_3
        LDRB     R0,[R0, #+0]
        LDR.W    R2,??DataTable13
        LDRSH    R2,[R2, #+0]
        ADDS     R2,R2,#+1
        CMP      R0,R2
        BGE.N    ??PushTmrNode_0
//   93         return 0;
        MOVS     R0,#+0
        B.N      ??PushTmrNode_1
//   94     if (sh1MsRegisteredTimers) {//
??PushTmrNode_0:
        LDR.W    R0,??DataTable13
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BEQ.N    ??PushTmrNode_2
//   95         pNode-> next = (void*)pHeadTmrNode;
        LDR.W    R0,??DataTable13_2
        LDR      R0,[R0, #+0]
        STR      R0,[R1, #+4]
//   96         pHeadTmrNode = pNode;
        LDR.W    R0,??DataTable13_2
        STR      R1,[R0, #+0]
//   97         sh1MsRegisteredTimers++;
        LDR.W    R0,??DataTable13
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R2,??DataTable13
        STRH     R0,[R2, #+0]
        B.N      ??PushTmrNode_3
//   98     } else {//First Insert
//   99         //?if (pHeadTmrNode == pTailTmrNode == ((void *)0))
//  100         pHeadTmrNode = pTailTmrNode = pNode;
??PushTmrNode_2:
        LDR.W    R0,??DataTable13_4
        STR      R1,[R0, #+0]
        LDR.W    R0,??DataTable13_4
        LDR      R0,[R0, #+0]
        LDR.W    R2,??DataTable13_2
        STR      R0,[R2, #+0]
//  101         pNode->next  = (void *)0;
        MOVS     R0,#+0
        STR      R0,[R1, #+4]
//  102         sh1MsRegisteredTimers++;
        LDR.W    R0,??DataTable13
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R2,??DataTable13
        STRH     R0,[R2, #+0]
//  103     }
//  104     return sh1MsRegisteredTimers;
??PushTmrNode_3:
        LDR.W    R0,??DataTable13
        LDRSH    R0,[R0, #+0]
??PushTmrNode_1:
        BX       LR               ;; return
//  105 }
//  106 //Adding an item to the special position of the list (cutting to the list)

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  107 long IncreaseTmrList(TmrNode *pNode,long lPos){
IncreaseTmrList:
        PUSH     {R4,R5}
        MOVS     R2,R0
//  108     register TmrNode *pCurrent;
//  109     void *pv;
//  110 
//  111     if ((sh1MsRegisteredTimers+1)< uCh_MAX_Amt_1_MS_TMR && lPos< sh1MsRegisteredTimers) {
        LDR.W    R0,??DataTable13
        LDRSH    R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R5,??DataTable13_3
        LDRB     R5,[R5, #+0]
        CMP      R0,R5
        BGE.N    ??IncreaseTmrList_0
        LDR.W    R0,??DataTable13
        LDRSH    R0,[R0, #+0]
        CMP      R1,R0
        BGE.N    ??IncreaseTmrList_0
//  112         pCurrent = pHeadTmrNode;
        LDR.W    R0,??DataTable13_2
        LDR      R0,[R0, #+0]
        MOVS     R3,R0
//  113         while (pCurrent->next != ((void *) 0) && lPos--) {
??IncreaseTmrList_1:
        LDR      R0,[R3, #+4]
        CMP      R0,#+0
        BEQ.N    ??IncreaseTmrList_2
        MOVS     R0,R1
        SUBS     R1,R0,#+1
        CMP      R0,#+0
        BEQ.N    ??IncreaseTmrList_2
//  114             pCurrent = (TmrNode*) pCurrent->next;
        LDR      R3,[R3, #+4]
        B.N      ??IncreaseTmrList_1
//  115         }
//  116         if ((lPos == 0) && pCurrent) {
??IncreaseTmrList_2:
        CMP      R1,#+0
        BNE.N    ??IncreaseTmrList_0
        CMP      R3,#+0
        BEQ.N    ??IncreaseTmrList_0
//  117             pv = (void*) pCurrent->next;
        LDR      R0,[R3, #+4]
        MOVS     R4,R0
//  118             pCurrent->next = (void*) pNode;
        STR      R2,[R3, #+4]
//  119             pNode->next = pv;
        STR      R4,[R2, #+4]
//  120             return ++sh1MsRegisteredTimers;
        LDR.W    R0,??DataTable13
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R5,??DataTable13
        STRH     R0,[R5, #+0]
        LDR.W    R0,??DataTable13
        LDRSH    R0,[R0, #+0]
        B.N      ??IncreaseTmrList_3
//  121         }
//  122     }
//  123     return 0;
??IncreaseTmrList_0:
        MOVS     R0,#+0
??IncreaseTmrList_3:
        POP      {R4,R5}
        BX       LR               ;; return
//  124 }
//  125 //Removing the first item (popping from the list)

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  126 long PopTmrNode(TmrNode *pNode) {
PopTmrNode:
        PUSH     {R4}
        MOVS     R1,R0
//  127     register TmrNode *pCurrent;
//  128     register long i;
//  129     if (sh1MsRegisteredTimers) {
        LDR.W    R0,??DataTable13
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BEQ.N    ??PopTmrNode_0
//  130         i = 0;
        MOVS     R0,#+0
        MOVS     R3,R0
//  131         pCurrent = pHeadTmrNode;
        LDR.W    R0,??DataTable13_2
        LDR      R0,[R0, #+0]
        MOVS     R2,R0
//  132         if (pCurrent == pNode) {
        CMP      R2,R1
        BNE.N    ??PopTmrNode_1
//  133             //Delete 1-st Element
//  134             pHeadTmrNode = pCurrent->next;
        LDR      R0,[R2, #+4]
        LDR.W    R4,??DataTable13_2
        STR      R0,[R4, #+0]
//  135             sh1MsRegisteredTimers--;
        LDR.W    R0,??DataTable13
        LDRH     R0,[R0, #+0]
        SUBS     R0,R0,#+1
        LDR.W    R4,??DataTable13
        STRH     R0,[R4, #+0]
//  136             return 1; //Registered Number
        MOVS     R0,#+1
        B.N      ??PopTmrNode_2
//  137         }
//  138         while (i < sh1MsRegisteredTimers) {
??PopTmrNode_1:
        LDR.W    R0,??DataTable13
        LDRSH    R0,[R0, #+0]
        CMP      R3,R0
        BGE.N    ??PopTmrNode_0
//  139             if (pCurrent->next == (void*)pNode) {
        LDR      R0,[R2, #+4]
        CMP      R0,R1
        BNE.N    ??PopTmrNode_3
//  140                 pCurrent->next = pNode->next;
        LDR      R0,[R1, #+4]
        STR      R0,[R2, #+4]
//  141                 sh1MsRegisteredTimers--;
        LDR.W    R0,??DataTable13
        LDRH     R0,[R0, #+0]
        SUBS     R0,R0,#+1
        LDR.W    R4,??DataTable13
        STRH     R0,[R4, #+0]
//  142                 return i; //Registered Number
        MOVS     R0,R3
        B.N      ??PopTmrNode_2
//  143             }
//  144             i++;
??PopTmrNode_3:
        ADDS     R3,R3,#+1
        B.N      ??PopTmrNode_1
//  145         }
//  146     }
//  147     return 0;
??PopTmrNode_0:
        MOVS     R0,#+0
??PopTmrNode_2:
        POP      {R4}
        BX       LR               ;; return
//  148 }
//  149 /*
//  150 //Removing the last item of the list
//  151 long CuttingList(TmrNode *pNode){
//  152  
//  153     return 0;
//  154 }
//  155 //Removing a specific item
//  156 long DecreaseTmrList(TmrNode *pNode,long lPos){
//  157 
//  158     return 0;
//  159 }
//  160 */
//  161 #include "Ereg.h"

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  162 char chGbl__DIN1_DIN5__RD_VAL;
chGbl__DIN1_DIN5__RD_VAL:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  163 char chGbl__DIN6_DIN12__RD_VAL;
chGbl__DIN6_DIN12__RD_VAL:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  164 char chGbl__LedColumns__RW_VAL;
chGbl__LedColumns__RW_VAL:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  165 char chGbl_REL_1_6__ROWS_A_D__RW_VAL;
chGbl_REL_1_6__ROWS_A_D__RW_VAL:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  166 char chGbl__REL_1_6__RD_VAL;
chGbl__REL_1_6__RD_VAL:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  167 char chGbl__REL7_REL14__RW_VAL;
chGbl__REL7_REL14__RW_VAL:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  168 char chGbl__REL7_REL14__RD_VAL;
chGbl__REL7_REL14__RD_VAL:
        DS8 1
//  169 
//  170 
//  171 
//  172 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  173 UI32Bit DiHrdStateUI32Bit;//, DiHrdStateUI32Bit
DiHrdStateUI32Bit:
        DS8 4
//  174 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  175 //---
//  176 extern void RdHrdIn(void*pv);
//  177 //..................................................................................
//  178 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  179 //~~~     функция считывания состояния дискретных входов                       ~~~~~
//  180 //~~~     p_out_param должен указывать на область памяти 4 байта              ~~~~~
//  181 //~~~     возврат 3 - команда выполнена успешно                               ~~~~~
//  182 //~~~                                                                         ~~~~~
//  183 //~~~     Положение бит                                                       ~~~~~
//  184 //~~~     MSB ...LSB                                                          ~~~~~
//  185 //~~~     ДВ16  ДВ0                                                           ~~~~~
//  186 //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//  187 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  188 ////////////////////////////////////////////////////////////////////////////////////

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  189 void RdHrdIn(void *pv){
RdHrdIn:
        PUSH     {R4}
//  190     register long i,j;
//  191     register void *pvRlc;
//  192     //reinterpret_cast<void*>(NOR_PSRAM_BANK2);
//  193     pvRlc = (void*)(((long)NOR_PSRAM_BANK2)+(ADR_READ_DIN01__05<<1));
        MOVS     R4,#+1686110208
        MOVS     R1,R4
//  194     //((char*)pvRlc) += ;//
//  195     i = *((char*)pvRlc);//0-5 bits
        LDRB     R4,[R1, #+0]
        MOVS     R2,R4
//  196     i&= 0x1f;
        ANDS     R2,R2,#0x1F
//  197     ((UI32Bit*) pv)->ar_uch[0] = (char)i;
        STRB     R2,[R0, #+0]
//  198     pvRlc = (void*)((long)NOR_PSRAM_BANK2+(ADR_READ_CHECK_RDO__REL_1_6<<1));
        MOVS     R4,#+1702887424
        MOVS     R1,R4
//  199     i = *((short*)pvRlc);//9-15 bits
        LDRSH    R4,[R1, #+0]
        MOVS     R2,R4
//  200     j = i & 600;
        ANDS     R4,R2,#0x258
        MOVS     R3,R4
//  201     j >>= 3; 
        ASRS     R3,R3,#+3
//  202     ((UI32Bit*) pv)->ar_uch[0] |= (char)j;//6,7 - 9-10
        LDRB     R4,[R0, #+0]
        ORRS     R4,R3,R4
        STRB     R4,[R0, #+0]
//  203     ((UI32Bit*) pv)->ar_uch[1] = (i >> 3);//8-12
        ASRS     R4,R2,#+3
        STRB     R4,[R0, #+1]
//  204     pvRlc = (void*)(((long)NOR_PSRAM_BANK2)+(ADR_READ_DIN06__12<<1));
        LDR.W    R4,??DataTable13_5  ;; 0x64c00000
        MOVS     R1,R4
//  205     i = *((char*)pvRlc);//13-17 5bit
        LDRB     R4,[R1, #+0]
        MOVS     R2,R4
//  206     j = i & 0x7;
        ANDS     R4,R2,#0x7
        MOVS     R3,R4
//  207     ((UI32Bit*) pv)->ar_uch[1] |= (j<<5);
        LDRB     R4,[R0, #+1]
        ORRS     R4,R4,R3, LSL #+5
        STRB     R4,[R0, #+1]
//  208     ((UI32Bit*) pv)->ar_uch[2] = i>>3;
        ASRS     R4,R2,#+3
        STRB     R4,[R0, #+2]
//  209     pvRlc = (void*)((long)NOR_PSRAM_BANK2+(ADR_READ_CHECK_RDO_REL7_REL14<<1));
        LDR.W    R4,??DataTable13_6  ;; 0x65c00000
        MOVS     R1,R4
//  210     i = *((short*)pvRlc);
        LDRSH    R4,[R1, #+0]
        MOVS     R2,R4
//  211     j = i>>14;
        ASRS     R4,R2,#+14
        MOVS     R3,R4
//  212     ((UI32Bit*) pv)->ar_uch[2] |= (j<<2);
        LDRB     R4,[R0, #+2]
        ORRS     R4,R4,R3, LSL #+2
        STRB     R4,[R0, #+2]
//  213 /*
//  214 sLV.pLAdr4 = reinterpret_cast<char*>( NOR_PSRAM_BANK2);
//  215 sLV.pLAdr4 += ADR_READ_DIN06__12<<1;
//  216 sLV.chVal = *(sLV.pLAdr3);
//  217 */
//  218 
//  219 
//  220    
//  221 }
        POP      {R4}
        BX       LR               ;; return

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  222 UI32Bit DoStateUI32Bit;
DoStateUI32Bit:
        DS8 4
//  223 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  224 //---
//  225 extern void SetHrdOut(void*pv);
//  226 //..................................................................................
//  227 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  228 //~~~     функция записи состояния дискретных входов                       ~~~~~
//  229 //~~~     p_out_param должен указывать на область памяти 4 байта              ~~~~~
//  230 //~~~     возврат 3 - команда выполнена успешно                               ~~~~~
//  231 //~~~                                                                         ~~~~~
//  232 //~~~     Положение бит                                                       ~~~~~
//  233 //~~~     MSB ...LSB                                                          ~~~~~
//  234 //~~~     ДВ16  ДВ0                                                           ~~~~~
//  235 //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//  236 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  237 //////////////////////////////////////////////////////////////////////////////////////////

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  238 void SetHrdOut(void*pv){
SetHrdOut:
        PUSH     {R4}
//  239     register long i,j;
//  240     register void *pvRlc;
//  241     i = ((UI32Bit*) pv)->ar_uch[0]; 
        LDRB     R4,[R0, #+0]
        MOVS     R1,R4
//  242     j = i&1;
        ANDS     R4,R1,#0x1
        MOVS     R2,R4
//  243     
//  244     pvRlc = (void*)(((long)NOR_PSRAM_BANK2)+(ADR_WRITE_RDO__REL_1_6__ROWS_A__D<<1));
        MOVS     R4,#+1702887424
        MOVS     R3,R4
//  245     *((char*)pvRlc) = j;//???
        STRB     R2,[R3, #+0]
//  246     pvRlc = (void*)((long)NOR_PSRAM_BANK2+(ADR_READ_CHECK_RDO_REL7_REL14<<1));
        LDR.W    R4,??DataTable13_6  ;; 0x65c00000
        MOVS     R3,R4
//  247     i = ((UI32Bit*) pv)->ar_uch[0]; 
        LDRB     R4,[R0, #+0]
        MOVS     R1,R4
//  248     j = i>>1;
        ASRS     R4,R1,#+1
        MOVS     R2,R4
//  249     j &= 0x3f;
        ANDS     R2,R2,#0x3F
//  250     *((char*)pvRlc) = j;
        STRB     R2,[R3, #+0]
//  251 
//  252     
//  253 }
        POP      {R4}
        BX       LR               ;; return
//  254 #include "HlDefs.h"

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
// __absolute LedRegCode const HLSelectorTable[26]
HLSelectorTable:
        DC8 0, 1, 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 1, 1, 5, 2, 1, 6, 3, 1, 7, 4
        DC8 1, 8, 1, 2, 9, 2, 2, 10, 3, 2, 11, 4, 2, 12, 1, 3, 13, 2, 3, 14, 3
        DC8 3, 15, 4, 3, 16, 1, 4, 17, 2, 4, 18, 3, 4, 19, 1, 5, 20, 2, 5, 21
        DC8 3, 5, 22, 3, 6, 23, 4, 6, 24, 2, 7, 25, 4, 7, 0, 0
//  255 enum LED_AUX_PARTS_OP { 
//  256 
//  257 LED_AUX_OP_INIT  = 0,  
//  258 LED_AUX_OP_SET   ,  
//  259 LED_AUX_OP_CLR   ,
//  260 LED_AUX_OP_EXIT  ,
//  261 TOTAL_LED_AUX_OP = LED_AUX_OP_EXIT + 1
//  262 };

        SECTION `.rodata`:CONST:REORDER:NOROOT(0)
        DATA
//  263 const char chNumIndependentParts = TOTAL_LED_AUX_OP;
chNumIndependentParts:
        DC8 4

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  264 fnPLpvrL arrFnPtr[TOTAL_LED_AUX_OP] = {
arrFnPtr:
        DC32 LedAuxOp1, LedAuxOp2, LedAuxOp3, LedAuxOp4
//  265 LedAuxOp1,
//  266 LedAuxOp2,
//  267 LedAuxOp3,
//  268 LedAuxOp4
//  269 };

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  270 static long lGlbOperationReflector = 0;
lGlbOperationReflector:
        DS8 4

        SECTION `.data`:DATA:REORDER:NOROOT(0)
        DATA
//  271 char chCounterLedService = TOTAL_LED_AUX_OP;
chCounterLedService:
        DC8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  272 UI32Bit LedStateUI32Bit,LedRawStateUI32Bit;
LedStateUI32Bit:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
LedRawStateUI32Bit:
        DS8 4
//  273 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  274 //---
//  275 extern void SetHrdLed(void*pv);
//  276 //..................................................................................
//  277 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  278 //~~~     функция записи состояния дискретных входов                       ~~~~~
//  279 //~~~     p_out_param должен указывать на область памяти 4 байта              ~~~~~
//  280 //~~~     возврат 3 - команда выполнена успешно                               ~~~~~
//  281 //~~~                                                                         ~~~~~
//  282 //~~~     Положение бит                                                       ~~~~~
//  283 //~~~     MSB ...LSB                                                          ~~~~~
//  284 //~~~     ДВ16  ДВ0                                                           ~~~~~
//  285 //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//  286 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  287 //////////////////////////////////////////////////////////////////////////////////////////

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  288 void SetHrdLed(void*pv){
SetHrdLed:
        PUSH     {R3-R7,LR}
        MOVS     R4,R0
//  289 register long i,j;
//  290  //   register void *pvRlc;
//  291     fnPLpvrL CurrAuxfunc; // 
//  292     volatile long lAuxVar = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
//  293     //volatile LedRegCode lcsLedRegCode;
//  294     i = chCounterLedService + 1;
        LDR.W    R0,??DataTable13_7
        LDRB     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        MOVS     R5,R0
//  295     if (i >= chNumIndependentParts){
        LDR.W    R0,??DataTable13_8
        LDRB     R0,[R0, #+0]
        CMP      R5,R0
        BLT.N    ??SetHrdLed_0
//  296         i = chCounterLedService = 0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable13_7
        STRB     R0,[R1, #+0]
        LDR.W    R0,??DataTable13_7
        LDRB     R0,[R0, #+0]
        MOVS     R5,R0
//  297         lGlbOperationReflector = 0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable13_9
        STR      R0,[R1, #+0]
//  298         LedRawStateUI32Bit.ul_val = LedStateUI32Bit.ul_val;
        LDR.W    R0,??DataTable13_10
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable13_11
        STR      R0,[R1, #+0]
        B.N      ??SetHrdLed_1
//  299     } else{
//  300         chCounterLedService = i;
??SetHrdLed_0:
        LDR.W    R0,??DataTable13_7
        STRB     R5,[R0, #+0]
//  301     }
//  302 
//  303     i = chCounterLedService;
??SetHrdLed_1:
        LDR.W    R0,??DataTable13_7
        LDRB     R0,[R0, #+0]
        MOVS     R5,R0
//  304     CurrAuxfunc = arrFnPtr[i];
        LDR.W    R0,??DataTable13_12
        LDR      R0,[R0, R5, LSL #+2]
        MOVS     R7,R0
//  305     j = CurrAuxfunc(i, (void*) &LedRawStateUI32Bit.ul_val);
        LDR.W    R1,??DataTable13_11
        MOVS     R0,R5
        BLX      R7
        MOVS     R6,R0
//  306 
//  307 }
        POP      {R0,R4-R7,PC}    ;; return
//  308 
//  309 
//  310 
//  311 
//  312 
//  313 
//  314 
//  315 
//  316 

        SECTION `.rodata`:CONST:REORDER:NOROOT(0)
        DATA
//  317 const char CH_AMOUNT_DI = 19;
CH_AMOUNT_DI:
        DC8 19

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  318 char arTimerDi[19] = {
arTimerDi:
        DS8 20
//  319 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
//  320 };

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  321 DICfgSuit sDiCfg;
sDiCfg:
        DS8 48
//  322 
//  323 
//  324 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  325 static long lCtr = 0; //char chTestStateIn = 1;char chOut;
lCtr:
        DS8 4
//  326 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  327 //---
//  328 extern void UpdateStateDI (void);
//  329 //..................................................................................
//  330 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  331 //~~~     функция анализа состояния дискретных входов                       ~~~~~
//  332 //~~~     p_out_param должен указывать на область памяти 4 байта              ~~~~~
//  333 //~~~     возврат 3 - команда выполнена успешно                               ~~~~~
//  334 //~~~                                                                         ~~~~~
//  335 //~~~     Положение бит                                                       ~~~~~
//  336 //~~~     MSB ...LSB                                                          ~~~~~
//  337 //~~~     ДВ16  ДВ0                                                           ~~~~~
//  338 //,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//  339 //""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//  340 //////////////////////////////////////////////////////////////////////////////////////////

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  341 void UpdateStateDI (void){
UpdateStateDI:
        PUSH     {R4-R7,LR}
        SUB      SP,SP,#+36
//  342     register long i, j;
//  343     register unsigned long ulrVal;
//  344     //register char *pCh;
//  345     register DICfgSuit *pDICfgSuit;
//  346     volatile char arChReferenceIdx[] = {
//  347     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18    };//7, 15, 0, 0};
        ADD      R0,SP,#+16
        LDR.W    R1,??DataTable13_13
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
//  348     volatile long arU32Tst[] = {0, 0, 0, 0};
        MOV      R0,SP
        MOVS     R1,#+16
        BL       __aeabi_memclr4
//  349     pDICfgSuit = &sDiCfg;
        LDR.W    R0,??DataTable13_14
        MOVS     R7,R0
//  350     sDiCfg.pDITmr = arTimerDi;
        LDR.W    R0,??DataTable13_15
        LDR.W    R1,??DataTable13_14
        STR      R0,[R1, #+40]
//  351     pDICfgSuit->DiHrdStateUI32Bit.ul_val = DiHrdStateUI32Bit.ul_val;
        LDR.W    R0,??DataTable13_16
        LDR      R0,[R0, #+0]
        STR      R0,[R7, #+24]
//  352     for (i = 0; i < CH_AMOUNT_DI; i++){
        MOVS     R0,#+0
        MOVS     R4,R0
??UpdateStateDI_0:
        LDR.W    R0,??DataTable13_17
        LDRB     R0,[R0, #+0]
        CMP      R4,R0
        BGE.W    ??UpdateStateDI_1
//  353         //Check Type Signal
//  354         if (pDICfgSuit->DiTypeSignal.ul_val & (1 << i)){
        LDR      R0,[R7, #+20]
        LSRS     R0,R0,R4
        LSLS     R0,R0,#+31
        BPL.N    ??UpdateStateDI_2
//  355             //Alternate Current
//  356             j = pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
        LDR      R0,[R7, #+24]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ANDS     R0,R1,R0
        MOVS     R5,R0
//  357             if (j == 0)
        CMP      R5,#+0
        BNE.N    ??UpdateStateDI_3
//  358               pDICfgSuit->DiAND.ul_val &= ~(1 << i);//pCh[OFF_BYTE_AND] &= ~(1 << i);
        LDR      R0,[R7, #+28]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        BICS     R0,R0,R1
        STR      R0,[R7, #+28]
//  359 
//  360             //pCh[OFF_BYTE_OR] |= pCh[OFF_BYTE_PIN] & (1 << i);
//  361             pDICfgSuit->DiOR.ul_val |= pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
??UpdateStateDI_3:
        LDR      R0,[R7, #+32]
        LDR      R1,[R7, #+24]
        MOVS     R2,#+1
        LSLS     R2,R2,R4
        ANDS     R1,R2,R1
        ORRS     R0,R1,R0
        STR      R0,[R7, #+32]
//  362             j = lCtr;
        LDR.W    R0,??DataTable13_18
        LDR      R0,[R0, #+0]
        MOVS     R5,R0
//  363             j++;
        ADDS     R5,R5,#+1
//  364             if (j > 12)
        CMP      R5,#+13
        BLT.N    ??UpdateStateDI_4
//  365             {
//  366                 lCtr = 0; //pCh[OFF_BYTE_DI_timer0+i];
        MOVS     R0,#+0
        LDR.W    R1,??DataTable13_18
        STR      R0,[R1, #+0]
//  367                 //Check 1
//  368                 //j = (pCh[OFF_BYTE_AND] & (1 << i));
//  369                 j = (pDICfgSuit->DiAND.ul_val & (1 << i));
        LDR      R0,[R7, #+28]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ANDS     R0,R1,R0
        MOVS     R5,R0
//  370                 if ((j == 0) && (pDICfgSuit->DiOR.ul_val & (1 << i))){//Stable 1
        CMP      R5,#+0
        BNE.N    ??UpdateStateDI_5
        LDR      R0,[R7, #+32]
        LSRS     R0,R0,R4
        LSLS     R0,R0,#+31
        BPL.N    ??UpdateStateDI_5
//  371                     pDICfgSuit->DiStartUP.ul_val |= (1 << i);//pCh[OFF_BYTE_DI_StartUP] |= (1 << i);
        LDR      R0,[R7, #+36]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ORRS     R0,R1,R0
        STR      R0,[R7, #+36]
        B.N      ??UpdateStateDI_6
//  372                 }else{
//  373                     pDICfgSuit->DiStartUP.ul_val &= ~(1 << i);
??UpdateStateDI_5:
        LDR      R0,[R7, #+36]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        BICS     R0,R0,R1
        STR      R0,[R7, #+36]
//  374                     arU32Tst[0] = pDICfgSuit->DiAND.ul_val;//pCh[OFF_BYTE_AND];
        LDR      R0,[R7, #+28]
        STR      R0,[SP, #+0]
//  375                     arU32Tst[1] = pDICfgSuit->DiOR.ul_val;//pCh[OFF_BYTE_OR];
        LDR      R0,[R7, #+32]
        STR      R0,[SP, #+4]
//  376                 }
//  377                 ulrVal = (pDICfgSuit->DiStartUP.ul_val & (1 << i));
??UpdateStateDI_6:
        LDR      R0,[R7, #+36]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ANDS     R0,R1,R0
        MOVS     R6,R0
//  378                 j = (pDICfgSuit->DiState.ul_val & (1 << i));
        LDR      R0,[R7, #+44]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ANDS     R0,R1,R0
        MOVS     R5,R0
//  379                 ulrVal ^= j;
        EORS     R6,R5,R6
//  380                 if (ulrVal){
        CMP      R6,#+0
        BEQ.N    ??UpdateStateDI_7
//  381                     ulrVal = pDICfgSuit->pDITmr[i];
        LDR      R0,[R7, #+40]
        LDRB     R0,[R4, R0]
        MOVS     R6,R0
//  382                     ulrVal++;
        ADDS     R6,R6,#+1
//  383                     j = arChReferenceIdx[i];
        ADD      R0,SP,#+16
        LDRB     R0,[R4, R0]
        MOVS     R5,R0
//  384                     //j = pprotect_cfg_tbl->ushDurationDI[j] + 1;
//  385                     j = pDICfgSuit->arChDurationDI[j] + 1;
        LDRB     R0,[R5, R7]
        ADDS     R5,R0,#+1
//  386                     if (ulrVal > (unsigned)j){
        CMP      R5,R6
        BCS.N    ??UpdateStateDI_8
//  387                         pDICfgSuit->pDITmr[i] = 0;//pCh[OFF_BYTE_DI_timer0 + i] = 0;
        MOVS     R0,#+0
        LDR      R1,[R7, #+40]
        STRB     R0,[R4, R1]
//  388                         //pCh[OFF_BYTE_DI_State] &= ~(1 << i);
//  389                         //pCh[OFF_BYTE_DI_State] |= pCh[OFF_BYTE_DI_StartUP] & (1 << i);
//  390                         pDICfgSuit->DiState.ul_val &= ~(1 << i);
        LDR      R0,[R7, #+44]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        BICS     R0,R0,R1
        STR      R0,[R7, #+44]
//  391                         pDICfgSuit->DiState.ul_val |= pDICfgSuit->DiStartUP.ul_val & (1 << i);
        LDR      R0,[R7, #+44]
        LDR      R1,[R7, #+36]
        MOVS     R2,#+1
        LSLS     R2,R2,R4
        ANDS     R1,R2,R1
        ORRS     R0,R1,R0
        STR      R0,[R7, #+44]
        B.N      ??UpdateStateDI_9
//  392                     }else
//  393                         pDICfgSuit->pDITmr[i] =  ulrVal;//pCh[OFF_BYTE_DI_timer0 + i] = ulrVal;
??UpdateStateDI_8:
        LDR      R0,[R7, #+40]
        STRB     R6,[R4, R0]
        B.N      ??UpdateStateDI_9
//  394                 }else
//  395                     pDICfgSuit->pDITmr[i] = 0;//pCh[OFF_BYTE_DI_timer0 + i] = 0;
??UpdateStateDI_7:
        MOVS     R0,#+0
        LDR      R1,[R7, #+40]
        STRB     R0,[R4, R1]
//  396                 pDICfgSuit->DiAND.ul_val |= (1 << i);//pCh[OFF_BYTE_AND] |= (1 << i);
??UpdateStateDI_9:
        LDR      R0,[R7, #+28]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ORRS     R0,R1,R0
        STR      R0,[R7, #+28]
//  397                 pDICfgSuit->DiOR.ul_val &= ~(1 << i);//pCh[OFF_BYTE_OR] &= ~(1 << i); //Now 2 Bits
        LDR      R0,[R7, #+32]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        BICS     R0,R0,R1
        STR      R0,[R7, #+32]
        B.N      ??UpdateStateDI_10
//  398             }
//  399             else
//  400                 lCtr = j;
??UpdateStateDI_4:
        LDR.W    R0,??DataTable13_18
        STR      R5,[R0, #+0]
        B.N      ??UpdateStateDI_10
//  401         }
//  402         else
//  403         {
//  404             //Direct Current
//  405             //ulrVal = (pCh[OFF_BYTE_DI_StartUP] & (1 << i)) ^ (pCh[OFF_BYTE_PIN] & (1 << i));
//  406             ulrVal = (pDICfgSuit->DiStartUP.ul_val & (1 << i)) 
//  407             ^ (pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i));
??UpdateStateDI_2:
        LDR      R0,[R7, #+36]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ANDS     R0,R1,R0
        LDR      R1,[R7, #+24]
        MOVS     R2,#+1
        LSLS     R2,R2,R4
        ANDS     R1,R2,R1
        EORS     R0,R1,R0
        MOVS     R6,R0
//  408             if (ulrVal){
        CMP      R6,#+0
        BEQ.N    ??UpdateStateDI_11
//  409                 //Set Di
//  410                 //j = pCh[OFF_BYTE_PIN] & (1 << i);
//  411                 //pCh[OFF_BYTE_DI_StartUP] &= ~(1 << i);
//  412                 //pCh[OFF_BYTE_DI_StartUP] |= j;
//  413                 //pCh[OFF_BYTE_AND] |= (1 << i);
//  414                 //pCh[OFF_BYTE_OR] &= ~(1 << i); //Now 2 Bits
//  415                 //pCh[OFF_BYTE_DI_timer0 + i] = 0;
//  416                 j = pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
        LDR      R0,[R7, #+24]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ANDS     R0,R1,R0
        MOVS     R5,R0
//  417                 pDICfgSuit->DiStartUP.ul_val &= ~(1 << i);
        LDR      R0,[R7, #+36]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        BICS     R0,R0,R1
        STR      R0,[R7, #+36]
//  418                 pDICfgSuit->DiStartUP.ul_val |= j;
        LDR      R0,[R7, #+36]
        ORRS     R0,R5,R0
        STR      R0,[R7, #+36]
//  419                 pDICfgSuit->DiAND.ul_val |= (1 << i);
        LDR      R0,[R7, #+28]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ORRS     R0,R1,R0
        STR      R0,[R7, #+28]
//  420                 pDICfgSuit->DiOR.ul_val &= ~(1 << i);
        LDR      R0,[R7, #+32]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        BICS     R0,R0,R1
        STR      R0,[R7, #+32]
//  421                 pDICfgSuit->pDITmr[i] = 0;
        MOVS     R0,#+0
        LDR      R1,[R7, #+40]
        STRB     R0,[R4, R1]
//  422             }
//  423             //if ((pCh[OFF_BYTE_DI_StartUP] & (1 << i)) == (pCh[OFF_BYTE_PIN] & (1 << i)))
//  424             if ((pDICfgSuit->DiStartUP.ul_val & (1 << i)) 
//  425             == (pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i))){
??UpdateStateDI_11:
        LDR      R0,[R7, #+36]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ANDS     R0,R1,R0
        LDR      R1,[R7, #+24]
        MOVS     R2,#+1
        LSLS     R2,R2,R4
        ANDS     R1,R2,R1
        CMP      R0,R1
        BNE.N    ??UpdateStateDI_10
//  426                 //j = pCh[OFF_BYTE_PIN] & (1 << i);
//  427                 j = pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
        LDR      R0,[R7, #+24]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ANDS     R0,R1,R0
        MOVS     R5,R0
//  428                 if (j == 0)
        CMP      R5,#+0
        BNE.N    ??UpdateStateDI_12
//  429                     //pCh[OFF_BYTE_AND] &= ~(1 << i); //Clr Bit
//  430                     pDICfgSuit->DiAND.ul_val &= ~(1 << i); //Clr Bit
        LDR      R0,[R7, #+28]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        BICS     R0,R0,R1
        STR      R0,[R7, #+28]
        B.N      ??UpdateStateDI_13
//  431                 else
//  432                     //pCh[OFF_BYTE_OR] |= pCh[OFF_BYTE_PIN] & (1 << i);
//  433                     pDICfgSuit->DiOR.ul_val |= pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
??UpdateStateDI_12:
        LDR      R0,[R7, #+32]
        LDR      R1,[R7, #+24]
        MOVS     R2,#+1
        LSLS     R2,R2,R4
        ANDS     R1,R2,R1
        ORRS     R0,R1,R0
        STR      R0,[R7, #+32]
//  434                 //j = pCh[OFF_BYTE_DI_timer0 + i];
//  435                 j = pDICfgSuit->pDITmr[i];
??UpdateStateDI_13:
        LDR      R0,[R7, #+40]
        LDRB     R0,[R4, R0]
        MOVS     R5,R0
//  436                 j++;
        ADDS     R5,R5,#+1
//  437                 ulrVal = arChReferenceIdx[i];
        ADD      R0,SP,#+16
        LDRB     R0,[R4, R0]
        MOVS     R6,R0
//  438                 //if (j < pprotect_cfg_tbl->ushDurationDI[ulrVal]){
//  439                 if (j < pDICfgSuit->arChDurationDI[ulrVal]){
        LDRB     R0,[R6, R7]
        CMP      R5,R0
        BGE.N    ??UpdateStateDI_14
//  440                     //pCh[OFF_BYTE_DI_timer0 + i] = j;
//  441                     pDICfgSuit->pDITmr[i] = j;
        LDR      R0,[R7, #+40]
        STRB     R5,[R4, R0]
        B.N      ??UpdateStateDI_10
//  442                 }
//  443                 else
//  444                 {
//  445                     //if ((pCh[OFF_BYTE_AND] & (1 << i)) == (pCh[OFF_BYTE_OR] & (1 << i))) //Stable 1
//  446                     if ((pDICfgSuit->DiAND.ul_val & (1 << i)) == (pDICfgSuit->DiOR.ul_val & (1 << i))) //Stable 1
??UpdateStateDI_14:
        LDR      R0,[R7, #+28]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ANDS     R0,R1,R0
        LDR      R1,[R7, #+32]
        MOVS     R2,#+1
        LSLS     R2,R2,R4
        ANDS     R1,R2,R1
        CMP      R0,R1
        BNE.N    ??UpdateStateDI_15
//  447                     {
//  448                         //Check Time
//  449                         //pCh[OFF_BYTE_DI_State] &= ~(1 << i);
//  450                         //pCh[OFF_BYTE_DI_State] |= pCh[OFF_BYTE_DI_StartUP] & (1 << i);
//  451                         pDICfgSuit->DiState.ul_val &= ~(1 << i);
        LDR      R0,[R7, #+44]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        BICS     R0,R0,R1
        STR      R0,[R7, #+44]
//  452                         pDICfgSuit->DiState.ul_val |= pDICfgSuit->DiStartUP.ul_val & (1 << i);
        LDR      R0,[R7, #+44]
        LDR      R1,[R7, #+36]
        MOVS     R2,#+1
        LSLS     R2,R2,R4
        ANDS     R1,R2,R1
        ORRS     R0,R1,R0
        STR      R0,[R7, #+44]
        B.N      ??UpdateStateDI_10
//  453                         //Check Inversion
//  454                         //Put Result
//  455                     }
//  456                     else
//  457                     {
//  458                         //reset
//  459                         //pCh[OFF_BYTE_DI_StartUP] &= ~(1 << i);
//  460                         //pCh[OFF_BYTE_DI_StartUP] |= pCh[OFF_BYTE_DI_State] & (1 << i);
//  461                         //pCh[OFF_BYTE_AND] |= (1 << i);
//  462                         //pCh[OFF_BYTE_OR] &= ~(1 << i); //Now 2 Bits
//  463                         //pCh[OFF_BYTE_DI_timer0 + i] = 0;
//  464                         j = pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
??UpdateStateDI_15:
        LDR      R0,[R7, #+24]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ANDS     R0,R1,R0
        MOVS     R5,R0
//  465                         pDICfgSuit->DiStartUP.ul_val &= ~(1 << i);
        LDR      R0,[R7, #+36]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        BICS     R0,R0,R1
        STR      R0,[R7, #+36]
//  466                         pDICfgSuit->DiStartUP.ul_val |= j;
        LDR      R0,[R7, #+36]
        ORRS     R0,R5,R0
        STR      R0,[R7, #+36]
//  467                         pDICfgSuit->DiAND.ul_val |= (1 << i);
        LDR      R0,[R7, #+28]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        ORRS     R0,R1,R0
        STR      R0,[R7, #+28]
//  468                         pDICfgSuit->DiOR.ul_val &= ~(1 << i);
        LDR      R0,[R7, #+32]
        MOVS     R1,#+1
        LSLS     R1,R1,R4
        BICS     R0,R0,R1
        STR      R0,[R7, #+32]
//  469                         pDICfgSuit->pDITmr[i] = 0;
        MOVS     R0,#+0
        LDR      R1,[R7, #+40]
        STRB     R0,[R4, R1]
//  470                     }
//  471                 }
//  472             }
//  473         }
//  474     }
??UpdateStateDI_10:
        ADDS     R4,R4,#+1
        B.N      ??UpdateStateDI_0
//  475 }
??UpdateStateDI_1:
        ADD      SP,SP,#+36
        POP      {R4-R7,PC}       ;; return
//  476 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  477 long LedAuxOp1(long l,void *pv){
LedAuxOp1:
        PUSH     {R4-R6}
        MOVS     R2,R0
//  478     register long i,j;
//  479     register void *pvRlc;
//  480     i = lGlbOperationReflector;
        LDR.N    R5,??DataTable13_9
        LDR      R5,[R5, #+0]
        MOVS     R0,R5
//  481     i |= 1<<l;
        MOVS     R5,#+1
        LSLS     R5,R5,R2
        ORRS     R0,R5,R0
//  482     lGlbOperationReflector = i;
        LDR.N    R5,??DataTable13_9
        STR      R0,[R5, #+0]
//  483     //*((char*)pv) = i;
//  484 
//  485     pvRlc = (void *) (((long) NOR_PSRAM_BANK2) + (ADR_WRITE_RDO__REL_1_6__ROWS_A__D << 1));
        MOVS     R5,#+1702887424
        MOVS     R4,R5
//  486     *((char *) pvRlc) = chGbl_REL_1_6__ROWS_A_D__RW_VAL | (1<<HL_RA);
        LDR.N    R5,??DataTable13_19
        LDRB     R5,[R5, #+0]
        ORRS     R5,R5,#0x2
        STRB     R5,[R4, #+0]
//  487     pvRlc = (void *) (((long) NOR_PSRAM_BANK2) + (ADR_WRITE_RI_COLUMNS01__06 << 1));
        MOVS     R5,#+1694498816
        MOVS     R4,R5
//  488     chGbl__LedColumns__RW_VAL = 0xff;
        MOVS     R5,#+255
        LDR.N    R6,??DataTable13_20
        STRB     R5,[R6, #+0]
//  489     *((char *) pvRlc) = chGbl__LedColumns__RW_VAL;
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        STRB     R5,[R4, #+0]
//  490     //Select Led
//  491     for (i = 0; i < TOTAL_LEDS; i++) {
        MOVS     R5,#+0
        MOVS     R0,R5
??LedAuxOp1_0:
        CMP      R0,#+26
        BGE.N    ??LedAuxOp1_1
//  492         if (((UI32Bit *) pv)->ul_val & (1 << i)) { //Set bit
        LDR      R5,[R1, #+0]
        LSRS     R5,R5,R0
        LSLS     R5,R5,#+31
        BPL.N    ??LedAuxOp1_2
//  493             j = HLSelectorTable[i].row;
        LDR.N    R5,??DataTable13_21
        MOVS     R6,#+3
        MLA      R5,R6,R0,R5
        LDRB     R5,[R5, #+1]
        MOVS     R3,R5
//  494             if (j == HL_RA) {
        CMP      R3,#+1
        BNE.N    ??LedAuxOp1_2
//  495                 j = HLSelectorTable[i].column;
        LDR.N    R5,??DataTable13_21
        MOVS     R6,#+3
        MLA      R5,R6,R0,R5
        LDRB     R5,[R5, #+2]
        MOVS     R3,R5
//  496                 chGbl__LedColumns__RW_VAL &= ~(1 << j);
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        MOVS     R6,#+1
        LSLS     R6,R6,R3
        BICS     R5,R5,R6
        LDR.N    R6,??DataTable13_20
        STRB     R5,[R6, #+0]
//  497             }
//  498         }
//  499     }
??LedAuxOp1_2:
        ADDS     R0,R0,#+1
        B.N      ??LedAuxOp1_0
//  500     *((char *) pvRlc) = chGbl__LedColumns__RW_VAL;
??LedAuxOp1_1:
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        STRB     R5,[R4, #+0]
//  501 return i;
        POP      {R4-R6}
        BX       LR               ;; return
//  502 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  503 long LedAuxOp2(long l,void *pv){
LedAuxOp2:
        PUSH     {R4-R6}
        MOVS     R2,R0
//  504     register long i,j;
//  505     register void *pvRlc;
//  506     i = lGlbOperationReflector;
        LDR.N    R5,??DataTable13_9
        LDR      R5,[R5, #+0]
        MOVS     R0,R5
//  507     i |= 1 << l;
        MOVS     R5,#+1
        LSLS     R5,R5,R2
        ORRS     R0,R5,R0
//  508     lGlbOperationReflector = i;
        LDR.N    R5,??DataTable13_9
        STR      R0,[R5, #+0]
//  509     //*((char*)pv) = i;
//  510     pvRlc = (void *) (((long) NOR_PSRAM_BANK2) + (ADR_WRITE_RDO__REL_1_6__ROWS_A__D << 1));
        MOVS     R5,#+1702887424
        MOVS     R4,R5
//  511     *((char *) pvRlc) = chGbl_REL_1_6__ROWS_A_D__RW_VAL | (1<<HL_RB);
        LDR.N    R5,??DataTable13_19
        LDRB     R5,[R5, #+0]
        ORRS     R5,R5,#0x4
        STRB     R5,[R4, #+0]
//  512     pvRlc = (void *) (((long) NOR_PSRAM_BANK2) + (ADR_WRITE_RI_COLUMNS01__06 << 1));
        MOVS     R5,#+1694498816
        MOVS     R4,R5
//  513     chGbl__LedColumns__RW_VAL = 0xff;
        MOVS     R5,#+255
        LDR.N    R6,??DataTable13_20
        STRB     R5,[R6, #+0]
//  514     *((char *) pvRlc) = chGbl__LedColumns__RW_VAL;
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        STRB     R5,[R4, #+0]
//  515     //Select Led
//  516     for (i = 0; i < TOTAL_LEDS; i++) {
        MOVS     R5,#+0
        MOVS     R0,R5
??LedAuxOp2_0:
        CMP      R0,#+26
        BGE.N    ??LedAuxOp2_1
//  517         if (((UI32Bit *) pv)->ul_val & (1 << i)) { //Set bit
        LDR      R5,[R1, #+0]
        LSRS     R5,R5,R0
        LSLS     R5,R5,#+31
        BPL.N    ??LedAuxOp2_2
//  518             j = HLSelectorTable[i].row;
        LDR.N    R5,??DataTable13_21
        MOVS     R6,#+3
        MLA      R5,R6,R0,R5
        LDRB     R5,[R5, #+1]
        MOVS     R3,R5
//  519             if (j == HL_RB) {
        CMP      R3,#+2
        BNE.N    ??LedAuxOp2_2
//  520                 j = HLSelectorTable[i].column;
        LDR.N    R5,??DataTable13_21
        MOVS     R6,#+3
        MLA      R5,R6,R0,R5
        LDRB     R5,[R5, #+2]
        MOVS     R3,R5
//  521                 chGbl__LedColumns__RW_VAL &= ~(1 << j);
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        MOVS     R6,#+1
        LSLS     R6,R6,R3
        BICS     R5,R5,R6
        LDR.N    R6,??DataTable13_20
        STRB     R5,[R6, #+0]
//  522             }
//  523         }
//  524     }
??LedAuxOp2_2:
        ADDS     R0,R0,#+1
        B.N      ??LedAuxOp2_0
//  525     *((char *) pvRlc) = chGbl__LedColumns__RW_VAL;
??LedAuxOp2_1:
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        STRB     R5,[R4, #+0]
//  526 return i;
        POP      {R4-R6}
        BX       LR               ;; return
//  527 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  528 long LedAuxOp3(long l,void *pv){
LedAuxOp3:
        PUSH     {R4-R6}
        MOVS     R2,R0
//  529     register long i,j;
//  530     register void *pvRlc;
//  531     i = lGlbOperationReflector;
        LDR.N    R5,??DataTable13_9
        LDR      R5,[R5, #+0]
        MOVS     R0,R5
//  532     i |= 1 << l;
        MOVS     R5,#+1
        LSLS     R5,R5,R2
        ORRS     R0,R5,R0
//  533     lGlbOperationReflector = i;
        LDR.N    R5,??DataTable13_9
        STR      R0,[R5, #+0]
//  534     //*((char*)pv) = i;
//  535     pvRlc = (void *) (((long) NOR_PSRAM_BANK2) + (ADR_WRITE_RDO__REL_1_6__ROWS_A__D << 1));
        MOVS     R5,#+1702887424
        MOVS     R4,R5
//  536     *((char *) pvRlc) = chGbl_REL_1_6__ROWS_A_D__RW_VAL | (1 << HL_RC);
        LDR.N    R5,??DataTable13_19
        LDRB     R5,[R5, #+0]
        ORRS     R5,R5,#0x8
        STRB     R5,[R4, #+0]
//  537     pvRlc = (void *) (((long) NOR_PSRAM_BANK2) + (ADR_WRITE_RI_COLUMNS01__06 << 1));
        MOVS     R5,#+1694498816
        MOVS     R4,R5
//  538     chGbl__LedColumns__RW_VAL = 0xff;
        MOVS     R5,#+255
        LDR.N    R6,??DataTable13_20
        STRB     R5,[R6, #+0]
//  539     *((char *) pvRlc) = chGbl__LedColumns__RW_VAL;
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        STRB     R5,[R4, #+0]
//  540     //Select Led
//  541     for (i = 0; i < TOTAL_LEDS; i++) {
        MOVS     R5,#+0
        MOVS     R0,R5
??LedAuxOp3_0:
        CMP      R0,#+26
        BGE.N    ??LedAuxOp3_1
//  542         if (((UI32Bit *) pv)->ul_val & (1 << i)) { //Set bit
        LDR      R5,[R1, #+0]
        LSRS     R5,R5,R0
        LSLS     R5,R5,#+31
        BPL.N    ??LedAuxOp3_2
//  543             j = HLSelectorTable[i].row;
        LDR.N    R5,??DataTable13_21
        MOVS     R6,#+3
        MLA      R5,R6,R0,R5
        LDRB     R5,[R5, #+1]
        MOVS     R3,R5
//  544             if (j == HL_RC) {
        CMP      R3,#+3
        BNE.N    ??LedAuxOp3_2
//  545                 j = HLSelectorTable[i].column;
        LDR.N    R5,??DataTable13_21
        MOVS     R6,#+3
        MLA      R5,R6,R0,R5
        LDRB     R5,[R5, #+2]
        MOVS     R3,R5
//  546                 chGbl__LedColumns__RW_VAL &= ~(1 << j);
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        MOVS     R6,#+1
        LSLS     R6,R6,R3
        BICS     R5,R5,R6
        LDR.N    R6,??DataTable13_20
        STRB     R5,[R6, #+0]
//  547             }
//  548         }
//  549     }
??LedAuxOp3_2:
        ADDS     R0,R0,#+1
        B.N      ??LedAuxOp3_0
//  550     *((char *) pvRlc) = chGbl__LedColumns__RW_VAL;
??LedAuxOp3_1:
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        STRB     R5,[R4, #+0]
//  551 return i;
        POP      {R4-R6}
        BX       LR               ;; return
//  552 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  553 long LedAuxOp4(long l,void *pv){
LedAuxOp4:
        PUSH     {R4-R6}
        MOVS     R2,R0
//  554     register long i,j;
//  555     register void *pvRlc;
//  556     i = lGlbOperationReflector;
        LDR.N    R5,??DataTable13_9
        LDR      R5,[R5, #+0]
        MOVS     R0,R5
//  557     i |= 1 << l;
        MOVS     R5,#+1
        LSLS     R5,R5,R2
        ORRS     R0,R5,R0
//  558     lGlbOperationReflector = i;
        LDR.N    R5,??DataTable13_9
        STR      R0,[R5, #+0]
//  559     //*((char*)pv) = i;
//  560     pvRlc = (void *) (((long) NOR_PSRAM_BANK2) + (ADR_WRITE_RDO__REL_1_6__ROWS_A__D << 1));
        MOVS     R5,#+1702887424
        MOVS     R4,R5
//  561     *((char *) pvRlc) = chGbl_REL_1_6__ROWS_A_D__RW_VAL | (1 << HL_RD);
        LDR.N    R5,??DataTable13_19
        LDRB     R5,[R5, #+0]
        ORRS     R5,R5,#0x10
        STRB     R5,[R4, #+0]
//  562     pvRlc = (void *) (((long) NOR_PSRAM_BANK2) + (ADR_WRITE_RI_COLUMNS01__06 << 1));
        MOVS     R5,#+1694498816
        MOVS     R4,R5
//  563     chGbl__LedColumns__RW_VAL = 0xff;
        MOVS     R5,#+255
        LDR.N    R6,??DataTable13_20
        STRB     R5,[R6, #+0]
//  564     *((char *) pvRlc) = chGbl__LedColumns__RW_VAL;
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        STRB     R5,[R4, #+0]
//  565     //Select Led
//  566     for (i = 0; i < TOTAL_LEDS; i++) {
        MOVS     R5,#+0
        MOVS     R0,R5
??LedAuxOp4_0:
        CMP      R0,#+26
        BGE.N    ??LedAuxOp4_1
//  567         if (((UI32Bit *) pv)->ul_val & (1 << i)) { //Set bit
        LDR      R5,[R1, #+0]
        LSRS     R5,R5,R0
        LSLS     R5,R5,#+31
        BPL.N    ??LedAuxOp4_2
//  568             j = HLSelectorTable[i].row;
        LDR.N    R5,??DataTable13_21
        MOVS     R6,#+3
        MLA      R5,R6,R0,R5
        LDRB     R5,[R5, #+1]
        MOVS     R3,R5
//  569             if (j == HL_RD) {
        CMP      R3,#+4
        BNE.N    ??LedAuxOp4_2
//  570                 j = HLSelectorTable[i].column;
        LDR.N    R5,??DataTable13_21
        MOVS     R6,#+3
        MLA      R5,R6,R0,R5
        LDRB     R5,[R5, #+2]
        MOVS     R3,R5
//  571                 chGbl__LedColumns__RW_VAL &= ~(1 << j);
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        MOVS     R6,#+1
        LSLS     R6,R6,R3
        BICS     R5,R5,R6
        LDR.N    R6,??DataTable13_20
        STRB     R5,[R6, #+0]
//  572             }
//  573         }
//  574     }
??LedAuxOp4_2:
        ADDS     R0,R0,#+1
        B.N      ??LedAuxOp4_0
//  575     *((char *) pvRlc) = chGbl__LedColumns__RW_VAL;
??LedAuxOp4_1:
        LDR.N    R5,??DataTable13_20
        LDRB     R5,[R5, #+0]
        STRB     R5,[R4, #+0]
//  576 return i;
        POP      {R4-R6}
        BX       LR               ;; return
//  577 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  578 long LedAuxOp5(long l,void *pv){
LedAuxOp5:
        MOVS     R2,R0
//  579     register long i;
//  580 	register void *pvRlc;
//  581         i = lGlbOperationReflector;
        LDR.N    R3,??DataTable13_9
        LDR      R3,[R3, #+0]
        MOVS     R0,R3
//  582     i |= 1<<l;
        MOVS     R3,#+1
        LSLS     R3,R3,R2
        ORRS     R0,R3,R0
//  583     lGlbOperationReflector = i;
        LDR.N    R3,??DataTable13_9
        STR      R0,[R3, #+0]
//  584     *((char*)pv) = i;
        STRB     R0,[R1, #+0]
//  585 return i;
        BX       LR               ;; return
//  586 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13:
        DC32     sh1MsRegisteredTimers

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_1:
        DC32     chGlSem

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_2:
        DC32     pHeadTmrNode

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_3:
        DC32     uCh_MAX_Amt_1_MS_TMR

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_4:
        DC32     pTailTmrNode

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_5:
        DC32     0x64c00000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_6:
        DC32     0x65c00000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_7:
        DC32     chCounterLedService

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_8:
        DC32     chNumIndependentParts

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_9:
        DC32     lGlbOperationReflector

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_10:
        DC32     LedStateUI32Bit

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_11:
        DC32     LedRawStateUI32Bit

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_12:
        DC32     arrFnPtr

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_13:
        DC32     ?_0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_14:
        DC32     sDiCfg

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_15:
        DC32     arTimerDi

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_16:
        DC32     DiHrdStateUI32Bit

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_17:
        DC32     CH_AMOUNT_DI

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_18:
        DC32     lCtr

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_19:
        DC32     chGbl_REL_1_6__ROWS_A_D__RW_VAL

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_20:
        DC32     chGbl__LedColumns__RW_VAL

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable13_21:
        DC32     HLSelectorTable

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//  587 
// 
//   114 bytes in section .bss
//    17 bytes in section .data
//   119 bytes in section .rodata
// 1 954 bytes in section .text
// 
// 1 954 bytes of CODE  memory
//   119 bytes of CONST memory
//   131 bytes of DATA  memory
//
//Errors: none
//Warnings: 2
