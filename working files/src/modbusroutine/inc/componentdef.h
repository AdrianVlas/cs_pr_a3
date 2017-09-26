#ifndef __COMPONENTDEF_H
#define __COMPONENTDEF_H


typedef struct
{
  int operativMarker[2];//оперативный маркер
  int countObject;//к-во обектов
  int isActiveActualData;

  int (*getModbusRegister)(int);//получить содержимое регистра
  int (*getModbusBit)(int);//получить содержимое бита
  int (*setModbusRegister)(int, int);//записать регистр
  int (*setModbusBit)(int, int);//записать бит

  void (*preReadAction)(void);//action до чтения
  void (*postReadAction)(void);//action после чтения
  void (*preWriteAction)(void);//action до записи
  void (*config_and_settings)(void);//action активации
  int (*postWriteAction)(void);//action после записи

} COMPONENT_OBJ;

#endif



