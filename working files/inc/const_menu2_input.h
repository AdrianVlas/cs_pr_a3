#ifndef __CONST_INPUTS_MENU2__
#define __CONST_INPUTS_MENU2__

enum __index_delay_inputs_m2
{
  INDEX_DELAY_INPUT_M2_DOPUSK = 0,
  
  MAX_ROW_DELAY_INPUT_M2
};

#define COL_DELAY_INPUT_DOPUSK_BEGIN                5
#define COL_DELAY_INPUT_DOPUSK_END                  6

enum __index_ctrl_input_m2
{
  INDEX_CTRL_INPUT_M2_TYPE_SIGNAL = 0,
  
  MAX_ROW_CTRL_INPUT_M2
};

#define MASKA_CTRL_INPUT_M2  ((1 << MAX_ROW_CTRL_INPUT_M2) - 1)

#endif 
