/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LULan.hpp
 * Author: user
 *
 * Created on 25 07 2018, 17:34
 */
#pragma once
#ifndef LULAN_HPP
#define LULAN_HPP

#include "lubase.h"
const short shCLULan_x_y_AmtOut = 8;
const short shCLULan_x_y_AmtIn  = 8;

enum Lan__2_1_INPUT_NAMES{
Lan__9_8_IN_NAME__IN1 =  1,//Connection Input
Lan__9_8_IN_NAME__IN2 =  2,//Connection Input
Lan__9_8_IN_NAME__IN3 =  3,//Connection Input
Lan__9_8_IN_NAME__IN4 =  4,//Connection Input
Lan__9_8_IN_NAME__IN5 =  5,//Connection Input
Lan__9_8_IN_NAME__IN6 =  6,//Connection Input
Lan__9_8_IN_NAME__IN7 =  7,//Connection Input
Lan__9_8_IN_NAME__IN8 =  8,//Connection Input
Lan__9_8_IN_NAME__BLOCK_L,
//
TOTAL_Lan__9_8_IN = Lan__9_8_IN_NAME__BLOCK_L
};

enum Lan__2_1_OUTPUT_NAMES{
//Lan__2_1_OUT_NAME_CO = 1,//CO - means connection Out
Lan__9_8_OUT_NAME__CO_1 =  1,
Lan__9_8_OUT_NAME__CO_2 =  2,
Lan__9_8_OUT_NAME__CO_3 =  3,
Lan__9_8_OUT_NAME__CO_4 =  4,
Lan__9_8_OUT_NAME__CO_5 =  5,
Lan__9_8_OUT_NAME__CO_6 =  6,
Lan__9_8_OUT_NAME__CO_7 =  7,
Lan__9_8_OUT_NAME__CO_8 =  8,
TOTAL_Lan__9_8_OUTPUT = Lan__9_8_OUT_NAME__CO_8
};


class CLULan :
public CLUBase {
public:
    CLULan(void);
    ~CLULan(void);
    CLULan(char chM, char chI);
    void UpdateCLULan(void);

    char* arrPchIn[TOTAL_Lan__9_8_IN]; // 
    char  arrOut  [TOTAL_Lan__9_8_OUTPUT]; //
    //    char chError;
    //    char chQ;
    //    char chIn_C;
    friend void Lan__9_8_Op(void *pObj);
};
extern void Lan__9_8_Op  (void *pObj);




#endif /* LULAN_HPP */

