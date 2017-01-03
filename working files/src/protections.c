#include "header.h"

/*****************************************************/
//Діагностика АЦП
/*****************************************************/
inline void diagnostyca_adc_execution(void)
{
  if (gnd_adc >0x51) _SET_BIT(set_diagnostyka, ERROR_GND_ADC_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_GND_ADC_TEST_BIT);

  if ((vref_adc <0x709) || (vref_adc > 0x8f5)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC_TEST_BIT);
  else _SET_BIT(clear_diagnostyka,ERROR_VREF_ADC_TEST_BIT);

  if ((vdd_adc <0x8F9) || (vdd_adc > 0xC24)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC_TEST_BIT);
}
/*****************************************************/

/*****************************************************/
//Пошук розрядності числа
/*****************************************************/
inline unsigned int norma_value(unsigned long long y)
{
  unsigned long long temp=y;
  unsigned int rezultat =0;
  if (temp == 0) return 0;

  while(temp !=0)
  {
    temp = temp>>1;
    rezultat++;
  }
  return rezultat-1;
}
/*****************************************************/

/*****************************************************/
//Пошук розрядності числа типу int
/*****************************************************/
inline unsigned int get_order(int value)
{
  unsigned int i = 0;

  if (value == 0) return 1;  
  if (value < 0) value =-value;

  while ((value >> (++i)) != 0); 

  return i;    
}
/*****************************************************/

/*****************************************************/
//Розрахунок кореня квадратного методом половинного ділення  з прогнозуванням розрядності числа
/*****************************************************/
unsigned int sqrt_64(unsigned long long y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned long long temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = (unsigned long long)c*(unsigned long long)c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//Розрахунок кореня квадратного методом половинного ділення  з прогнозуванням розрядності числа
/*****************************************************/
inline unsigned int sqrt_32(unsigned int y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned int temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = c*c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//Розрахунки віимірювань
/*****************************************************/
inline void calc_measurement(void)
{
  unsigned long long sum_sqr_data_local[NUMBER_ANALOG_CANALES];
  
  //Копіюємо вхідні велечини у локальні змінні
  /*
  Оскільки для інтеградбного розгахунку сума квадратів з період ділиться на період, 
  що для дискретного випадку аналогічно діленню на кількість виборок, то ми це ділення якраз і робимо зміщенням
  */
  unsigned int bank_sum_sqr_data_tmp = (bank_sum_sqr_data + 1) & 0x1;
  for(uint32_t i =0; i < NUMBER_ANALOG_CANALES; i++ )
  {
    /***/
    //Розраховуємо діюче значення 3I0 по інтегральній сформулі
    /***/
    /*Добуваємо квадратний корінь*/
    sum_sqr_data_local[i] = sqrt_64(sum_sqr_data[i][bank_sum_sqr_data_tmp]);
  
    /*Для приведення цього значення у мА треба помножити на свій коефіцієнт*/
    /*Ще сигнал зараз є підсиленим у 16 раз, тому ділим його на 16*/

    /*
    Ми маємо ще отримане число поділити на корнь з NUMBER_POINT = 32 = 16*2
    Тобто ми маємо поділити на 4*sqrt(2)
    4 це зміщення на 2
    ((MNOGNYK_I_D * X )>> VAGA_DILENNJA_I_D)/sqrt(2) тотожне
   (MNOGNYK_I_DIJUCHE_D * X )>> VAGA_DILENNJA_I_DIJUCHE_D 
  
    Якщо робити через пари (MNOGNYK_I_DIJUCHE_D;VAGA_DILENNJA_I_DIJUCHE_D) і (MNOGNYK_I_D;VAGA_DILENNJA_I_D)
    то виникає похибка при розрахунку вищих гармонік (що було коли для захистів велися такі розрахунки. У ЦС їх немає).
    Тому треба іти на такі спрощення виразів
    */
    float value_i_float = (unsigned int)(MNOGNYK_I_DIJUCHE_FLOAT*((float)sum_sqr_data_local[i])/(64.0f)); /*64 = 4*16. 16 - це підсилення каналів "Analog Input"; 4 - це sqrt(16), а 16 береться з того, що 32 = 16*2 */
    measurement[i] = (unsigned int)value_i_float; 
    /***/
  }
}
/*****************************************************/

/*****************************************************/
//Модуль обробки дискретних входів
/*****************************************************/
inline void input_scan(void)
{
  unsigned int state_inputs_into_pin, temp_state_inputs_into_pin; //Змінні у якій формуємо значення входів отримані із входів процесора (пінів)
  static unsigned int state_inputs_into_pin_trigger; //У цій змінній зберігається попередній стан піна, у випадку коли ми перевіряємо .чи утримається цей стан до кінця тактування таймера допуску

  /***************************/
  //У цій частині знімаємо стани входів процесора (пінів), які відповідають за дискретні входи
  /*
  -----------------------------
  значення поміщається у відпорвідні біти змінної state_inputs_into_pin
    "є     сигнал " - відповідає встановленому біту (1)
    "немає сигналу" - відповідає скинутому     біту (0)
  -----------------------------
  */
  unsigned int temp_state_inputs_into_pin_1 = _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_INPUTS_1) & ((1 << NUMBER_INPUTS_1) - 1);
  unsigned int temp_state_inputs_into_pin_2 = _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_INPUTS_2) & ((1 << NUMBER_INPUTS_2) - 1);
  temp_state_inputs_into_pin = temp_state_inputs_into_pin_1 | (temp_state_inputs_into_pin_2 << NUMBER_INPUTS_1);
  
  //Змінюємо порядок, щоб наймений номер відповідав нумерації на приладі
  state_inputs_into_pin = 0;
  for (unsigned int index = 0; index < NUMBER_INPUTS; index++)
  {
    if ((temp_state_inputs_into_pin & (1 << index)) != 0) 
    {
      if (index < NUMBER_INPUTS_1)
        state_inputs_into_pin |= 1 << (NUMBER_INPUTS_1 - index - 1);
      else
        state_inputs_into_pin |= 1 << index;
    }
  }
  /***************************/
  
  /***************************/
  //Обробка таймерів допуску дискретних входів
  /***************************/
  for(unsigned int i = 0; i < NUMBER_INPUTS; i++)
  {
    unsigned int maska = 1<<i;
    int max_value_timer = current_settings_prt.dopusk_dv[i];

    if (global_timers[INDEX_TIMER_INPUT_START + i] < 0)
    {
      //Провірка на зміну стану дискретного входу здійснюється тільки тоді, коли величина таймере є від'ємною
      //Що означає що таймер не запущений у попередній момент
      
      //Перевіряємо чи таеперішній стан входу відповідає попердньомук стану
      if ((state_inputs_into_pin & maska) != (state_inputs & maska))
      {
        //Якщо стан входу змінився, то виконуємо дії по зміні стану

        //1-дія: Запям'ятовуємо текучий стан входу
        state_inputs_into_pin_trigger &= ~maska;
        state_inputs_into_pin_trigger |= (state_inputs_into_pin & maska);

        //2-дія: Запускаємо таймер допуску дискретного входу
        global_timers[INDEX_TIMER_INPUT_START + i] = 0;
      }
    }
    else
    {
      //Якщо таймер запущений виконуємо дії з таймером
      if (global_timers[INDEX_TIMER_INPUT_START + i] < max_value_timer)
      {
        //Якщо таймер ще не дійшов до свого макисмуму, то просто збільшуємо його величину
        global_timers[INDEX_TIMER_INPUT_START + i] += DELTA_TIME_FOR_TIMERS;
        
        //У випадку, якщо тип сигналу на вхід подається змінний
        //і ми перевіряємо чи не відбувся перехід "є сигнал"->"немає сигналу"
        //то поява сигналу під час тактування таймера допуску означає, що сигнал на вході є - 
        //а це означає, що треба зупинити nаймер, бо переходу "є сигнал"->"немає сигналу" на протязі тактування таймеру не зафіксовано 
        if ((current_settings_prt.type_of_input_signal & maska) != 0)
        {
           if ((state_inputs_into_pin_trigger & maska) == 0)
           {
             if ((state_inputs_into_pin & maska) != 0)
               global_timers[INDEX_TIMER_INPUT_START + i] = -1;
           }
        }
      }
    }
    
    //Якщо величина таймера допуска знаходиться у свому максимальному значенні, то перевіряємо, чи фактично змінився стано входу
    if (global_timers[INDEX_TIMER_INPUT_START + i] >= max_value_timer)
    {
      //Перевіряємо, чи стан піна змінився у порівнянні із станом, який був на момент запуску таймера допуску дискретного входу
      unsigned int state_1, state_2;
        
      state_1 = state_inputs_into_pin_trigger & maska;
      state_2 = state_inputs_into_pin  & maska;
        
      if (state_1 == state_2)
      {
        //Якщо два стани співпадають, то ми вважаємо, що відбулася зіна стану дискретного входу і формуємо новий стан входу
        //При цьому враховуємо що для прявого    входу 1 - це активний вхід, а 0 - це пасивний вхід
        //                        для інверсного входу 0 - це активний вхід, а 1 - це пасивний вхід
          state_inputs &=  ~maska;
          state_inputs |=   state_2;
      }
        
      //У будь-якому випадк, чи змінився стан входу, чи ні, а оскілька таймер допуску дотактував до кінця, то скидаємотаймер у висхідне від'ємне занчення
      global_timers[INDEX_TIMER_INPUT_START + i] = -1;
    }
  }
  /***************************/
}
/*****************************************************/

/*****************************************************/
//Функція обробки таймерів
/*****************************************************/
inline void clocking_global_timers(void)
{
  //Опрацьовуємо дискретні входи
  input_scan();
  
  //опрацьовуємо всі решта таймери логіки
  for (unsigned int i = (INDEX_TIMER_INPUT_START + NUMBER_INPUTS); i < MAX_NUMBER_GLOBAL_TIMERS; i++)
  {
    if (global_timers[i] >= 0)
    {
      //Першою умовою того, що таймер треба тактувати є той факт, що величина таймеру не від'ємна

      //Перевіряємо чи треба збільшувати величину таймеру, якщо він ще не досягнув свого максимуму
      if (global_timers[i] <= (0x7fffffff - DELTA_TIME_FOR_TIMERS)) global_timers[i] += DELTA_TIME_FOR_TIMERS;
    }
  }
  
  if (++timer_meander >= PERIOD_SIGNAL_MEANDER)
  {
    timer_meander = 0;
    output_timer_meander ^= true;
  }
}
/*****************************************************/

/*****************************************************/
//Опрацювання визначуваних "І"
/*****************************************************/
inline void d_and_handler(volatile unsigned int *p_active_functions)
{
  unsigned int state_defined_and = 0;

  //Визначаємо стан всіх визначуваних "І" (не виставляючи поки що їх у робочому масиві)
  for (unsigned int i = 0; i < /*NUMBER_DEFINED_AND*/current_settings_prt.number_defined_and; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 0] & p_active_functions[0]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 0]) && 
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 1] & p_active_functions[1]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 1]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 2] & p_active_functions[2]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 2]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 3] & p_active_functions[3]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 3]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 4] & p_active_functions[4]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 4]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 5] & p_active_functions[5]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 5]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 6] & p_active_functions[6]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 6])
       )
    {
      state_defined_and |= (1 << i);
    }
  }

  //Установлюємо, або скидаємо визначувані "І" у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив p_active_functions у якому ще не встановлені нові значення виходів В-"І", тому що інші В-"І"
  можуть бути джерелом , але джерелом може буте попереднє значення В-"І", а не те,
  що зараз встановлюється. А оскілдьки ми встановлюємо значення у масиві
  p_active_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом встановлення/скидання)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
  {
    //Установлюємо, або скидаємо В-"І"
    unsigned int index_d_and = RANG_D_AND1 + i;
      
    if ((state_defined_and & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_and);
    else _CLEAR_BIT(p_active_functions, index_d_and);
  }
}
/*****************************************************/

/*****************************************************/
//Опрацювання визначуваних "АБО"
/*****************************************************/
inline void d_or_handler(volatile unsigned int *p_active_functions)
{
  unsigned int state_defined_or = 0;

  //Визначаємо стан всіх визначуваних "АБО" (не виставляючи поки що їх у робочому масиві)
  for (unsigned int i = 0; i < /*NUMBER_DEFINED_OR*/current_settings_prt.number_defined_or; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 0] & p_active_functions[0]) != 0) || 
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 1] & p_active_functions[1]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 2] & p_active_functions[2]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 3] & p_active_functions[3]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 4] & p_active_functions[4]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 5] & p_active_functions[5]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 6] & p_active_functions[6]) != 0)
       )
    {
      state_defined_or |= (1 << i);
    }
  }

  //Установлюємо, або скидаємо визначувані "АБО" у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив p_active_functions у якому ще не встановлені нові значення виходів В-"АБО", тому що інші В-"АБО"
  можуть бути джерелом , але джерелом може буте попереднє значення В-"АБО", а не те,
  що зараз встановлюється. А оскілдьки ми встановлюємо значення у масиві
  p_active_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом встановлення/скидання)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
  {
    //Установлюємо, або скидаємо В-"АБО"
    unsigned int index_d_or = RANG_D_OR1 + i;
      
    if ((state_defined_or & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_or);
    else _CLEAR_BIT(p_active_functions, index_d_or);
  }
}
/*****************************************************/

/*****************************************************/
//Опрацювання визначуваних "Викл.АБО"
/*****************************************************/
inline void d_xor_handler(volatile unsigned int *p_active_functions)
{
  unsigned int state_defined_xor = 0;

  //Визначаємо стан всіх визначуваних "Викл.АБО" (не виставляючи поки що їх у робочому масиві)
  for (unsigned int i = 0; i < /*NUMBER_DEFINED_XOR*/current_settings_prt.number_defined_xor; i++)
  {
    unsigned int temp_array[N_BIG];
    temp_array[0] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 0] & p_active_functions[0];
    temp_array[1] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 1] & p_active_functions[1];
    temp_array[2] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 2] & p_active_functions[2];
    temp_array[3] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 3] & p_active_functions[3];
    temp_array[4] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 4] & p_active_functions[4];
    temp_array[5] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 5] & p_active_functions[5];
    temp_array[6] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 6] & p_active_functions[6];
    
    if (
        (temp_array[0] != 0) || 
        (temp_array[1] != 0) ||
        (temp_array[2] != 0) ||
        (temp_array[3] != 0) ||
        (temp_array[4] != 0) ||
        (temp_array[5] != 0) ||
        (temp_array[6] != 0)
       )
    {
      unsigned int signals = 0;
      for (unsigned int j = 0; j < N_BIG; j++)
      {
        for (unsigned int k = 0; k < 32; k++)
        {
          if ((temp_array[j] & (1 << k)) != 0) signals++;
        }
      }
      if (signals == 1) state_defined_xor |= (1 << i);
    }
  }

  //Установлюємо, або скидаємо визначувані "Викл.АБО" у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив p_active_functions у якому ще не встановлені нові значення виходів В-"Викл.АБО", тому що інші В-"Викл.АБО"
  можуть бути джерелом , але джерелом може буте попереднє значення В-"Викл.АБО", а не те,
  що зараз встановлюється. А оскілдьки ми встановлюємо значення у масиві
  p_active_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом встановлення/скидання)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
  {
    //Установлюємо, або скидаємо В-"Викл.АБО"
    unsigned int index_d_xor = RANG_D_XOR1 + i;
      
    if ((state_defined_xor & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_xor);
    else _CLEAR_BIT(p_active_functions, index_d_xor);
  }
}
/*****************************************************/

/*****************************************************/
//Опрацювання визначуваних "НЕ"
/*****************************************************/
inline void d_not_handler(volatile unsigned int *p_active_functions)
{
  unsigned int state_defined_not = 0;

  //Визначаємо стан всіх визначуваних "НЕ" (не виставляючи поки що їх у робочому масиві)
  for (unsigned int i = 0; i < /*NUMBER_DEFINED_NOT*/current_settings_prt.number_defined_not; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 0] & p_active_functions[0]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 1] & p_active_functions[1]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 2] & p_active_functions[2]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 3] & p_active_functions[3]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 4] & p_active_functions[4]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 5] & p_active_functions[5]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 6] & p_active_functions[6]) == 0)
       )
    {
      state_defined_not |= (1 << i);
    }
  }

  //Установлюємо, або скидаємо визначувані "НЕ" у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив p_active_functions у якому ще не встановлені нові значення виходів В-"НЕ", тому що інші В-"НЕ"
  можуть бути джерелом , але джерелом може буте попереднє значення В-"НЕ", а не те,
  що зараз встановлюється. А оскілдьки ми встановлюємо значення у масиві
  p_active_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом встановлення/скидання)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
  {
    //Установлюємо, або скидаємо В-"НЕ"
    unsigned int index_d_not = RANG_D_NOT1 + i;
      
    if ((state_defined_not & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_not);
    else _CLEAR_BIT(p_active_functions, index_d_not);
  }
}
/*****************************************************/

/*****************************************************/
//Перевірка на необхідність завершення роботи аналогового/дискретного реєстраторів
/*****************************************************/
inline unsigned int stop_regisrator(volatile unsigned int* carrent_active_functions, unsigned int* ranguvannja_registrator)
{
  unsigned int stop = 0;

  {
    if (
        ((carrent_active_functions[0] & ranguvannja_registrator[0]) == 0) &&
        ((carrent_active_functions[1] & ranguvannja_registrator[1]) == 0) &&
        ((carrent_active_functions[2] & ranguvannja_registrator[2]) == 0) &&
        ((carrent_active_functions[3] & ranguvannja_registrator[3]) == 0) &&
        ((carrent_active_functions[4] & ranguvannja_registrator[4]) == 0) &&
        ((carrent_active_functions[5] & ranguvannja_registrator[5]) == 0) &&
        ((carrent_active_functions[6] & ranguvannja_registrator[6]) == 0)
      )
    {
      //Зафіксовано, що ні одне джерело активації реєстратора зараз не активне
      
      //Помічаємо, що реєстратор може бути зупиненим
      stop = 0xff;
    }
  }
  
  return stop;
}
/*****************************************************/

/*****************************************************/
//Зафіксована невизначена помилка роботи дискретного реєстратора
/*****************************************************/
void fix_undefined_error_dr(volatile unsigned int* carrent_active_functions)
{
  //Виставляємо помилку з записом в дисретний реєстратор
  _SET_BIT(set_diagnostyka, ERROR_DR_UNDEFINED_BIT);
  _SET_BIT(carrent_active_functions, RANG_DEFECT);
  //Переводимо режим роботи з реєстратором у сатн "На даний момент ніких дій з дискретним реєстратором не виконується" 
  state_dr_record = STATE_DR_NO_RECORD;
  //Скидаєсо сигнал роботи дискретного реєстратора
  _CLEAR_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);
}
/*****************************************************/

/*****************************************************/
//Подача команди почати запис у DataFalsh
/*****************************************************/
inline void command_start_saving_record_dr_into_dataflash(void)
{
  //У структурі по інформації стану реєстраторів виставляємо повідомлення, що почався запис і ще не закінчився
  _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);
  info_rejestrator_dr.saving_execution = 1;
        
  //Виставляємо першу частину запису
  part_writing_dr_into_dataflash = 0;
  //Виставляємо команду запису у мікросхему DataFlash
  control_tasks_dataflash |= TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR;
}
/*****************************************************/

/*****************************************************/
//Функція обробки черги зформованих записів дискретного реєстратора
/*****************************************************/
inline void routine_for_queue_dr(void)
{
  if(
     (state_dr_record == STATE_DR_MAKE_RECORD)            || /*Стоїть умова сформовані дані передати на запис у DataFlsh без повторного початку  нового запису, бо умова завершення запиу    досягнкта, а не стояла умова примусового завершення даного сформованого запису*/
     (state_dr_record == STATE_DR_CUT_RECORD)             || /*Стоїть умова сформовані дані передати на запис у DataFlsh   з повторним  початком нового запису, бо умова завершення запиу не досягнкта, а    стояла умова примусового завершення даного сформованого запису*/
     (number_records_dr_waiting_for_saving_operation != 0)  
    )
  {
    if ((control_tasks_dataflash & TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR) == 0)
    {
      //На даний момент запису у Datafalsh не проводиться
      unsigned char *buffer_source, *buffer_target;
        
      if (number_records_dr_waiting_for_saving_operation == 0)
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++)
        {
          *(buffer_target + i) = *(buffer_source + i);
          *(buffer_source + i) = 0xff;
        }
        number_records_dr_waiting_for_saving_operation = 0;
      }
      else if (number_records_dr_waiting_for_saving_operation == 1)
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record_level_1;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target +i ) = *(buffer_source + i);
        
        if((state_dr_record == STATE_DR_MAKE_RECORD) || (state_dr_record == STATE_DR_CUT_RECORD))
        {
          buffer_target = buffer_for_save_dr_record_level_1;
          buffer_source = buffer_for_save_dr_record;
          for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
          {
            *(buffer_target + i) = *(buffer_source + i);
            *(buffer_source + i) = 0xff;
          }
          number_records_dr_waiting_for_saving_operation = 1;
        }
        else number_records_dr_waiting_for_saving_operation = 0;
      }
      else
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record_level_1;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target + i) = *(buffer_source + i);
        buffer_target = buffer_for_save_dr_record_level_1;
        buffer_source = buffer_for_save_dr_record;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
        {
          *(buffer_target + i) = *(buffer_source + i);
          *(buffer_source + i) = 0xff;
        }
        number_records_dr_waiting_for_saving_operation = 1;
      }
        
      //Подаємо команду почати запис у DataFalsh
      command_start_saving_record_dr_into_dataflash();
    }
    else
    {
      //На даний момент запису у Datafalsh проводиться
      //Треба наш теперішній запис поставити у чергу
      if (number_records_dr_waiting_for_saving_operation == 0)
      {
        //На даний момент крім того, буфера - з якого іде безпосередній запис у DataFalsh, більше ніяких записів у черзі немає
        //Переміщаємо текучий запис у буфер buffer_for_save_dr_record_level_1
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
        {
          buffer_for_save_dr_record_level_1[i] = buffer_for_save_dr_record[i];
          buffer_for_save_dr_record[i] = 0xff;
        }
    
        //Помічаємо, що один запис очікує передау його на безпосередній запис у dataFalsh
        number_records_dr_waiting_for_saving_operation = 1;
      }
      else if (number_records_dr_waiting_for_saving_operation >= 1)
      {
         if((state_dr_record == STATE_DR_MAKE_RECORD) || (state_dr_record == STATE_DR_CUT_RECORD))
         {
          //На даний момент крім того, буфера - з якого іде безпосередній запис у DataFalsh, ще один сформований запис стоїть у буфері buffer_for_save_dr_record_level_1
          /*
          Тому даний запис залишаємо у цьому самому буфері buffer_for_save_dr_record, але збільшуємо кількість записів. які стоять у черзі
          і якщо буде спроба почати новий запис, то будемо фіксувати помилку втрати даних
          */
          number_records_dr_waiting_for_saving_operation = 2;
         }
      }
    }
    
    if (state_dr_record == STATE_DR_MAKE_RECORD)
    {
      //Помічаємо, що ми готові приймати наступний запис
      state_dr_record = STATE_DR_NO_RECORD;
    }
    else if (state_dr_record == STATE_DR_CUT_RECORD)
    {
      //Помічаємо, що треба примусово запустити новий запис
      state_dr_record = STATE_DR_FORCE_START_NEW_RECORD;
    }
      
  }
}
/*****************************************************/

/*****************************************************/
//Зафіксована невизначена помилка роботи аналогового реєстратора
/*****************************************************/
void fix_undefined_error_ar(volatile unsigned int* carrent_active_functions)
{
  //Виставляємо помилку з записом в дисретний реєстратор
  _SET_BIT(set_diagnostyka, ERROR_AR_UNDEFINED_BIT);
  _SET_BIT(carrent_active_functions, RANG_DEFECT);
  //Переводимо режим роботи з реєстратором у сатн "На даний момент ніких дій з дискретним реєстратором не виконується" 
  continue_previous_record_ar = 0; /*помічаємо, що ми не чикаємо деактивації всіх джерел активації аналогового реєстратора*/
  state_ar_record = STATE_AR_NO_RECORD;
  //Скидаєсо сигнал роботи аналогового реєстратора
  _CLEAR_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR);

  //Виставляємо команду запису структуру для аналогового реєстратора у EEPROM
  _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
  //Відновлюємо інформаційну структуру для аналогового реєстратора
  /*
  Адресу залишаємо попередню, тобто така яка і була
  */
  info_rejestrator_ar.saving_execution = 0;
  /*
  оскільки скоріше всього якась частна запису відбулася, а це значить, що, якщо там були корисні дані
  якогось запису, то вони зіпсовані. Тому треба помітити, що якщо у аналоговому реєстраторі до цього часу була
  максимально можлива кількість записів, то зараз оснанній з них є зіпсований, тобто кількість записів стала 
  у такому випадку на одиницю менша
  */
  unsigned int max_number_records_ar_tmp = max_number_records_ar;
  if (info_rejestrator_ar.number_records >= max_number_records_ar_tmp) 
    info_rejestrator_ar.number_records = max_number_records_ar_tmp - 1; /*Умова мал аб бути ==, але щоб перестахуватися на невизначену помилку я поставив >=*/
}
/*****************************************************/

/*****************************************************/
//Функція обробки логіки дискретного реєстратора
/*****************************************************/
inline void analog_registrator(volatile unsigned int* carrent_active_functions)
{
  static unsigned int unsaved_bytes_of_header_ar;

  //Попередньо скидаємо невизначену помилку  роботи аналогового реєстратора
  _SET_BIT(clear_diagnostyka, ERROR_AR_UNDEFINED_BIT);

  if (continue_previous_record_ar != 0)
  {
    /*
    Ця ситуація означає, що були активними джерела аналогового реєстратора, які запустили
    в роботу аналоговий реєстратор, і тепер для розблокування можливості запускати новий запис ми 
    чекаємо ситуації, що всі джерела активації деактивуються (у будь-який час чи до
    завершення записування текучого запису аналогового реєстратора, чи вже після завершення
    записування. Це буде умовою розблокування можливості запису нового запису)
    */
    if(
       ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) == 0) &&
       ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) == 0) &&
       ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) == 0) &&
       ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) == 0) &&
       ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) == 0) &&
       ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) == 0) &&
       ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) == 0)
      ) 
    {
      //Умова розблокування можливості початку нового запису виконана
      continue_previous_record_ar = 0;
    }
  }

  switch (state_ar_record)
  {
  case STATE_AR_NO_RECORD:
    {
      if(semaphore_read_state_ar_record == 0)
      {
        /*
        Можливо була ситуація, що при попередній роботі модуля аналогового реєстратора відбувалося блокування роботи аналоговго реєстратора
        Знятий семафор semaphore_read_state_ar_record при умові, що стан роботи аналогового реєстратора STATE_AR_NO_RECORD означає,
        що зараз немає перешкод на його запуск, тому знімаємо теоретично можливу подію про тимчасову неготовність роботи аналогового реєстратора
        */
        _SET_BIT(clear_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
      }

      //Аналізуємо, чи стоїть умова запуску аналогового реєстратора
      if (
          (
           ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
           ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
           ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
           ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
           ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
           ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0) ||
           ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) != 0)
          )
          &&  
          (continue_previous_record_ar == 0) /*при попередній роботі ан.реєстротора (якщо така була) вже всі джерела активації були зняті і зароз вони знову виникли*/ 
         )
      {
        //Перевіряємо, чи при початку нового запису у нас не іде спроба переналаштвати аналоговий реєстратор
        if(semaphore_read_state_ar_record == 0)
        {
          //Є умова запуску аналогового реєстратора
          continue_previous_record_ar = 0xff; /*помічаємо будь-яким числом, що активувалися дзжерела ан.реєстратора, які запустили роботц аналогового реєстратора*/
    
          //Можна починати новий запис
          
          //Записуємо мітку початку запису
          header_ar.label_start_record = LABEL_START_RECORD_AR;
          //Записуємо час початку запису
          unsigned char *label_to_time_array;
          if (copying_time == 0) label_to_time_array = time;
          else label_to_time_array = time_copy;
          for(unsigned int i = 0; i < 7; i++) header_ar.time[i] = *(label_to_time_array + i);
          //І'мя ячейки
          for(unsigned int i=0; i<MAX_CHAR_IN_NAME_OF_CELL; i++)
            header_ar.name_of_cell[i] = current_settings_prt.name_of_cell[i] & 0xff;
          
          //Помічаємо, що ще ми ще не "відбирали" миттєві значення з масив для аналогового реєстратора
          copied_number_samples = 0;
          //Визначаємо загальну кількість миттєвих значень, які мають бути записані у мікросхему dataFlash2
          total_number_samples = ((current_settings_prt.prefault_number_periods + current_settings_prt.postfault_number_periods) << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar);

          //Визначаємо,що покищо заготовок аналогового реєстратора не скопійоманий у масив звідки будуть дані забирватися вже для запису у DataFlash
          unsaved_bytes_of_header_ar = sizeof(__HEADER_AR);

          //Визначаємо з якої адреси записувати
          temporary_address_ar = info_rejestrator_ar.next_address;

          //Визначаєом, що поки що немає підготовлених даних для запису
          count_to_save = 0;
          //Виставляємо будь-яким ненульовим числом дозвіл на підготовку нових даних для запису
          permit_copy_new_data = 0xff;

          //Робим спробу перекопіювати хоч частину заголовку аналогового реєстраторра і підготовлених даних у масив для запису в DataFlash
          if (making_buffer_for_save_ar_record(&unsaved_bytes_of_header_ar) != 0)
          {
            //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
            fix_undefined_error_ar(carrent_active_functions);
          }
          else
          {
            //Переводимо режим роботи із аналоговим реєстратором у стан "Запус нового запису"
            state_ar_record = STATE_AR_START;
            //Виставляємо активну функцію
            _SET_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR);

            //У структурі по інформації стану реєстраторів виставляємо повідомлення, що почався запис і ще не закінчився
            _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
            info_rejestrator_ar.saving_execution = 1;
          }
        }
        else
        {
          //Виставляємо помилку, що тимчасово аналоговий реєстратор є занятий (черз те, що іде намаганні змінити часові витримки)
          _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
          _SET_BIT(carrent_active_functions, RANG_DEFECT);
        }
      }
      break;
    }
  case STATE_AR_START:
    {
      //Ніяких дій не виконуємо, поки не встанвиться режим STATE_AR_SAVE_SRAM_AND_SAVE_FLASH,  або STATE_AR_ONLY_SAVE_FLASH
      break;
    }
  case STATE_AR_SAVE_SRAM_AND_SAVE_FLASH:
  case STATE_AR_ONLY_SAVE_FLASH:
    {
      if (state_ar_record == STATE_AR_ONLY_SAVE_FLASH)
      {
        /*
        Весь післяаварійний масив підготовлений до запису
        */
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR) != 0)
        {
          //Знімаємо сигнал роботи аналогового реєстратора
          _CLEAR_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR);
        }
        
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR) == 0)
        {
          /*
          Враховуємо також той момент, коли сигнал запуску роботи аналогового реєсстратора був знятий
          */
          if  (continue_previous_record_ar == 0)
          {
            /*
            Перевіряємо, чи немає умови запуску нового заппису до моменту, 
            поки ще старий запис не закінчився повністю
            */
            if (
                ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
                ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
                ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
                ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
                ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
                ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0) ||
                ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) != 0)
               ) 
            {
              //Виставляємо помилку, що тимчасово аналоговий реєстратор є занятий (черз те, що завершується попередній запис)
              _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
              _SET_BIT(carrent_active_functions, RANG_DEFECT);
            }
          }
        }
      }
      
      if (permit_copy_new_data != 0)
      {
        /*
        Робим спробу перекопіювати хоч частину заголовку аналогового реєстраторра 
        і підготовлених даних у масив для запису в DataFlash тільки тоді, коли є дозвіл
        на цю операцію
        */
        if (making_buffer_for_save_ar_record(&unsaved_bytes_of_header_ar) != 0)
        {
          //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
          fix_undefined_error_ar(carrent_active_functions);
        }
      }
      else
      {
        if (
            (copied_number_samples == total_number_samples) &&
            (count_to_save == 0                           ) && 
            (
             (control_tasks_dataflash &
              (
               TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR | 
               TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR
              )
             ) == 0
            )   
           )
        {
          //Умова зупинки роботи анаалогового реєстратора
          unsigned int index_array_ar_heat_tmp = index_array_ar_heat;/*це робим для того, бо компілятор видає завуваження при порівнянні змінних з префіксом volatile*/
          unsigned int index_array_ar_tail_tmp = index_array_ar_tail;/*це робим для того, бо компілятор видає завуваження при порівнянні змінних з префіксом volatile*/
          if(
             (index_array_ar_tail_tmp == index_array_ar_heat_tmp) &&
             (state_ar_record == STATE_AR_ONLY_SAVE_FLASH)  
            )  
          {
            //Коректна умова зупинки роботи аналогового реєстратора
            state_ar_record = STATE_AR_NO_RECORD;

            //Виставляємо команду запису структури аналогового реєстратора у EEPROM
            _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
            //Визначаємо нову адресу наступного запису, нову кількість записів і знімаємо сигналізацію, що зараз іде запис
            if ((temporary_address_ar + size_one_ar_record) > (NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2))
              temporary_address_ar = 0; 
            info_rejestrator_ar.next_address = temporary_address_ar;
            info_rejestrator_ar.saving_execution = 0;
            unsigned int max_number_records_ar_tmp = max_number_records_ar;
            if (info_rejestrator_ar.number_records < max_number_records_ar_tmp) info_rejestrator_ar.number_records += 1;
            else info_rejestrator_ar.number_records = max_number_records_ar_tmp;
          }
          else
          {
            /*В процесі роботи аналогового реєстратора відбувся збій, який привів
            до непередбачуваного завершення роботи аналогового реєстратора
            
            Це скоріше всього виникло внаслідок того, що ми досягнули передчасно
            максимальної кількості зкопійованих миттєвих значень
            */
            fix_undefined_error_ar(carrent_active_functions);
          }
        }
        else
        {
          //Треба подати команду на запис підготовлених даних
          if (
              (count_to_save != 0 ) 
              && 
              (
               (control_tasks_dataflash &
                (
                 TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR | 
                 TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR
                )
               ) == 0
              )   
             )
          {
            /*
            Подаємо команду на запис нових даних тільки тоді коли не іде зараз запис
            попередньо підготованих даних і коли є нові дані для запису
            */
            
            if (((temporary_address_ar & 0x1ff) + count_to_save) <= SIZE_PAGE_DATAFLASH_2)
            {
              //Немає помилки при фомауванні кількості байт для запису (в одну сторінку дані поміщаються з текучої адреси)
              
              if (count_to_save == SIZE_PAGE_DATAFLASH_2) control_tasks_dataflash |= TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR;
              else control_tasks_dataflash |= TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR;
            }
            else
            {
              //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
              fix_undefined_error_ar(carrent_active_functions);
            }
          }
        }

      }
      break;
    }
  case STATE_AR_TEMPORARY_BLOCK:
    {
      //На даний момент певні внутрішні операції блокують роботу аналогового реєстратрора
      //Аналізуємо, чи стоїть умова запуску аналогового реєстратора
      if (
          ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
          ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
          ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
          ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
          ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
          ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0) ||
          ((carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6]) != 0)
         )
      {
        //Виставляємо помилку, що тимчасово аналоговий реєстратор є занятий
        _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
        _SET_BIT(carrent_active_functions, RANG_DEFECT);
      }
      break;
    }
  default:
    {
      //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
      fix_undefined_error_ar(carrent_active_functions);
      break;
    }
  }
}
/*****************************************************/


/*****************************************************/
//Функція захистів з якої здійснюються всі інші операції
/*****************************************************/
inline void main_protection(void)
{
  copying_active_functions = 1; //Помічаємо, що зараз обновляємо значення активних функцій
  
  //Скижаємо ті сигнали, які відповідають за входи, фкнопки і активацію з інтерфейсу
  const unsigned int maska_input_signals[N_BIG] = 
  {
    MASKA_FOR_INPUT_SIGNALS_0, 
    MASKA_FOR_INPUT_SIGNALS_1, 
    MASKA_FOR_INPUT_SIGNALS_2, 
    MASKA_FOR_INPUT_SIGNALS_3, 
    MASKA_FOR_INPUT_SIGNALS_4, 
    MASKA_FOR_INPUT_SIGNALS_5, 
    MASKA_FOR_INPUT_SIGNALS_6 
  };
  for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_input_signals[i]);
  
  /**************************/
  //Перевірка, чи треба очистити трігерні функції
  /**************************/
  if (reset_trigger_function_from_interface !=0)
  {
    if ((reset_trigger_function_from_interface & (1 << USB_RECUEST)) != 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++) trigger_functions_USB[i] = 0;
    }
    if ((reset_trigger_function_from_interface & (1 << RS485_RECUEST)) != 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++) trigger_functions_RS485[i] = 0;
    }
    
    //Помічаємо що ми виконали очистку по ВСІХ інтерфейсах
    reset_trigger_function_from_interface = 0;
  }
  /**************************/

  /**************************/
  //Опрацьовуємо натиснуті кнопки - Мають опрацьовуватися найпершими, бо тут іде аналіз чи активовується опреділювані функції з кнопок
  /**************************/
  if ((pressed_buttons !=0) || (activation_function_from_interface != 0))
  {
    unsigned int temp_value_for_activated_function = 0;
    
    //Активація з кнопуки
    if (pressed_buttons != 0)
    {
//      for (unsigned int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
//      {
//        if ((pressed_buttons & (1 << i)) != 0)
//          temp_value_for_activated_function |= current_settings_prt.ranguvannja_buttons[i];
//      }

      //Очищаємо натиснуті кнопка, які ми вже опрацювали
      pressed_buttons =0;
    }
    
    //Активація з інтерфейсу
    if (activation_function_from_interface != 0)
    {
      temp_value_for_activated_function |= activation_function_from_interface;
      
      //Очищаємо помітку активації функцій з інетфейсу, які ми вже опрацювали
      activation_function_from_interface = 0;
    }
    
    //Якщо  функції активовувалися через кнопки то переносимо їх у тимчасовий масив функцій, які мають бути зараз активавані
    if(temp_value_for_activated_function != 0) 
    {
      //Скидання світлодіодів і реле
      if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_TU_SILENCE)) 
        _SET_BIT(active_functions, RANG_SILENCE);
      if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_TU_RESET)) 
        _SET_BIT(active_functions, RANG_RESET);
      if (_GET_OUTPUT_STATE(temp_value_for_activated_function, RANG_TU_TEST)) 
        _SET_BIT(active_functions, RANG_TEST);
    }
  }
  /**************************/

  /**************************/
  //Опрацьовуємо дискретні входи
  /**************************/
  //Перевіряємо чи є зараз активні входи
  if (state_inputs !=0)
  {
    for (unsigned int i = 0; i < NUMBER_INPUTS; i++)
    {
      if ((state_inputs & (1 << i)) != 0) _SET_BIT(active_functions, (RANG_DI1 + i));
    }
  }
  /**************************/

  /**************************/
  //Виконуємо фільтрацію переднього фронту для тих сигналів, які мають активуватися тільки по передньому фронтові
  /**************************/
  {
    static unsigned int previous_activating_functions[N_BIG];
    //Формуємо маску сигналів, які треба позначити, як активні тільки в момент переходу з "0" в "1"
    unsigned int temp_maska_filter_function[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
    unsigned int temp_activating_functions[N_BIG] = {0, 0, 0, 0, 0, 0, 0};
  
    //Сигнал "Тиша"
    _SET_BIT(temp_maska_filter_function, RANG_SILENCE);
  
    //Сигнал "Скидання"
    _SET_BIT(temp_maska_filter_function, RANG_RESET);

    //Сигнал "Тест"
    _SET_BIT(temp_maska_filter_function, RANG_TEST);

    for (unsigned int i = 0; i < N_BIG; i++)
    {
      //З масиву попередніх станів виділяємо тільки ті функції, якиї нас цікавить фронт змін і поміщаємо їх у тимчасовий масив
      temp_activating_functions[i] = previous_activating_functions[i] & temp_maska_filter_function[i];
  
      //У тимчасовому масиві виділяємо тільки ті функції, у яких зафіксовано або передній, або задній фронти
      temp_activating_functions[i] ^= (active_functions[i] & temp_maska_filter_function[i]);
  
      //Тепер виділяємо у тимчасовому масиві тільки ті функції у яких зараз значення стоять рівні "1" (тобто відбувся перехід з "0" в "1")
      temp_activating_functions[i] &= active_functions[i];

      /*
      Перед тим, як виділити ті функції, які у цьому циклі будуть відмічені як активні 
      з урахуванням того, що деякі функції активоються по передньому фронті
      копіюємо статичний стан функцій (без врахування фронтів) у тимчасовий масив
      щоб при наступному аналізі мати попередній статичний стан активних функцій
      */ 
      previous_activating_functions[i] = active_functions[i];

      //Обновляємо масив функцій, які зараз активуються з врахуванням того, що серед виділених функцій маскою активними мають юути тільки ті, у яких перехід був з "0" в "1"
      active_functions[i] = (active_functions[i] & (~temp_maska_filter_function[i])) | temp_activating_functions[i];
    }
  }
  /**************************/

  /**************************/
  //Сигнал меандру
  /**************************/
  if (output_timer_meander) _SET_BIT(active_functions, RANG_MEANDER);
  /**************************/
  
  /***********************************************************/
  //Розрахунок вимірювань
  /***********************************************************/
  calc_measurement();

      
  //Діагностика справності раз на період
  diagnostyca_adc_execution();
  
  //Копіюємо вимірювання для низькопріоритетних і високопріоритетних завдань
  unsigned int bank_measurement_high_tmp = (bank_measurement_high ^ 0x1) & 0x1;
  if(semaphore_measure_values_low1 == 0)
  {
    for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement_middle[i] = measurement[i];
    }
  }
  else
  {
    for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement[i];
    }
  }
  bank_measurement_high = bank_measurement_high_tmp;
  /***********************************************************/
  
  
  /**************************/
  //Сигнал "Несправность Общая"
  /**************************/
  unsigned int diagnostyka_tmp[3];
  diagnostyka_tmp[0] = diagnostyka[0];
  diagnostyka_tmp[1] = diagnostyka[1];
  diagnostyka_tmp[2] = diagnostyka[2];

  diagnostyka_tmp[0] &= (unsigned int)(~clear_diagnostyka[0]); 
  diagnostyka_tmp[0] |= set_diagnostyka[0]; 

  diagnostyka_tmp[1] &= (unsigned int)(~clear_diagnostyka[1]); 
  diagnostyka_tmp[1] |= set_diagnostyka[1]; 

  diagnostyka_tmp[2] &= (unsigned int)(~clear_diagnostyka[2]); 
  diagnostyka_tmp[2] |= set_diagnostyka[2]; 
  
  diagnostyka_tmp[2] &= USED_BITS_IN_LAST_INDEX; 

  _CLEAR_BIT(diagnostyka_tmp, EVENT_START_SYSTEM_BIT);
  _CLEAR_BIT(diagnostyka_tmp, EVENT_DROP_POWER_BIT);
  if (
      (diagnostyka_tmp[0] != 0) ||
      (diagnostyka_tmp[1] != 0) ||
      (diagnostyka_tmp[2] != 0)
     )   
  {
    _SET_BIT(active_functions, RANG_DEFECT);
  }
  else
  {
    _CLEAR_BIT(active_functions, RANG_DEFECT);
  }
  /**************************/

  /**************************/
  //Сигнал "Несправность Аварийная"
  /**************************/
  if (
      ((diagnostyka[0] & MASKA_AVAR_ERROR_0) != 0) ||
      ((diagnostyka[1] & MASKA_AVAR_ERROR_1) != 0) ||
      ((diagnostyka[2] & MASKA_AVAR_ERROR_2) != 0)
     )   
  {
    _SET_BIT(active_functions, RANG_AVAR_DEFECT);
  }
  else
  {
    _CLEAR_BIT(active_functions, RANG_AVAR_DEFECT);
  }
  /**************************/
  
  //Логічні схеми мають працювати тільки у тому випадку, якщо немє сигналу "Аварийная неисправность"
  if (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) == 0)
  {
    //Аварійна ситуація не зафіксована

    /**************************/
    //"Перевірка фазування"
    /**************************/
    if ((current_settings_prt.configuration & (1 << CTRL_PHASE_BIT_CONFIGURATION)) != 0) 
    {
    } 
    else 
    {
      //Очищуємо сигнали, які не можуть бути у даній конфігурації
      const unsigned int maska_ctrl_phase_signals[N_BIG] = 
      {
        MASKA_CTRL_PHASE_SIGNALS_0, 
        MASKA_CTRL_PHASE_SIGNALS_1, 
        MASKA_CTRL_PHASE_SIGNALS_2,
        MASKA_CTRL_PHASE_SIGNALS_3, 
        MASKA_CTRL_PHASE_SIGNALS_4, 
        MASKA_CTRL_PHASE_SIGNALS_5, 
        MASKA_CTRL_PHASE_SIGNALS_6
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_ctrl_phase_signals[i]);
      
      global_timers[INDEX_TIMER_CTRL_PHASE_U] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_U_D] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_PHI] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_PHI_D] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_F] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_F_D] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_TMP1_100MS] = -1;
      global_timers[INDEX_TIMER_CTRL_PHASE_TMP2_100MS] = -1;
    }
    /**************************/
    
    /**************************/
    //Розширена логіка
    /**************************/
    unsigned int active_functions_tmp[NUMBER_ITERATION_EL_MAX][N_BIG];
    unsigned int iteration = 0;
	unsigned int repeat_state = false;
//    unsigned int df_changed_state_with_start_new_timeout = 0;
    do
    {
      for (unsigned int i = 0; i < iteration; i++)
      {
        if (
            (active_functions_tmp[i][0] == active_functions[0]) &&
            (active_functions_tmp[i][1] == active_functions[1]) &&
            (active_functions_tmp[i][2] == active_functions[2]) &&
            (active_functions_tmp[i][3] == active_functions[3]) &&
            (active_functions_tmp[i][4] == active_functions[4]) &&
            (active_functions_tmp[i][5] == active_functions[5]) &&
            (active_functions_tmp[i][6] == active_functions[6])
           )
        {
          repeat_state = true;
          break;
        }
      }
      if (repeat_state != false ) break;
        
      active_functions_tmp[iteration][0] = active_functions[0];
      active_functions_tmp[iteration][1] = active_functions[1];
      active_functions_tmp[iteration][2] = active_functions[2];
      active_functions_tmp[iteration][3] = active_functions[3];
      active_functions_tmp[iteration][4] = active_functions[4];
      active_functions_tmp[iteration][5] = active_functions[5];
      active_functions_tmp[iteration][6] = active_functions[6];

      d_and_handler(active_functions);
      d_or_handler(active_functions);
      d_xor_handler(active_functions);
      d_not_handler(active_functions);
        
      iteration++;
    }
    while (
           (iteration < current_settings_prt.number_iteration_el)
           &&
           (
            (active_functions_tmp[iteration - 1][0] != active_functions[0]) ||
            (active_functions_tmp[iteration - 1][1] != active_functions[1]) ||
            (active_functions_tmp[iteration - 1][2] != active_functions[2]) ||
            (active_functions_tmp[iteration - 1][3] != active_functions[3]) ||
            (active_functions_tmp[iteration - 1][4] != active_functions[4]) ||
            (active_functions_tmp[iteration - 1][5] != active_functions[5]) ||
            (active_functions_tmp[iteration - 1][6] != active_functions[6])
           ) 
          );
      
    if (
        (repeat_state != false ) ||
        (iteration >= current_settings_prt.number_iteration_el)
       )
    {
      _SET_BIT(active_functions, RANG_ERROR_CONF_EL);
    }
    else
    {
      _CLEAR_BIT(active_functions, RANG_ERROR_CONF_EL);
    }
    /**************************/
  }
  else
  {
    //Аварійна ситуація зафіксована
    
    //Скидаємо всі активні функції, крім інформативних
    active_functions[0] &= MASKA_INFO_SIGNALES_0;
    active_functions[1] &= MASKA_INFO_SIGNALES_1;
    active_functions[2] &= MASKA_INFO_SIGNALES_2;
    active_functions[3] &= MASKA_INFO_SIGNALES_3;
    active_functions[4] &= MASKA_INFO_SIGNALES_4;
    active_functions[5] &= MASKA_INFO_SIGNALES_5;
    active_functions[6] &= MASKA_INFO_SIGNALES_6;
    
    //Деактивовуємо всі реле
    state_outputs = 0;
    
    //Скидаємо всі таймери, які присутні у лозіці
    for(unsigned int i = INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START; i < MAX_NUMBER_GLOBAL_TIMERS; i++)
      global_timers[i] = -1;
    
    //Стан виконання ОФ переводимо у початковий
    for(unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      etap_execution_df[i] = NONE_DF;
    }
  }

  /**************************/
  //Обробка аналогового реєстратора
  /**************************/
  analog_registrator(active_functions);
  /**************************/

  /**************************/
  //Робота з функціями, які мають записуватися у енергонезалежну пам'ять
  /**************************/
  const unsigned int maska_trg_func_array[N_BIG] = {MASKA_TRIGGER_SIGNALES_0, MASKA_TRIGGER_SIGNALES_1, MASKA_TRIGGER_SIGNALES_2, MASKA_TRIGGER_SIGNALES_3, MASKA_TRIGGER_SIGNALES_4, MASKA_TRIGGER_SIGNALES_5, MASKA_TRIGGER_SIGNALES_6};
  unsigned int comparison_true = true;
  for (unsigned int i = 0; i < N_BIG; i++)
  {
    unsigned int tmp_data;
    if (trigger_active_functions[i] != (tmp_data = (active_functions[i] & maska_trg_func_array[i])))
    {
      comparison_true = false;
      trigger_active_functions[i] = tmp_data;
    }
  }
  if (comparison_true != true)
  {
    /*
    Сигнали, значення яких записується у енергонезалежну пам'1ять змінилися.
    Подаємо команду на їх запис у енергонезалежну пам'ять
    */
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
  }
  /**************************/

  /**************************/
  //Перекидання інфомації у масиви активних і тригерних функцій
  /**************************/
  for (unsigned int i = 0; i < N_BIG; i++)
  {
    unsigned int temp_data = active_functions[i];
    trigger_functions_USB[i]   |= temp_data;
    trigger_functions_RS485[i] |= temp_data;
  }

  copying_active_functions = 0; //Помічаємо, що обновлення значення активних функцій завершене
  
  /*
  Робимо копію значення активних функцій для того, щоб коли ці знаення будуть
  обновлятися, то можна було б іншим модулям  (запис у об'єднаний аналоговий
  реєстратор) взяти попереднє, але достовірне значення
  */
  for (unsigned int i = 0; i < N_BIG; i++) active_functions_copy[i] = active_functions[i];
  /**************************/

  /**************************/
  //Вивід інформації на виходи
  /**************************/
  
  if (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) == 0)
  {
    //Не зафіксовано аварійної ситуації, тому встановлювати реле можна
    
    //Визначаємо, які реле зараз мають бути замкнутими
    for (unsigned int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      //У тимчасовий масив поміщаємо ЛОГІЧНЕ І ранжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
      unsigned int temp_array_of_outputs[N_BIG];
    
      for (unsigned int j = 0; j < N_BIG; j++) temp_array_of_outputs[j] = current_settings_prt.ranguvannja_outputs[N_BIG*i + j] & active_functions[j];

      //Сигнал "Аварійна несправність" працює у інверсному режимі: замикає реле на якому зранжована у випадку, коли даний сигнал не активинй
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_AVAR_DEFECT) !=0)
      {
        //Сигнал "Aварийная неисправность"  справді зранжовано на даний вихід
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT) == 0)
        {
          //Сигнал "Aварийная неисправность" не є активним
          //Приимусово встановлюємо його у активний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _SET_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT);
        }
        else
        {
          //Сигнал "Aварийная неисправность" є активним
          //Приимусово переводимо його у пасивний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _CLEAR_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT);
        }
      }
      
      //Сигнал "Загальна несправність" працює у інверсному режимі: замикає реле на якому зранжована у випадку, коли даний сигнал не активинй
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_DEFECT) !=0)
      {
        //Сигнал "Загальна несправність"  справді зранжовано на даний вихід
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_DEFECT) == 0)
        {
          //Сигнал "Загальна несправність" не є активним
          //Приимусово встановлюємо його у активний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _SET_BIT(temp_array_of_outputs, RANG_DEFECT);
        }
        else
        {
          //Сигнал "Загальна несправність" є активним
          //Приимусово переводимо його у пасивний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _CLEAR_BIT(temp_array_of_outputs, RANG_DEFECT);
        }
      }

      //Перевіряємо, чи є співпадіння між ранжованими функціями на цьому виході і функціями, які зараз є активними - умова активації виходу
      if (
          (temp_array_of_outputs[0] !=0 ) ||
          (temp_array_of_outputs[1] != 0) ||
          (temp_array_of_outputs[2] != 0) ||
          (temp_array_of_outputs[3] != 0) ||
          (temp_array_of_outputs[4] != 0) ||
          (temp_array_of_outputs[5] != 0) ||
          (temp_array_of_outputs[6] != 0)
         )
      {
        //Відмічаємо, що даний вихід - ЗАМКНУТИЙ
        state_outputs |= (1 << i);
      }
      else
      {
        //Відмічаємо, що даний вихід - РОЗІМКНУТИЙ
        state_outputs &= ~(1 << i);
      }
    }
  }
  else
  {
    //Зафіксовано аварійнe ситуацію, тому деактивуємо всі реле!!!

    //Деактивовуємо всі реле
    state_outputs = 0;
  }
  
  //Виводимо інформацію по виходах на піни процесора (у зворотньому порядку)
  unsigned int temp_state_outputs = 0;
  for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
  {
    if ((state_outputs & (1 << index)) != 0)
    {
      if (index < NUMBER_OUTPUTS_1)
        temp_state_outputs |= 1 << (NUMBER_OUTPUTS_1 - index - 1);
      else
        temp_state_outputs |= 1 << index;
    }
  }
  unsigned int temp_state_outputs_1 =  temp_state_outputs                      & ((1 << NUMBER_OUTPUTS_1) - 1);
  unsigned int temp_state_outputs_2 = (temp_state_outputs >> NUMBER_OUTPUTS_1) & ((1 << NUMBER_OUTPUTS_2) - 1);
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_1) = temp_state_outputs_1;
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_2) = temp_state_outputs_2;
  /**************************/

  /**************************/
  //Вивід інформації на світлодіоди
  /**************************/
  //Спочатку перевіряємо, чи не активовувалвся команда "Сблос индикации" - і якщо так, то попередньо скидаємо всю індикацію
  
  //Визначаємо, які світлоіндикатори зараз мають бути активними
  for (unsigned int i = 0; i < NUMBER_LEDS; i++)
  {
    //У тимчасовий масив копіюємо ранжування світлоіндикатора, який індексується інедексом "i"
    unsigned int temp_array_of_leds[N_BIG];
    
    //Перевіряємо, чи є співпадіння між ранжованими функціями на цьому світлоіндикаторі і функціями, які зараз є активними - умова активації виходу
    for (unsigned int j = 0; j < N_BIG; j++ ) temp_array_of_leds[j] = current_settings_prt.ranguvannja_leds[N_BIG*i + j] & active_functions[j];

    if (
        (temp_array_of_leds[0] != 0) ||
        (temp_array_of_leds[1] != 0) ||
        (temp_array_of_leds[2] != 0) ||
        (temp_array_of_leds[3] != 0) ||
        (temp_array_of_leds[4] != 0) ||
        (temp_array_of_leds[5] != 0) ||
        (temp_array_of_leds[6] != 0)
       )
    {
      //Відмічаємо, що даний світлоіндикатор - ГОРИТЬ
      state_leds |= (1 << i);
    }
    else
    {
      //Відмічаємо, що даний світлоіндикатор - ПОГАШЕНИЙ
      state_leds &= ~(1 << i);
    }
  }
  //Виводимо інформацію по світлоіндикаторах на світлодіоди
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_LEDS) = state_leds;
  /**************************/

  /**************************/
  //
  /**************************/
  /**************************/
}
/*****************************************************/

/*****************************************************/
//Переривання від таймеру TIM2, який обслуговує систему захистів
/*****************************************************/
void TIM2_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    /***********************************************************************************************/
    //Переривання відбулося вік каналу 1, який генерує переривання кожні 1 мс, для опраціьовування таймерів і систем захистів
    /***********************************************************************************************/
    TIM2->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff);
    uint32_t current_tick = TIM2->CCR1;
    
    /***********************************************************/
    //Перевіряємо, чи відбувалися зміни настройок
    /***********************************************************/
    if (
        (changed_settings == CHANGED_ETAP_ENDED) && /*Це є умова, що нові дані підготовлені для передачі їх у роботу системою захистів (і при цьому зараз дані не змінюються)*/
        (state_ar_record  != STATE_AR_START    )    /*Це є умова, що на даний момент не може виникнути переривання від вимірювальної системи (з вищим пріоритетом за пріоритет системи захистів) з умовою початку формування запису аналогового реєстратора. де треба буде взяти ширину доаварійного і післяаварійного масивів*/ 
       )   
    {
      //Копіюємо таблицю настройок у копію цієї таблиці але з якою працює (читає і змінює) тільки система захистів
      current_settings_prt = current_settings;
      
      //Помічаємо, що зміни прийняті системою захистів
      changed_settings = CHANGED_ETAP_NONE;
    }
    /***********************************************************/

    /***********************************************************/
    //Перевіряємо необхідність очистки аналогового і дискретного реєстраторів
    /***********************************************************/
    //Аналоговий реєстратор
    if (
        ((clean_rejestrators & CLEAN_AR) != 0 )
        &&  
        (state_ar_record == STATE_AR_NO_RECORD)
        &&  
        (
         (control_tasks_dataflash & (
                                     TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR |
                                     TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR      |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB                         |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485                       |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU
                                    )
         ) == 0
        )   
       )
    {
      //Виставлено каманда очистити аналогового реєстратора

      //Виставляємо команду запису цієї структури у EEPROM
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
    
      //Очищаємо структуру інформації по дискретному реєстраторі
      info_rejestrator_ar.next_address = MIN_ADDRESS_AR_AREA;
      info_rejestrator_ar.saving_execution = 0;
      info_rejestrator_ar.number_records = 0;
    
      //Помічаємо, що номер запису не вибраний
      number_record_of_ar_for_menu = 0xffff;
      number_record_of_ar_for_USB = 0xffff;
      number_record_of_ar_for_RS485 = 0xffff;

      //Знімаємо команду очистки аналогового реєстратора
      clean_rejestrators &= (unsigned int)(~CLEAN_AR);
    }
    
    //Дискретний реєстратор
    if (
        ((clean_rejestrators & CLEAN_DR) != 0)
        &&  
        (
         (control_tasks_dataflash & (
                                     TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR | 
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB                    |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485                  |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU
                                    )
         ) == 0
        )
       )   
    {
      //Виставлено каманда очистити дискретного реєстратор

      //Виставляємо команду запису цієї структури у EEPROM
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);

      //Очищаємо структуру інформації по дискретному реєстраторі
      info_rejestrator_dr.next_address = MIN_ADDRESS_DR_AREA;
      info_rejestrator_dr.saving_execution = 0;
      info_rejestrator_dr.number_records = 0;

      //Помічаємо, що номер запису не вибраний
      number_record_of_dr_for_menu  = 0xffff;
      number_record_of_dr_for_USB   = 0xffff;
      number_record_of_dr_for_RS485 = 0xffff;

      //Знімаємо команду очистки дискретного реєстратора
      clean_rejestrators &= (unsigned int)(~CLEAN_DR);
    }
    /***********************************************************/

    /***********************************************************/
    //Опрцювання логічних тайменрів і дискретних входів тільки коли настройки успішно прочитані
    /***********************************************************/
    clocking_global_timers();
    /***********************************************************/
    
    /***********************************************************/
    //Опрцювання функцій захистів
    /***********************************************************/
    //Діагностика вузлів, яку треба проводити кожен раз перед початком опрацьовуванням логіки пристрою
    unsigned int control_state_outputs_1 = (( (~((unsigned int)(_DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_1)))) >> 8) & ((1 << NUMBER_OUTPUTS_1) - 1));
    unsigned int control_state_outputs_2 = (( (~((unsigned int)(_DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_2)))) >> 8) & ((1 << NUMBER_OUTPUTS_2) - 1));
    unsigned int control_state_outputs = control_state_outputs_1 | (control_state_outputs_2 << NUMBER_OUTPUTS_1);
    //Формуємо стани виходів у відповідності до зміненої нумерації
    unsigned int temp_state_outputs = 0;
    for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
    {
      if ((state_outputs & (1 << index)) != 0) 
      {
        if (index < NUMBER_OUTPUTS_1)
          temp_state_outputs |= 1 << (NUMBER_OUTPUTS_1 - index - 1);
        else
          temp_state_outputs |= 1 << index;
      }
    }
    if (control_state_outputs != temp_state_outputs) _SET_BIT(set_diagnostyka, ERROR_DIGITAL_OUTPUTS_BIT);
//    else _SET_BIT(clear_diagnostyka, ERROR_DIGITAL_OUTPUTS_BIT);
    
    //Перевіряємо достовірність значень для аналогового реєстратора
    if (
        (state_ar_record  != STATE_AR_TEMPORARY_BLOCK) &&
        (changed_settings == CHANGED_ETAP_NONE       )  
       )   
    {
      //Перевірку здійснюємо тільки тоді, коли не іде зміна часових параметрів
      unsigned int size_one_ar_record_tmp = size_one_ar_record, max_number_records_ar_tmp = max_number_records_ar;
      if (
          ((number_word_digital_part_ar*8*sizeof(short int)) < NUMBER_TOTAL_SIGNAL_FOR_RANG)
          ||  
          (size_one_ar_record_tmp != (sizeof(__HEADER_AR) + ((current_settings_prt.prefault_number_periods + current_settings_prt.postfault_number_periods) << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int)))
          ||
          (
           !(
             (size_one_ar_record_tmp* max_number_records_ar_tmp      <= ((NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2))) &&
             (size_one_ar_record_tmp*(max_number_records_ar_tmp + 1) >  ((NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2)))
            ) 
          ) 
         )
      {
        //Теоретично ця помилка ніколи не малаб реєструватися
        /*Якщо виникла така ситуація то треба зациклити ропаграму, щоб вона пішла на перезапуск - 
        бо відбулася недопустима незрозуміла помилка у розраховуваних параметрах аналогового реєстратора.
        Не зрозумілу чого вона виникла, коли і де, коректність роботи пригоамного забезпечення під питанням!*/
        total_error_sw_fixed(5);
      }
    }

    //Функції захистів
    main_protection();
    /***********************************************************/

    /***********************************************************/
    //Перевірка на необхідність зроботи резервні копії даних для самоконтролю
    /***********************************************************/
    //Триґерна інформація
    if (periodical_tasks_TEST_TRG_FUNC != 0)
    {
      //Стоїть у черзі активна задача зроботи резервні копії даних
      if ((state_i2c_task & STATE_TRG_FUNC_EEPROM_GOOD) != 0)
      {
        //Робимо копію тільки тоді, коли триґерна інформація успішно зчитана і сформована контрольна сума
        if (
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT    ) == 0)
           ) 
        {
          //На даний моммент не іде читання-запис триґерної інформації, тому можна здійснити копіювання
          for (unsigned int i = 0; i < N_BIG; i++) trigger_active_functions_ctrl[i] = trigger_active_functions[i];
          crc_trg_func_ctrl = crc_trg_func;

          //Скидаємо активну задачу формування резервної копії 
          periodical_tasks_TEST_TRG_FUNC = false;
          //Виставляємо активну задачу контролю достовірності по резервній копії 
          periodical_tasks_TEST_TRG_FUNC_LOCK = true;
        }
      }
      else
      {
        //Скидаємо активну задачу формування резервної копії 
        periodical_tasks_TEST_TRG_FUNC = false;
      }
    }

    //Аналоговий реєстратор
    if (periodical_tasks_TEST_INFO_REJESTRATOR_AR != 0)
    {
      //Стоїть у черзі активна задача зроботи резервні копії даних
      if ((state_i2c_task & STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD) != 0)
      {
        //Робимо копію тільки тоді, коли структура інформації реєстратора успішно зчитана і сформована контрольна сума
        if (
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0)
           ) 
        {
          //На даний моммент не іде читання-запис структури інформації реєстратора, тому можна здійснити копіювання
          info_rejestrator_ar_ctrl = info_rejestrator_ar;
          crc_info_rejestrator_ar_ctrl = crc_info_rejestrator_ar;

          //Скидаємо активну задачу формування резервної копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
          //Виставляємо активну задачу контролю достовірності по резервній копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK = true;
        }
      }
      else
      {
        //Скидаємо активну задачу формування резервної копії 
        periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
      }
    }

    //Дискретний реєстратор
    if (periodical_tasks_TEST_INFO_REJESTRATOR_DR != 0)
    {
      //Стоїть у черзі активна задача зроботи резервні копії даних
      if ((state_i2c_task & STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD) != 0)
      {
        //Робимо копію тільки тоді, коли структура інформації реєстратора успішно зчитана і сформована контрольна сума
        if (
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0)
           ) 
        {
          //На даний моммент не іде читання-запис структури інформації реєстратора, тому можна здійснити копіювання
          info_rejestrator_dr_ctrl = info_rejestrator_dr;
          crc_info_rejestrator_dr_ctrl = crc_info_rejestrator_dr;

          //Скидаємо активну задачу формування резервної копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
          //Виставляємо активну задачу контролю достовірності по резервній копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK = true;
        }
      }
      else
      {
        //Скидаємо активну задачу формування резервної копії 
        periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
      }
    }
    /***********************************************************/

    /***********************************************************/
    //Встановлюємо "значення лічильника для наступного переривання"
    /***********************************************************/
    uint32_t capture_new;
    unsigned int delta;
    TIM2->CCR1 = (capture_new = (current_tick + (delta = TIM2_CCR1_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM2->CNT;

      uint64_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x100000000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM2, TIM_IT_CC1) == RESET)
        {
          if (delta < TIM2_CCR1_VAL)
          {
            uint64_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x100000000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM2_CCR1_VAL)
            delta = 1; /*Намагаємося, щоб нове переивання запустилося як омога скоріше*/
          else
          {
            //Теоретично цього ніколи не мало б бути
            total_error_sw_fixed(83);
          }
          TIM2->CCR1 = (capture_new = (TIM2->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/
    
    /***********************************************************/
    //Виставляємо повідомлення про те, система захисів праціює
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_PROTECTION;
    /***********************************************************/
    /***********************************************************************************************/
  }
  else
  {
    total_error_sw_fixed(23);
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

