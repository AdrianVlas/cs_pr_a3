#ifndef __CONST_DIAGNOSTYKA_MENU2__
#define __CONST_DIAGNOSTYKA_MENU2__

#define N_DIAGN_ARRAYS  9

enum _error_id 
{
ERROR_START_VIA_I2C_BIT = 0,
ERROR_USTUVANNJA_EEPROM_BIT,
ERROR_USTUVANNJA_EEPROM_EMPTY_BIT,
ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT,
ERROR_USTUVANNJA_EEPROM_CONTROL_BIT,
ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT,
ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT,
ERROR_CONFIG_EEPROM_BIT,
ERROR_CONFIG_EEPROM_EMPTY_BIT,
ERROR_CONFIG_EEPROM_COMPARISON_BIT,
ERROR_CONFIG_EEPROM_CONTROL_BIT,
ERROR_NO_FREE_DYNAMIC_MEMORY_BIT,
ERROR_PRT_MEMORY_BIT,
ERROR_SETTINGS_EEPROM_BIT,
ERROR_SETTINGS_EEPROM_EMPTY_BIT,
ERROR_SETTINGS_EEPROM_COMPARISON_BIT,
ERROR_SETTINGS_EEPROM_CONTROL_BIT,
ERROR_TRG_FUNC_EEPROM_BIT,
ERROR_TRG_FUNC_EEPROM_EMPTY_BIT,
ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT,
ERROR_TRG_FUNC_EEPROM_CONTROL_BIT,
ERROR_INFO_REJESTRATOR_LOG_EEPROM_BIT,
ERROR_INFO_REJESTRATOR_LOG_EEPROM_EMPTY_BIT,
ERROR_INFO_REJESTRATOR_LOG_COMPARISON_BIT,
ERROR_INFO_REJESTRATOR_LOG_CONTROL_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_CONTROL_BIT,

RTC_BATTERY_LOW_BIT,
RTC_OSCILLATOR_STOPED_BIT,
RTC_OSCILLATOR_FAIL_BIT,
RTC_UPDATING_HALTED_BIT,
RTC_WORK_FIELD_NOT_SET_BIT,

ERROR_GND_ADC_TEST_BIT,
ERROR_VREF_ADC_TEST_BIT,
ERROR_VDD_ADC_TEST_BIT,
ERROR_GND_ADC_TEST_COARSE_BIT,
ERROR_VREF_ADC_TEST_COARSE_BIT,
ERROR_VDD_ADC_TEST_COARSE_BIT,

ERROR_LOG_OVERLOAD_BIT,
ERROR_LOG_LOSS_INFORMATION_BIT,
ERROR_PR_ERR_OVERLOAD_BIT,
ERROR_PR_ERR_LOSS_INFORMATION_BIT,

EVENT_CHANGE_CONFIGURATION_BIT,
EVENT_CHANGE_SETTINGS_BIT,
EVENT_START_SYSTEM_BIT,
EVENT_RESTART_SYSTEM_BIT,
EVENT_SOFT_RESTART_SYSTEM_BIT,
EVENT_STOP_SYSTEM_BIT,
EVENT_DROP_POWER_BIT,

ERROR_LCD_BIT,
ERROR_SPI_DF_BIT,
ERROR_EXTERNAL_SRAM_BIT,
ERROR_INTERNAL_FLASH_BIT,

ERROR_DIGITAL_OUTPUTS_BIT,

_NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS = ERROR_DIGITAL_OUTPUTS_BIT
};

#define MAX_ROW_FOR_DIAGNOSTYKA              (_NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS + 1)


#define NUMBER_ERRORS (_NUMBER_ERRORS_WITHOUT_DIGITAL_OUTPUTS + current_config_prt.n_output)

#define MASKA_AVAR_ERROR_0        (unsigned int)(               \
    (1 << (ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT))             \
  | (1 << (ERROR_CONFIG_EEPROM_BIT))                            \
  | (1 << (ERROR_CONFIG_EEPROM_EMPTY_BIT))                      \
  | (1 << (ERROR_CONFIG_EEPROM_COMPARISON_BIT) )                \
  | (1 << (ERROR_CONFIG_EEPROM_CONTROL_BIT))                    \
  | (1 << (ERROR_NO_FREE_DYNAMIC_MEMORY_BIT))                   \
  | (1 << (ERROR_PRT_MEMORY_BIT))                               \
  | (1 << (ERROR_SETTINGS_EEPROM_BIT))                          \
  | (1 << (ERROR_SETTINGS_EEPROM_EMPTY_BIT))                    \
  | (1 << (ERROR_SETTINGS_EEPROM_COMPARISON_BIT) )              \
  | (1 << (ERROR_SETTINGS_EEPROM_CONTROL_BIT))                  \
  | (1 << (ERROR_USTUVANNJA_EEPROM_BIT) )                       \
  | (1 << (ERROR_USTUVANNJA_EEPROM_EMPTY_BIT))                  \
  | (1 << (ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT))             \
  | (1 << (ERROR_USTUVANNJA_EEPROM_CONTROL_BIT))                \
  | (1 << (ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT))     \
  | (1 << (ERROR_TRG_FUNC_EEPROM_BIT))                          \
  | (1 << (ERROR_TRG_FUNC_EEPROM_EMPTY_BIT))                    \
  | (1 << (ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT))               \
  | (1 << (ERROR_TRG_FUNC_EEPROM_CONTROL_BIT))                  \
)

#define MASKA_AVAR_ERROR_1        (unsigned int)(               \
    (1 << (ERROR_GND_ADC_TEST_BIT - 32))                        \
  | (1 << (ERROR_VREF_ADC_TEST_BIT - 32))                       \
  | (1 << (ERROR_VDD_ADC_TEST_BIT - 32))                        \
  | (1 << (ERROR_GND_ADC_TEST_COARSE_BIT - 32))                 \
  | (1 << (ERROR_VREF_ADC_TEST_COARSE_BIT - 32))                \
  | (1 << (ERROR_VDD_ADC_TEST_COARSE_BIT - 32))                 \
  | (1 << (ERROR_EXTERNAL_SRAM_BIT - 32))                       \
  | (1 << (ERROR_INTERNAL_FLASH_BIT - 32))                      \
)

#define MASKA_AVAR_ERROR_2              0


# define NAME_DIAGN_RU  \
  " Ош.I2C         ",   \
  " Ош.юстирования ",   \
  " Юстирования нет",   \
  " Ош.зап.юстир.  ",   \
  " Ош.контр.юстир.",   \
  " Ош.юстир.набора",   \
  " Ош.типа конф.  ",   \
  " Ош.конфигурации",   \
  "Конфигурации нет",   \
  "  Ош.зап.конф.  ",   \
  " Ош.конф.настр. ",   \
  " Недост.динам.п.",   \
  " Ош.памяти защит",   \
  " Ош.настроек    ",   \
  " Настроек нет   ",   \
  " Ош.зап.настр.  ",   \
  " Ош.контр.настр.",   \
  "  Ош.триг.инф.  ",   \
  "  Триг.инф.нет  ",   \
  "Ош.зап.триг.инф.",   \
  "Ош.контр.триг.и.",   \
  " Ош.инф.ж.соб.  ",   \
  " Инф.ж.соб.нет  ",   \
  " Ош.зап.и.ж.соб.",   \
  " Ош.контр.ж.соб.",   \
  "Ош.инф.рег.пр.с.",   \
  "Инф.рег.пр.с.нет",   \
  "Ош.зап.и.р.пр.с.",   \
  "Ош.контр.р.пр.с.",   \
  " Батарея разряж.",   \
  "Осцилятор остан.",   \
  "Отказ Осцилятора",   \
  " Ост.обновл.RTC ",   \
  " Не уст.поля RTC",   \
  " Тест GND АЦП   ",   \
  " Тест VREF АЦП  ",   \
  " Тест VDD АЦП   ",   \
  "Тест GND АЦП гр.",   \
  "Тест VREF АЦП гр",   \
  "Тест VDD АЦП гр.",   \
  "Переп.буф.ж.соб.",   \
  " Потеря д.ж.соб.",   \
  "Переп.буф.пр.ош.",   \
  " Потеря д.пр.ош.",   \
  "Изм.конфиругации",   \
  " Изм.настроек   ",   \
  " Старт устр.    ",   \
  " Рестарт устр.  ",   \
  "Пр.Рестарт устр.",   \
  " Останов.устр.  ",   \
  " Пропад.питания ",   \
  " Отказ ЖКИ      ",   \
  " Ош.SPI_DF      ",   \
  " Ош.внешней SRAM",   \
  " Ош.внутр.FLASH ",   \
  " Ош.вых.реле    "

# define NAME_DIAGN_UA  \
  " Пом.I2C        ",   \
  " Пом.юстування  ",   \
  " Юстування нема ",   \
  " Пом.зап.юст.   ",   \
  " Пом.контр.юст. ",   \
  " Пом.юст.набору ",   \
  " Пом.типу конф. ",   \
  "Пом.конфігурації",   \
  " Конф.нема      ",   \
  " Пом.зап.конф.  ",   \
  " Пом.контр.конф.",   \
  " Недост.динам.п.",   \
  "Пом.пам'яті зах.",   \
  " Пом.налаштувань",   \
  "Налаштувань нема",   \
  " Пом.зап.налашт.",   \
  "Пом.контр.налашт",   \
  " Пом.триґ.інф.  ",   \
  " Триґ.інф.нема  ",   \
  " Пом.зап.триґ.і.",   \
  "Пом.контр.триґ.і",   \
  " Пом.інф.ж.п.   ",   \
  " Інф.ж.п.нема   ",   \
  " Пом.зап.і.ж.п. ",   \
  " Пом.контр.ж.п. ",   \
  " Пом.інф.р.пр.п.",   \
  " Інф.р.пр.п.нема",   \
  "Пом.зап.і.р.пр.п",   \
  "Пом.контр.р.пр.п",   \
  "Батарея разрядж.",   \
  " Осцилятор зуп. ",   \
  " Відм.Осцилятора",   \
  " Зуп.обновл.RTC ",   \
  " Не вст.поля RTC",   \
  " Тест GND АЦП   ",   \
  " Тест VREF АЦП  ",   \
  " Тест VDD АЦП   ",   \
  "Тест GND АЦП гр.",   \
  "Тест VREF АЦП гр",   \
  "Тест VDD АЦП гр.",   \
  " Переп.буф.ж.п. ",   \
  " Втрата д.ж.п.  ",   \
  "Переп.буф.р.пр.п",   \
  " Втрата д.р.пр.п",   \
  " Зм.конфіругації",   \
  " Зм.налаштувань ",   \
  " Старт пристр.  ",   \
  " Рестарт пристр.",   \
  " Пр.Рестарт пр. ",   \
  " Зуп.пристр.    ",   \
  " Пропад.живлення",   \
  " Відмова РКІ    ",   \
  " Пом.SPI_DF     ",   \
  " Пом.зовн.SRAM  ",   \
  " Пом.внутр.FLASH",   \
  " Пом.вих.реле   "

# define NAME_DIAGN_EN  \
  " I2C Err.       ",   \
  " Adjust Err.    ",   \
  " No adjust      ",   \
  " Adjust W.Err.  ",   \
  "Adjust Ctrl.Err.",   \
  " Adjust-Set Err.",   \
  " Conf.Type Err. ",   \
  " Conf.Err.      ",   \
  " No Conf.       ",   \
  " Conf.W.Err.    ",   \
  " Conf.Ctrl.Err. ",   \
  "No enough dyn.m.",   \
  " Ош.памяти защит",   \
  " Settings Err.  ",   \
  " No settings    ",   \
  " Sett.W.Err.    ",   \
  " Sett.Ctrl.Err. ",   \
  "  Ош.триг.инф.  ",   \
  "  Триг.инф.нет  ",   \
  "Ош.зап.триг.инф.",   \
  "Ош.контр.триг.и.",   \
  " Ev.Log.Inf.Err.",   \
  " No Ev.Log.Inf. ",   \
  "Inf.Ev.Log.W.Err",   \
  "Ev.Log.Ctrl.Err.",   \
  " PER Inf.Err.   ",   \
  " No Inf.of PER  ",   \
  "Inf.W.Err.of PER",   \
  " PER Ctrl.Err.  ",   \
  " RTC:Battery low",   \
  " RTC:Osc.stop   ",   \
  " RTC:Osc.fail   ",   \
  " RTC:Halt update",   \
  "RTC:No def.sett.",   \
  " ADC:GND fail   ",   \
  " ADC:VREF fail  ",   \
  " ADC:VDD fail   ",   \
  " ADC:GND Test R.",   \
  " ADC:VREF Test R",   \
  " ADC:VDD Test R.",   \
  "OVF of Ev.Log.b.",   \
  "Ev.Log.Data lost",   \
  "OVF of PER buff.",   \
  " PER Data lost  ",   \
  " Conf.changed   ",   \
  "Settings changed",   \
  " Device Start   ",   \
  " Device Restart ",   \
  " Device SFTRST  ",   \
  " Device Stop    ",   \
  " Пропад.питания ",   \
  " LCD Fail       ",   \
  " DF SPI Err.    ",   \
  " Ext.SRAM Err.  ",   \
  " Int.FLASH Err. ",   \
  " DO Ctrl.Err.   "

# define NAME_DIAGN_KZ  \
  " Ош.I2C         ",   \
  " Ош.юстирования ",   \
  " Юстирования нет",   \
  " Ош.зап.юстир.  ",   \
  " Ош.контр.юстир.",   \
  " Ош.юстир.набора",   \
  " Ош.типа конф.  ",   \
  " Ош.конфигурации",   \
  "Конфигурации нет",   \
  " Ош.зап.конф.   ",   \
  " Ош.конф.настр. ",   \
  " Недост.динам.п.",   \
  " Ош.памяти защит",   \
  " Ош.настроек    ",   \
  " Настроек нет   ",   \
  " Ош.зап.настр.  ",   \
  " Ош.контр.настр.",   \
  "  Ош.триг.инф.  ",   \
  "  Триг.инф.нет  ",   \
  "Ош.зап.триг.инф.",   \
  "Ош.контр.триг.и.",   \
  " Ош.инф.ж.соб.  ",   \
  " Инф.ж.соб.нет  ",   \
  " Ош.зап.и.ж.соб.",   \
  " Ош.контр.ж.соб.",   \
  "Ош.инф.рег.пр.с.",   \
  "Инф.рег.пр.с.нет",   \
  "Ош.зап.и.р.пр.с.",   \
  "Ош.контр.р.пр.с.",   \
  " Батарея разряж.",   \
  "Осцилятор остан.",   \
  "Отказ Осцилятора",   \
  " Ост.обновл.RTC ",   \
  " Не уст.поля RTC",   \
  " Тест GND АЦП   ",   \
  " Тест VREF АЦП  ",   \
  " Тест VDD АЦП   ",   \
  "Тест GND АЦП гр.",   \
  "Тест VREF АЦП гр",   \
  "Тест VDD АЦП гр.",   \
  "Переп.буф.ж.соб.",   \
  " Потеря д.ж.соб.",   \
  "Переп.буф.пр.ош.",   \
  " Потеря д.пр.ош.",   \
  "Изм.конфиругации",   \
  " Изм.настроек   ",   \
  " Старт устр.    ",   \
  " Рестарт устр.  ",   \
  "Пр.Рестарт устр.",   \
  " Останов.устр.  ",   \
  " Пропад.питания ",   \
  " Отказ ЖКИ      ",   \
  " Ош.SPI_DF      ",   \
  " Ош.внешней SRAM",   \
  " Ош.внутр.FLASH ",   \
  " Ош.вых.реле    "


#endif
