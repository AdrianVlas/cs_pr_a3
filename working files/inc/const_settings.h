#ifndef __CONST_SETTINGS__
#define __CONST_SETTINGS__

#define BIT_CHANGED_CONFIGURATION       0
#define MASKA_CHANGED_CONFIGURATION     (1 << BIT_CHANGED_CONFIGURATION)
#define BIT_CHANGED_SETTINGS            1
#define MASKA_CHANGED_SETTINGS          (1 << BIT_CHANGED_SETTINGS)
#define BIT_MENU_LOCKS                  2
#define MASKA_MENU_LOCKS                (1 << BIT_MENU_LOCKS)
#define BIT_USB_LOCKS                   3
#define MASKA_USB_LOCKS                 (1 << BIT_USB_LOCKS)
#define BIT_RS485_LOCKS                 4
#define MASKA_RS485_LOCKS               (1 << BIT_RS485_LOCKS)

#define NUMBER_IN_AND                   8
#define NUMBER_IN_OR                    8

#define SFIFT_PARAM_ID                  24
#define SFIFT_PARAM_N                   16
#define SFIFT_PARAM_OUT                 0

#define MASKA_PARAM_ID                  ((1 << (8*sizeof(uint32_t) - SFIFT_PARAM_ID )) - 1)
#define MASKA_PARAM_N                   ((1 << (SFIFT_PARAM_ID     - SFIFT_PARAM_N  )) - 1)
#define MASKA_PARAM_OUT                 ((1 << (SFIFT_PARAM_N      - SFIFT_PARAM_OUT)) - 1)

enum _id_fb
{
  _ID_FB_FIRST_ALL = 1,                                                 /*1*/
  
    _ID_FB_FIRST_FIX = _ID_FB_FIRST_ALL,                                /*1*/

      ID_FB_CONTROL_BLOCK = _ID_FB_FIRST_FIX,                           /*1*/
      
    _ID_FB_LAST_FIX,                                                    /*2*/

    _ID_FB_FIRST_VAR = _ID_FB_LAST_FIX,                                 /*2*/
    
      _ID_FB_FIRST_VAR_NONE_CHANGED = _ID_FB_FIRST_VAR,                 /*2*/

        ID_FB_INPUT = _ID_FB_FIRST_VAR_NONE_CHANGED,                    /*2*/
        ID_FB_OUTPUT,                                                   /*3*/
        ID_FB_LED,                                                      /*4*/

      _ID_FB_LAST_VAR_NONE_CHANGED,                                     /*5*/

      _ID_FB_FIRST_VAR_CHANGED = _ID_FB_LAST_VAR_NONE_CHANGED,          /*5*/
      
        ID_FB_AND = _ID_FB_FIRST_VAR_CHANGED,                           /*5*/
        ID_FB_OR,                                                       /*6*/
        ID_FB_XOR,                                                      /*7*/
        ID_FB_NOT,                                                      /*8*/

        ID_FB_TIMER,                                                    /*9*/
        ID_FB_TRIGGER,                                                  /*10*/

        ID_FB_MEANDER,                                                  /*11*/
  
      _ID_FB_LAST_VAR_CHANGED,                                          /*12*/
      
    _ID_FB_LAST_VAR = _ID_FB_LAST_VAR_CHANGED,                          /*12*/

  _ID_FB_LAST_ALL = _ID_FB_LAST_VAR                                     /*12*/
};

#define NUMBER_FIX_BLOCKS       (_ID_FB_LAST_FIX - _ID_FB_FIRST_FIX)

#define NUMBER_VAR_BLOCKS_NONE_CHANGED  (_ID_FB_LAST_VAR_NONE_CHANGED - _ID_FB_FIRST_VAR_NONE_CHANGED)
#define NUMBER_VAR_BLOCKS_CHANGED       (_ID_FB_LAST_VAR_CHANGED      - _ID_FB_FIRST_VAR_CHANGED     )

#define NUMBER_VAR_BLOCKS       (NUMBER_VAR_BLOCKS_NONE_CHANGED + NUMBER_VAR_BLOCKS_CHANGED)
#define NUMBER_ALL_BLOCKS       (NUMBER_FIX_BLOCKS + NUMBER_VAR_BLOCKS)

enum _signals_of_INPUT
{
  INPUT_OUT = 0,
  
  INPUT_SIGNALS
    
};

enum _signals_of_OUTPUT
{
  OUTPUT_OUT = 0,
  OUTPUT_BOARD,
  
  OUTPUT_SIGNALS
    
};
enum _output_input_signals
{
  OUTPUT_LOGIC_INPUT = 0,
  OUTPUT_RESET,
  OUTPUT_MEANDER1,
  OUTPUT_MEANDER2,
  
  OUTPUT_MAX_NUMBER
};



enum _signals_of_LED
{
  LED_OUT = 0,
  LED_BOARD,
  
  LED_SIGNALS
    
};
enum _led_input_signals
{
  LED_LOGIC_INPUT = 0,
  LED_RESET,
  LED_MEANDER1,
  LED_MEANDER2,
  
  LED_MAX_NUMBER
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
enum _output_timer_signals
{
  TIMER_LOGIC_INPUT = 0,
  TIMER_RESET,
  
  TIMER_MAX_NUMBER
};


enum _input_signals_of_TRIGGER
{
  INPUT_TRIGGER_SET = 0,
  INPUT_TRIGGER_RESET,
  INPUT_TRIGGER_D,
  INPUT_TRIGGER_C,
  
  INPUT_TRIGGER_SIGNALS
    
};

enum _signals_of_TRIGGER
{
  TRIGGER_OUT = 0,
  TRIGGER_OUT_INV,
  
  TRIGGER_SIGNALS
    
};

enum _signals_of_MEANDER
{
  MEANDER_OUT = 0,
  
  MEANDER_SIGNALS
    
};


#endif
