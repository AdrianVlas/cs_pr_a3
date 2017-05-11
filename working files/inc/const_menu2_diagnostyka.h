#ifndef __CONST_DIAGNOSTYKA_MENU2__
#define __CONST_DIAGNOSTYKA_MENU2__

#define MAX_ROW_FOR_DIAGNOSTYKA              (8*(4 + 4))

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
ERROR_INFO_REJESTRATOR_DR_EEPROM_BIT,
ERROR_INFO_REJESTRATOR_DR_EEPROM_EMPTY_BIT,
ERROR_INFO_REJESTRATOR_DR_COMPARISON_BIT,
ERROR_INFO_REJESTRATOR_DR_CONTROL_BIT,
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

ERROR_DIGITAL_OUTPUTS_BIT,

ERROR_PR_ERR_OVERLOAD_BIT,
ERROR_PR_ERR_LOSS_INFORMATION_BIT,

EVENT_START_SYSTEM_BIT,
EVENT_RESTART_SYSTEM_BIT,
EVENT_STOP_SYSTEM_BIT,
EVENT_DROP_POWER_BIT,

ERROR_LCD_BIT,
ERROR_SPI_DF_BIT,
ERROR_EXTERNAL_SRAM_BIT,
ERROR_INTERNAL_FLASH_BIT,

_NUMBER_ERRORS


};

#define MASKA_AVAR_ERROR_0        (unsigned int)(               \
    (1 << (ERROR_CONFIG_EEPROM_BIT))                            \
  | (1 << (ERROR_CONFIG_EEPROM_EMPTY_BIT))                      \
  | (1 << (ERROR_CONFIG_EEPROM_COMPARISON_BIT) )                \
  | (1 << (ERROR_CONFIG_EEPROM_CONTROL_BIT))                    \
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
  | (1 << (ERROR_DIGITAL_OUTPUTS_BIT + 0 - 32))                 \
  | (1 << (ERROR_INTERNAL_FLASH_BIT - 32))                      \
)

#define MASKA_AVAR_ERROR_2              0


# define NAME_DIAGN_RU  \
  " ��.I2C         ",   \
  " ��.����������� ",   \
  " ����������� ���",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  " ��.�����.������",   \
  " ��.���� ����.  ",   \
  " ��.������������",   \
  "������������ ���",   \
  "  ��.���.����.  ",   \
  " ��.����.�����. ",   \
  " ������.�����.�.",   \
  " ��.������ �����",   \
  " ��.��������    ",   \
  " �������� ���   ",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  "  ��.����.���.  ",   \
  "  ����.���.���  ",   \
  "��.���.����.���.",   \
  "��.�����.����.�.",   \
  " ��.���.�.���.  ",   \
  " ���.�.���.���  ",   \
  " ��.���.�.�.���.",   \
  " ��.�����.�.���.",   \
  "��.���.���.��.�.",   \
  "���.���.��.�.���",   \
  "��.���.�.�.��.�.",   \
  "��.�����.�.��.�.",   \
  " ������� ������.",   \
  "��������� �����.",   \
  "����� ����������",   \
  " ���.������.RTC ",   \
  " �� ���.���� RTC",   \
  " ���� GND ���   ",   \
  " ���� VREF ���  ",   \
  " ���� VDD ���   ",   \
  "���� GND ��� ��.",   \
  "���� VREF ��� ��",   \
  "���� VDD ��� ��.",   \
  " ��.���.����    ",   \
  "�����.���.��.��.",   \
  " ������ �.��.��.",   \
  " ����� ����.    ",   \
  " ������� ����.  ",   \
  " �������.����.  ",   \
  " ������.������� ",   \
  " ����� ���      ",   \
  " ��.SPI_DF      ",   \
  " ��.������� SRAM",   \
  " ��.�����.FLASH ",   \
  " ������ 52      ",   \
  " ������ 53      ",   \
  " ������ 54      ",   \
  " ������ 55      ",   \
  " ������ 56      ",   \
  " ������ 57      ",   \
  " ������ 58      ",   \
  " ������ 59      ",   \
  " ������ 60      ",   \
  " ������ 61      ",   \
  " ������ 62      ",   \
  " ������ 63      ",   \
  " ������ 64      "

# define NAME_DIAGN_UA  \
  " ���.I2C        ",   \
  " ���.���������  ",   \
  " ��������� ���� ",   \
  " ���.���.���.   ",   \
  " ���.�����.���. ",   \
  " ���.���.������ ",   \
  " ���.���� ����. ",   \
  "���.������������",   \
  " ����.����      ",   \
  " ���.���.����.  ",   \
  " ���.�����.����.",   \
  " ������.�����.�.",   \
  "���.���'�� ���.",   \
  " ���.�����������",   \
  "����������� ����",   \
  " ���.���.������.",   \
  "���.�����.������",   \
  " ���.���.���.  ",   \
  " ���.���.����  ",   \
  " ���.���.���.�.",   \
  "���.�����.���.�",   \
  " ���.���.�.�.   ",   \
  " ���.�.�.����   ",   \
  " ���.���.�.�.�. ",   \
  " ���.�����.�.�. ",   \
  " ���.���.�.��.�.",   \
  " ���.�.��.�.����",   \
  "���.���.�.�.��.�",   \
  "���.�����.�.��.�",   \
  "������� �������.",   \
  " ��������� ���. ",   \
  " ³��.����������",   \
  " ���.������.RTC ",   \
  " �� ���.���� RTC",   \
  " ���� GND ���   ",   \
  " ���� VREF ���  ",   \
  " ���� VDD ���   ",   \
  "���� GND ��� ��.",   \
  "���� VREF ��� ��",   \
  "���� VDD ��� ��.",   \
  " ���.���.����   ",   \
  "�����.���.�.��.�",   \
  " ������ �.�.��.�",   \
  " ����� ������.  ",   \
  " ������� ������.",   \
  " ���.������.    ",   \
  " ������.��������",   \
  " ³����� �ʲ    ",   \
  " ���.SPI_DF     ",   \
  " ���.����.SRAM  ",   \
  " ���.�����.FLASH",   \
  " ������� 52     ",   \
  " ������� 53     ",   \
  " ������� 54     ",   \
  " ������� 55     ",   \
  " ������� 56     ",   \
  " ������� 57     ",   \
  " ������� 58     ",   \
  " ������� 59     ",   \
  " ������� 60     ",   \
  " ������� 61     ",   \
  " ������� 62     ",   \
  " ������� 63     ",   \
  " ������� 64     "

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
  " ��.������ �����",   \
  " Settings Err.  ",   \
  " No settings    ",   \
  " Sett.W.Err.    ",   \
  " Sett.Ctrl.Err. ",   \
  "  ��.����.���.  ",   \
  "  ����.���.���  ",   \
  "��.���.����.���.",   \
  "��.�����.����.�.",   \
  " D.Rec.Inf.Err. ",   \
  " No D.Rec.Inf.  ",   \
  "Inf.D.Rec.W.Err.",   \
  " D.Rec.Ctrl.Err.",   \
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
  " DO Ctrl.Err.   ",   \
  "OVF of PER buff.",   \
  " PER Data lost  ",   \
  " Device Start   ",   \
  " Device Restart ",   \
  " Device Stop    ",   \
  " ������.������� ",   \
  " LCD Fail       ",   \
  " DF SPI Err.    ",   \
  " Ext.SRAM Err.  ",   \
  " Int.FLASH Err. ",   \
  " Error 52       ",   \
  " Error 53       ",   \
  " Error 54       ",   \
  " Error 55       ",   \
  " Error 56       ",   \
  " Error 57       ",   \
  " Error 58       ",   \
  " Error 59       ",   \
  " Error 60       ",   \
  " Error 61       ",   \
  " Error 62       ",   \
  " Error 63       ",   \
  " Error 64       "

# define NAME_DIAGN_KZ  \
  " ��.I2C         ",   \
  " ��.����������� ",   \
  " ����������� ���",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  " ��.�����.������",   \
  " ��.���� ����.  ",   \
  " ��.������������",   \
  "������������ ���",   \
  " ��.���.����.   ",   \
  " ��.����.�����. ",   \
  " ������.�����.�.",   \
  " ��.������ �����",   \
  " ��.��������    ",   \
  " �������� ���   ",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  "  ��.����.���.  ",   \
  "  ����.���.���  ",   \
  "��.���.����.���.",   \
  "��.�����.����.�.",   \
  " ��.���.�.���.  ",   \
  " ���.�.���.���  ",   \
  " ��.���.�.�.���.",   \
  " ��.�����.�.���.",   \
  "��.���.���.��.�.",   \
  "���.���.��.�.���",   \
  "��.���.�.�.��.�.",   \
  "��.�����.�.��.�.",   \
  " ������� ������.",   \
  "��������� �����.",   \
  "����� ����������",   \
  " ���.������.RTC ",   \
  " �� ���.���� RTC",   \
  " ���� GND ���   ",   \
  " ���� VREF ���  ",   \
  " ���� VDD ���   ",   \
  "���� GND ��� ��.",   \
  "���� VREF ��� ��",   \
  "���� VDD ��� ��.",   \
  " ��.���.����    ",   \
  "�����.���.��.��.",   \
  " ������ �.��.��.",   \
  " ����� ����.    ",   \
  " ������� ����.  ",   \
  " �������.����.  ",   \
  " ������.������� ",   \
  " ����� ���      ",   \
  " ��.SPI_DF      ",   \
  " ��.������� SRAM",   \
  " ��.�����.FLASH ",   \
  " ������ 52      ",   \
  " ������ 53      ",   \
  " ������ 54      ",   \
  " ������ 55      ",   \
  " ������ 56      ",   \
  " ������ 57      ",   \
  " ������ 58      ",   \
  " ������ 59      ",   \
  " ������ 60      ",   \
  " ������ 61      ",   \
  " ������ 62      ",   \
  " ������ 63      ",   \
  " ������ 64      "


#endif
