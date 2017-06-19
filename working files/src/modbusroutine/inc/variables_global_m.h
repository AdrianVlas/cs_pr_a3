#ifndef __GLOBAL_VARIABLES_H
#define __GLOBAL_VARIABLES_H

#include "componentdef.h"
#include "componentenum.h"
#include "prototyps.h"

 COMPONENT_OBJ config_array[TOTAL_COMPONENT];
 short tempReadArray[2028];
 short tempWriteArray[MAXIMUMTW];
 int   indexTW;//индекс буфера записи
 short rprAdresRegister[130];//хранилище адресов пользовательских регистров

#endif
