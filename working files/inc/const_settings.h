#ifndef __CONST_SETTINGS__
#define __CONST_SETTINGS__

#define NUMBER_IN_AND                   8
#define NUMBER_IN_OR                    8

enum _control_array
{
  CA_INPUT = 0,
  CA_OUTPUT,
  CA_LED,
  
  CA_STANDART_LOGIC_AND,
  CA_STANDART_LOGIC_OR,
  CA_STANDART_LOGIC_XOR,
  CA_STANDART_LOGIC_NOT,
  CA_STANDART_LOGIC_TIMER,
  CA_STANDART_LOGIC_TRIGGER,

  CA_MEANDER,
  
  CA_MAX
    
};



enum _protect_control_array
{
  PCA_TIMERS = 0,    //Таймери
  PCA_AF,            //Активні функції
  PCA_TF,            //Триґерні функції
  PCA_EM,            //Додаткова пам'ять для вибраного функціонального блоку
  
  PCA_MAX
};

enum _signals_of_INPUT
{
  INPUT_OUT = 0,
  
  INPUT_SIGNALS
    
};

enum _signals_of_OUTPUT
{
  OUTPUT_RAW = 0,
  OUTPUT_OUT,
  
  OUTPUT_SIGNALS
    
};

enum _signals_of_LED
{
  LED_RAW = 0,
  LED_OUT,
  
  LED_SIGNALS
    
};


enum _signals_of_AND
{
  AND_OUT = 0,
  
  AND_SIGNALS
    
};

enum _signals_of_OR
{
  OR_OUT = 0,
  
  OR_SIGNALS
    
};

enum _signals_of_XOR
{
  XOR_OUT = 0,
  
  XOR_SIGNALS
    
};

enum _signals_of_NOT
{
  NOT_OUT = 0,
  
  NOT_SIGNALS
    
};

enum _signals_of_TIMER
{
  TIMER_OUT = 0,
  
  TIMER_SIGNALS
    
};

enum _signals_of_TRIGGER
{
  TRIGGER_OUT = 0,
  
  TRIGGER_SIGNALS
    
};

enum _signals_of_MEANDER
{
  MEANDER_OUT = 0,
  
  MEANDER_SIGNALS
    
};


#endif
