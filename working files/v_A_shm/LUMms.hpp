/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LUMms.hpp
 * Author: user
 *
 * Created on 25 07 2018, 17:35
 */

#ifndef LUMMS_HPP
#define LUMMS_HPP

#include "lubase.h"
const short shCLUMms_x_y_AmtOut = 8;
const short shCLUMms_x_y_AmtIn  = 2;

enum Mms__2_1_INPUT_NAMES{
//Mms__2_1_IN_NAME__CI = 1,//Connection Input
//Mms__10_8_IN_NAME__IN1 =  1,
//Mms__10_8_IN_NAME__IN2 =  2,
//Mms__10_8_IN_NAME__IN3 =  3,
//Mms__10_8_IN_NAME__IN4 =  4,
//Mms__10_8_IN_NAME__IN5 =  5,
//Mms__10_8_IN_NAME__IN6 =  6,
//Mms__10_8_IN_NAME__IN7 =  7,
//Mms__10_8_IN_NAME__IN8 =  8,
Mms__2_8_IN_NAME__BLOCK_M = 1,
Mms__2_8_IN_NAME__BLOCK_LR,
TOTAL_Mms__2_8_IN = Mms__2_8_IN_NAME__BLOCK_LR
};

enum Mms__2_1_OUTPUT_NAMES{
//Mms__2_1_OUT_NAME_CO = 1,//CO - means connection Out
Mms__2_8_OUT_NAME__CO_1 =  1,
Mms__2_8_OUT_NAME__CO_2 =  2,
Mms__2_8_OUT_NAME__CO_3 =  3,
Mms__2_8_OUT_NAME__CO_4 =  4,
Mms__2_8_OUT_NAME__CO_5 =  5,
Mms__2_8_OUT_NAME__CO_6 =  6,
Mms__2_8_OUT_NAME__CO_7 =  7,
Mms__2_8_OUT_NAME__CO_8 =  8,

TOTAL_Mms__2_8_OUTPUT = Mms__2_8_OUT_NAME__CO_8
};

class CLUMms :
public CLUBase {
public:
    CLUMms(void);
    ~CLUMms(void);
    CLUMms(char chM,char chI);
    void UpdateCLUMms(void);
    
    char* arrPchIn[TOTAL_Mms__2_8_IN];// 
	char  arrOut  [TOTAL_Mms__2_8_OUTPUT];//
//    char chError;

    friend void  Mms__2_8_Op  (void *pObj);
};
extern void Mms__2_8_Op  (void *pObj);


#endif /* LUMMS_HPP */

