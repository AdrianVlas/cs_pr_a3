#ifndef __CONST_OUTPUTS_MENU2__
#define __CONST_OUTPUTS_MENU2__

enum __index_ctrl_output_m2
{
  INDEX_CTRL_OUTPUT_M2_N_T = 0, /*N - normal; T - trigger*/
  INDEX_CTRL_OUTPUT_M2_C_I, /*S - Constant; I - impulse*/
  INDEX_CTRL_OUTPUT_M2_SI_EI, /*SI - simple impulse; EI - expanded impulse*/

  _MAX_ROW_CTRL_OUTPUT_M2_BITS_SETTINGS,
  
  INDEX_CTRL_OUTPUT_M2_MEANDER1 = _MAX_ROW_CTRL_OUTPUT_M2_BITS_SETTINGS,
  INDEX_CTRL_OUTPUT_M2_MEANDER2,
  
  MAX_ROW_CTRL_OUTPUT_M2
};

#define MASKA_CTRL_OUTPUT_M2  ((1 << _MAX_ROW_CTRL_OUTPUT_M2_BITS_SETTINGS) - 1)

#endif 
