#ifndef __CONST_MF_TIMERS_MENU2__
#define __CONST_MF_TIMERS_MENU2__

enum __index_delay_timer_m2
{
  INDEX_DELAY_TIMER_M2_PAUSE = 0,
  INDEX_DELAY_TIMER_M2_WORK,
  
  MAX_ROW_DELAY_TIMER_M2
};

#define COL_DELAY_TIMER_PAUSE_BEGIN                3
#define COL_DELAY_TIMER_PAUSE_COMMA                6
#define COL_DELAY_TIMER_PAUSE_END                  8

#define COL_DELAY_TIMER_WORK_BEGIN                 3
#define COL_DELAY_TIMER_WORK_COMMA                 6
#define COL_DELAY_TIMER_WORK_END                   8

enum __index_ctrl_timer_m2
{
  INDEX_CTRL_TIMER_M2_TYPE = 0,
  
  MAX_ROW_CTRL_TIMER_M2
};

#define MASKA_CTRL_TIMER_M2  ((1 << MAX_ROW_CTRL_TIMER_M2) - 1)

#endif 
