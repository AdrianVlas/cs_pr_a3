#pragma once


#ifndef LU_CFG_INFO
#define LU_CFG_INFO
typedef struct LUCfgInfo_tag{
void* pvLUClass;
void* pvCfgSuit;
void* pvChangeSuitFn;
}LUCfgInfo;


#endif


enum TYPE_LU_OP {
LU_OP_NULL = 1,
LU_OP_AND,
LU_OP_OR ,
LU_OP_XOR,
LU_OP_NOT,
LU_OP_MEANDR,
LU_OP_READ_DI,
LU_OP_SET_OUT,
LU_OP_SET_LED,
LU_OP_MFT,
LU_OP_LSS,
LU_OP_BGS,
LU_OP_D_TRG__4_2,
LU_OP_F_KEY,
LU_OP_TU,
LU_OP_TS,
LU_OP_LOG,
LU_OP_STNG_FIX

};
 void AND_Op    (void *pObj);
 void OR__Op    (void *pObj);
 void XOR_Op    (void *pObj);
 void NOT_Op    (void *pObj);
 void Meandr_Op (void *pObj);
 void Null_OP   (void *pObj);
 void READ_DI_Op(void *pObj);
 void SET_OUT_Op(void *pObj);
 void SET_LED_Op(void *pObj);
 void Mft_Op    (void *pObj);








/* 
#ifndef LU_OUT_DSC
#define LU_OUT_DSC
typedef struct tag_LUInputDsc{
	short shIdLUStng  ;//Type LU Described in settings
	short shOrdNumStng;//Order Num LU Described in settings
	char  chOrdNumOut ;// this LU Out Order Num
	//char *pStateOut;
}LUOutDsc;//In future compres in BitField
#endif
*/


typedef long(*logicfnptr1)(void*pIn,void *pOut);//-  pointer to a exec function
//class CLUBase;
typedef void(*logicfnptr)(void *pObj);//-  pointer to a exec function

typedef  union{
        char ch;
        short sh;
        long l;
    } UNNCLUBaseAuxInfo;


class BaseInPoint;
class CLUBase
{
public:
	CLUBase(void);
	~CLUBase(void);
	CLUBase(CLUBase&);
	CLUBase(char chM,char chI,char chNumIn,char chNumOut);
	CLUBase& operator= (const CLUBase&);
//    static  char chCBL_II;
    static UNNCLUBaseAuxInfo m_AuxInfo;
	void* pIn;//List Addr//BaseInPoint* pIn;//List Addr
//	struct ch{
		char chMaxIteratoin;
		char chIteration;
		char chNumInput;
		char chNumOutput;
		char chTypeLogicFunction;//enum ID_LUOp
		char chLinkSetOn;
//	};
//	struct sh{
	short shShemasIdLUStng  ;//Type LU Described in settings
	short shShemasOrdNumStng;//Order Num LU Described in settings
	short shLUBieldOrdNum;//Order Num when bield LU
//	};
	//long lIn;
	//long lOut;
	logicfnptr LogicFunc;
		//In Reference
	
	//Out Reference
	void* pOut;//List Addr//BaseInPoint* pOut;//List Addr
    void* pvCfgLN;
	void SetOrderNumber(void);
	friend void AND_Op    (void *pObj);
	friend void OR__Op    (void *pObj);
	friend void XOR_Op    (void *pObj);
	friend void NOT_Op    (void *pObj);
	friend void Meandr_Op (void *pObj);
	friend void Null_OP   (void *pObj);
	friend void READ_DI_Op(void *pObj);
	friend void SET_OUT_Op(void *pObj);
	friend void SET_LED_Op(void *pObj);
	
	friend void SetupCircutLinks(void *pLULinksInfo, void*pObj);
	static short shOrderNumberCLUBase;
};



//extern inline void Null_OP   (void *pObj);//{}
//extern inline void NOT_Op    (void *pObj);//{}
