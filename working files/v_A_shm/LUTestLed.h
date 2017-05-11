#pragma once
#include "lubase.h"
const short shCLUTestLed_x_y_AmtOut = 1;
const short shCLUTestLed_x_y_AmtIn  = 0;
#include "LuGenOp.h"
#include "prtTmr.hpp"
enum TEST_LED_INPUT_NAMES{
TEST_LED_IN_NAME__TEST_K = 1 ,
TEST_LED_IN_NAME__RESET_I     ,

TOTAL_TEST_LED_IN = TEST_LED_IN_NAME__RESET_I
};

enum TEST_LED_OUTPUT_NAMES{
TEST_LED_OUT_NAME_TEST_M,
TEST_LED_OUT_NAME_TLED00,
TEST_LED_OUT_NAME_TLED01,
TEST_LED_OUT_NAME_TLED02,
TEST_LED_OUT_NAME_TLED03,
TEST_LED_OUT_NAME_TLED04,
TEST_LED_OUT_NAME_TLED05,
TEST_LED_OUT_NAME_TLED06,
TEST_LED_OUT_NAME_TLED07,
TEST_LED_OUT_NAME_TLED08,
TEST_LED_OUT_NAME_TLED09,
TEST_LED_OUT_NAME_TLED10,
TEST_LED_OUT_NAME_TLED11,
TEST_LED_OUT_NAME_TLED12,
TEST_LED_OUT_NAME_TLED13,
TEST_LED_OUT_NAME_TLED14,
TEST_LED_OUT_NAME_TLED15,
TEST_LED_OUT_NAME_TLED16,
TEST_LED_OUT_NAME_TLED17,
TEST_LED_OUT_NAME_TLED18,
TEST_LED_OUT_NAME_TLED19,
TEST_LED_OUT_NAME_TLED20,
TEST_LED_OUT_NAME_TLED21,
TEST_LED_OUT_NAME_TLED22,


TOTAL_TEST_LED_OUTPUT = TEST_LED_OUT_NAME_TLED22
};

typedef struct TestLedInOutParam_t{
    
    char* pChTest;
    char* pChReset;
    
}TestLedInOutParam;



class CLUTestLed :
public CLUBase {
public:
    CLUTestLed(void);
    ~CLUTestLed(void);
    void CalcLedSchematic(void);
    char* arrPchIn[TOTAL_TEST_LED_IN];//
    char m_arChQTrg[TEST_LED_OUT_NAME_TLED22];
    char m_arChInC[TEST_LED_OUT_NAME_TLED22];
	//char m_arChErrorQTrg[TEST_LED_OUT_NAME_TLED22];;
	char  arrOut  [TOTAL_TEST_LED_OUTPUT];
    char m_chLinkedTimers; //Field bit
    TmrNode m_Node1_1Ms;
    char m_chStateT1_1Ms;
    long T1_1Ms(long lActivKey);
    
    TmrNode m_NodeTicAltZp5ms;//Zero Point 5 ms
    char m_chStateAltZp5ms;
    char m_chOutGen;
    long TAltZp5ms(long lActivKey);
    
    inline void SetStateVarchQTrg(long lIdTrg, char&chQTrg);
	inline void SetStateVarchInC (long lIdTrg, char&chInC);
//	inline void SetStateVarchErrorQTrg(long lIdTrg, char&chErrorQTrg);
	inline long GetStateVarchQTrg(long lIdTrg);
//	inline long GetStateVarchErrorQTrg(long lIdTrg);
    inline long GetStateVarchInC (long lIdTrg);
    long LinkTestLedTimers(void);
    void UpdateCLUTestLed(void);
    void CalCLUTestLedSchematic(void);
};

