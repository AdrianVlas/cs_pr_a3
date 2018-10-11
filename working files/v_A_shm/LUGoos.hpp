/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LUGoos.hpp
 * Author: user
 *
 * Created on 25 07 2018, 17:37
 */

#ifndef LUGOOSE_HPP
#define LUGOOSE_HPP

#include "lubase.h"
#include <stdint.h>

const short shCLUGoose_x_y_AmtOut = 8;
const short shCLUGoose_x_y_AmtIn  = 8;

enum Goose__1_8_INPUT_NAMES{

//Goose__9_8_IN_NAME__IN1 =  1,
//Goose__9_8_IN_NAME__IN2 =  2,
//Goose__9_8_IN_NAME__IN3 =  3,
//Goose__9_8_IN_NAME__IN4 =  4,
//Goose__9_8_IN_NAME__IN5 =  5,
//Goose__9_8_IN_NAME__IN6 =  6,
//Goose__9_8_IN_NAME__IN7 =  7,
//Goose__9_8_IN_NAME__IN8 =  8,
Goose__1_8_IN_NAME__BLOCK_G = 1,

TOTAL_Goose__1_8_IN = Goose__1_8_IN_NAME__BLOCK_G
};

enum Goose__1_8_OUTPUT_NAMES{
//Goose__2_1_OUT_NAME_CO = 1,//CO - means connection Out
Goose__1_8_OUT_NAME__CO_1 =  1,
Goose__1_8_OUT_NAME__CO_2 =  2,
Goose__1_8_OUT_NAME__CO_3 =  3,
Goose__1_8_OUT_NAME__CO_4 =  4,
Goose__1_8_OUT_NAME__CO_5 =  5,
Goose__1_8_OUT_NAME__CO_6 =  6,
Goose__1_8_OUT_NAME__CO_7 =  7,
Goose__1_8_OUT_NAME__CO_8 =  8,
TOTAL_Goose__1_8_OUTPUT = Goose__1_8_OUT_NAME__CO_8
//TOTAL_Goose__2_1_OUTPUT = Goose__2_1_OUT_NAME_CO
};


class CLUGoose :
public CLUBase {
public:
    CLUGoose(void);
    ~CLUGoose(void);
    CLUGoose(char chM, char chI);
    void UpdateCLUGoose(void);

    char* arrPchIn[TOTAL_Goose__1_8_IN]; // 
    char arrOut   [TOTAL_Goose__1_8_OUTPUT]; //
    //    char chError;
    //    char chQ;
    unsigned char chIn_C;
    unsigned char chIn_E;
    friend void  Goose__1_8_Op  (void *pObj);
};
extern void Goose__1_8_Op  (void *pObj);
extern uint32_t  IEC_board_present;

#endif /* LUGOOSE_HPP */

