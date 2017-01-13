#ifndef __CONST_SETTINGS__
#define __CONST_SETTINGS__

#define NUMBER_IN_AND                   8
#define NUMBER_IN_OR                    8

enum _control_array_index
{
  CA_STANDART_LOGIC_AND = 0,
  CA_STANDART_LOGIC_OR,
  CA_STANDART_LOGIC_XOR,
  CA_STANDART_LOGIC_NOT,
  CA_STANDART_LOGIC_TIMER,
  CA_STANDART_LOGIC_TRIGGER,
  
  CA_MAX
    
};



enum _protect_control_array
{
  PCA_TIMERS = 0,    //Таймери
  PCA_AF,            //Активні функції
  PCA_TF,            //Триґерні функції
  
  PCA_MAX
};

#endif
