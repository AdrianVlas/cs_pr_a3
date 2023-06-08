#ifndef I_PRT_TIMER_H
#define I_PRT_TIMER_H
typedef long(*fnPLpvrL)(long l,void *pv);
//-  pointer to a exec function two param long void* return long
typedef void(*fnPpvrV)(void *pv);
typedef void(*fnPVrV) (void *pv);
enum FIX_LED_NAMES_BITS{
    LED_IDX_BLOCK_BIT   = 24,
    LED_IDX_ALARM_BIT   = 25,
    LED_IDX_MUTE_BIT    = 1,
    LED_IDX_EROR_C_BIT  = 23,
    LED_IDX_EROR_NC_BIT = 1,
    LED_IDX_RUN_BIT     = 22
};

typedef struct TmrNode_t{
    long lTmrVal;
    void *next;
}TmrNode;
typedef union {

    unsigned char      ar_uch[4];      //
    unsigned short     ar_ush[2];      //
    unsigned long int  ul_val;         //
} UI32Bit;
extern const char CH_AMOUNT_DI ;
typedef struct DiHrdStateData_tag{
char arChDurationDI[19];//Time-out for apopriate DI
UI32Bit DiTypeSignal;//OFF_BYTE_TypeSignal

UI32Bit DiHrdStateUI32Bit;//Copy DiHrdStateUI32Bit;//OFF_BYTE_PIN
UI32Bit DiAND;//OFF_BYTE_AND
UI32Bit DiOR;//OFF_BYTE_OR
UI32Bit DiStartUP;//OFF_BYTE_DI_StartUP
char *pDITmr;//Begin timer0//OFF_BYTE_DI_timer0
UI32Bit DiState;//OFF_BYTE_DI_State
//DInRawState
}DICfgSuit;
extern void  TmrCalls(void);
extern char chGlSem ;
//fix max amount available in system timers
extern const unsigned short uSh_MAX_Amt_1_MS_TMR  ;
//counter for 1ms Timers <-now Reserved as is the functionaliyi should move to locals Vars
//extern short  sh1MsCtrServicedTimers;
extern short  sh1MsRegisteredTimers;//Max amount fix timers
extern TmrNode *pHeadTmrNode; //Pointer on Firsst
extern TmrNode *pTailTmrNode;
extern TmrNode *PCurrNode;
//Semafor for Stop Processing
extern long RegisterTimer(TmrNode *pNode);

//Iterating over a list void print_list(node_t * head)
//All Insert Functions Return Registered Number 0-False
//All Dell Functions Return old Registered Number If Ok 0-False
//Adding an item to the end of the list
extern long TallingList(TmrNode *pNode);
//Adding an item to the beginning of the list (pushing to the list)
extern long PushTmrNode(TmrNode *pNode);
//Adding an item to the special position of the list (cutting to the list)
extern long IncreaseTmrList(TmrNode *pNode,long lPos);
//Removing the first item (popping from the list)
extern long PopTmrNode(TmrNode *pNode);
//Removing the last item of the list
extern long CuttingList(TmrNode *pNode);
//Removing a specific item
extern long DecreaseTmrList(TmrNode *pNode,long lPos);
extern void ClrTmrVars(void);
//counter for 2ms Timers
//Pointer on Firsst

//counter for 5ms Timers
//Pointer on Firsst

//counter for 10 ms Timers
//Pointer on Firsst

//counter for 50 ms Timers
//Pointer on Firsst

//counter for 100 ms Timers
//Pointer on Firsst
extern UI32Bit DiHrdStateUI32Bit;
extern UI32Bit DoStateUI32Bit;
extern UI32Bit LedStateUI32Bit;
extern UI32Bit DoCheckUI32Bit;
extern UI32Bit DoHdwUI32Bit;

extern void RdHrdIn  (void *pv);
extern void SetHrdOut(void *pv);
extern void SetHrdLed(void *pv);
extern void UpdateStateDI (void);
extern void UpdateDICfgSuit(long lIdxDi, long lTypeSignal, long lDurationDI );

long LedAuxOp1(long l,void *pv);
long LedAuxOp2(long l,void *pv);
long LedAuxOp3(long l,void *pv);
long LedAuxOp4(long l,void *pv);
long LedAuxOp5(long l,void *pv);

#endif

