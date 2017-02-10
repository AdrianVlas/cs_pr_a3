#ifndef __CONST_SETTINGS__
#define __CONST_SETTINGS__

#define BIT_CHANGED_CONFIGURATION       0
#define MASKA_CHANGED_CONFIGURATION     (1 << BIT_CHANGED_CONFIGURATION)
#define BIT_CHANGED_SETTINGS            1
#define MASKA_CHANGED_SETTINGS          (1 << BIT_CHANGED_SETTINGS)

#define NUMBER_IN_AND                   8
#define NUMBER_IN_OR                    8

enum _id_fb
{
  _ID_FB_FIRST_ALL = 1,                                 /*1*/
  
    _ID_FB_FIRST_FIX = _ID_FB_FIRST_ALL,                /*1*/

      ID_FB_CONTROL_BLOCK = _ID_FB_FIRST_FIX,           /*1*/
      
    _ID_FB_LAST_FIX,                                    /*2*/

    _ID_FB_FIRST_VAR = _ID_FB_LAST_FIX,                 /*2*/
    
      ID_FB_INPUT = _ID_FB_FIRST_VAR,                   /*2*/
      ID_FB_OUTPUT,                                     /*3*/
      ID_FB_LED,                                        /*4*/
  
      ID_FB_AND,                                        /*5*/
      ID_FB_OR,                                         /*6*/
      ID_FB_XOR,                                        /*7*/
      ID_FB_NOT,                                        /*8*/

      ID_FB_TIMER,                                      /*9*/
      ID_FB_TRIGGER,                                    /*10*/

      ID_FB_MEANDER,                                    /*11*/
  
    _ID_FB_LAST_VAR,                                    /*12*/

  _ID_FB_LAST_ALL = _ID_FB_LAST_VAR                     /*12*/
};

#define NUMBER_FIX_BLOCKS       (_ID_FB_LAST_FIX - _ID_FB_FIRST_FIX)
#define NUMBER_VAR_BLOCKS       (_ID_FB_LAST_VAR - _ID_FB_FIRST_VAR)
#define NUMBER_ALL_BLOCKS       (NUMBER_FIX_BLOCKS + NUMBER_VAR_BLOCKS)

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
