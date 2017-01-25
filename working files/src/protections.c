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
  for (unsigned int i = INDEX_TIMER_TEMP; i < MAX_NUMBER_GLOBAL_TIMERS; i++)
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
//Функція захистів з якої здійснюються всі інші операції
/*****************************************************/
inline void main_protection(void)
{
  /**************************/
  //Перевірка, чи треба очистити трігерні функції
  /**************************/
  if (reset_trigger_function_from_interface !=0)
  {
    
    //Помічаємо що ми виконали очистку по ВСІХ інтерфейсах
    reset_trigger_function_from_interface = 0;
  }
  /**************************/

  /**************************/
  //Опрацьовуємо натиснуті кнопки
  /**************************/
  //Активація з кнопуки
  if (pressed_buttons != 0)
  {

    //Очищаємо натиснуті кнопка, які ми вже опрацювали
    pressed_buttons =0;
  }
  /**************************/
    
  /**************************/
  //Опрацьовуємо сигнали з ТУ/Goose
  /**************************/
  if (activation_function_from_interface != 0)
  {

    //Очищаємо помітку активації функцій з інетфейсу, які ми вже опрацювали
    activation_function_from_interface = 0;
  }
  /**************************/

  /**************************/
  //Опрацьовуємо дискретні входи
  /**************************/
  //Перевіряємо чи є зараз активні входи
  if (state_inputs !=0)
  {
  }
  /**************************/

  /**************************/
  //Виконуємо фільтрацію переднього фронту для тих сигналів, які мають активуватися тільки по передньому фронтові
  /**************************/
  {
  }
  /**************************/

  /***********************************************************/
  //Розрахунок вимірювань
  /***********************************************************/
  calc_measurement();

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
  /**************************/

  /**************************/
  //Сигнал "Несправность Общая"
  /**************************/
  diagnostyca_adc_execution();

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
    /**************************/
    //Сигнал "Несправность Аварийная"
    /**************************/
    if (
        ((diagnostyka_tmp[0] & MASKA_AVAR_ERROR_0) != 0) ||
        ((diagnostyka_tmp[1] & MASKA_AVAR_ERROR_1) != 0) ||
        ((diagnostyka_tmp[2] & MASKA_AVAR_ERROR_2) != 0)
       )   
    {
      _SET_BIT(active_functions, RANG_AVAR_DEFECT);
    }
    else
    {
      _CLEAR_BIT(active_functions, RANG_AVAR_DEFECT);
    }
    /**************************/
  }
  else
  {
    _CLEAR_BIT(active_functions, RANG_DEFECT);
    _CLEAR_BIT(active_functions, RANG_AVAR_DEFECT);
  }
  /**************************/

  
  //Логічні схеми мають працювати тільки у тому випадку, якщо немє сигналу "Аварийная неисправность"
  if (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) == 0)
  {
    //Аварійна ситуація не зафіксована

  }
  else
  {
    //Аварійна ситуація зафіксована
    
    //Скидаємо всі активні функції, крім інформативних
    
    //Деактивовуємо всі реле
    state_outputs = 0;
    
    //Скидаємо всі таймери, які присутні у лозіці
    
  }

  /**************************/
  //Робота з функціями, які мають записуватися у енергонезалежну пам'ять
  /**************************/
//  unsigned int comparison_true = true;
//
//  if (comparison_true != true)
//  {
//    /*
//    Сигнали, значення яких записується у енергонезалежну пам'1ять змінилися.
//    Подаємо команду на їх запис у енергонезалежну пам'ять
//    */
//    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
//  }
  /**************************/

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
    //Перевіряємо необхідність очистки аналогового і дискретного реєстраторів
    /***********************************************************/
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

