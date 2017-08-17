#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 4664
//макс к-во обектов
#define TOTAL_OBJ 128
#define REGISTER_FOR_OBJ 1

int privateGIBigGetReg1(int adrReg);
int privateGIBigGetReg2(int adrReg);

int getGIBigModbusRegister(int);//получить содержимое регистра
int getGIBigModbusBit(int);//получить содержимое бита
int setGIBigModbusRegister(int, int);//получить содержимое регистра
int setGIBigModbusBit(int, int);//получить содержимое бита

void setGIBigCountObject(void);//записать к-во обектов
void preGIBigReadAction(void);//action до чтения
void postGIBigReadAction(void);//action после чтения
void preGIBigWriteAction(void);//action до записи
int postGIBigWriteAction(void);//action после записи
//void loadGIBigActualData(void);

COMPONENT_OBJ *gibigcomponent;

/**************************************/
//подготовка компонента генераторов импульсов
/**************************************/
void constructorGIBigComponent(COMPONENT_OBJ *gibigcomp)
{
  gibigcomponent = gibigcomp;

  gibigcomponent->countObject = 0;//к-во обектов

  gibigcomponent->getModbusRegister = getGIBigModbusRegister;//получить содержимое регистра
  gibigcomponent->getModbusBit      = getGIBigModbusBit;//получить содержимое бита
  gibigcomponent->setModbusRegister = setGIBigModbusRegister;//получить содержимое регистра
  gibigcomponent->setModbusBit      = setGIBigModbusBit;//получить содержимое бита

  gibigcomponent->preReadAction   = preGIBigReadAction;//action до чтения
  gibigcomponent->postReadAction  = postGIBigReadAction;//action после чтения
  gibigcomponent->preWriteAction  = preGIBigWriteAction;//action до записи
  gibigcomponent->postWriteAction = postGIBigWriteAction;//action после записи

  gibigcomponent->isActiveActualData = 0;
}//prepareDVinConfig
/*
void loadGIBigActualData(void) {
 setGIBigCountObject(); //записать к-во обектов
  //ActualData
   __LN_MEANDER *arr = (__LN_MEANDER*)(spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
   for(int item=0; item<gibigcomponent->countObject; item++) {

   int value = arr[item].settings.set_delay[0];
   tempReadArray[item*REGISTER_FOR_OBJ+0] = value;
   }//for

}//loadActualData() 
*/

int getGIBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
extern int pointInterface;//метка интерфейса 0-USB 1-RS485
  if(privateGIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(gibigcomponent->isActiveActualData) setGIBigCountObject(); //к-во обектов
  gibigcomponent->isActiveActualData = 0;
  if(privateGIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(gibigcomponent, adrReg);
/*
   __LN_MEANDER *arr = (__LN_MEANDER*)(spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
   return arr[idxSubObj].settings.set_delay[0]/100;
 }//switch
*/
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта
  __settings_for_MEANDER *arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_USB_LOCKS)) == 0 ) ? &(((__LN_MEANDER*)(spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_MEANDER*)(sca_of_p[ID_FB_MEANDER - _ID_FB_FIRST_VAR])) + idxSubObj);
  if(pointInterface)//метка интерфейса 0-USB 1-RS485
                        arr =  ((config_settings_modified & MASKA_FOR_BIT(BIT_RS485_LOCKS)) == 0 ) ? &(((__LN_MEANDER*)(spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR])) + idxSubObj)->settings : (((__settings_for_MEANDER*)(sca_of_p[ID_FB_MEANDER - _ID_FB_FIRST_VAR])) + idxSubObj);
  switch(offset%REGISTER_FOR_OBJ) {//индекс регистра 
   case 0:
   return arr->set_delay[0]/100;
 }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getGIBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setGIBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateGIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(gibigcomponent->isActiveActualData) setGIBigCountObject(); //к-во обектов
  gibigcomponent->isActiveActualData = 0;
  if(privateGIBigGetReg1(adrReg)==MARKER_OUTPERIMETR) return MARKER_ERRORPERIMETR;

  superSetOperativMarker(gibigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

    if(dataReg>100) return MARKER_ERRORDIAPAZON;
    if(dataReg<5) return MARKER_ERRORDIAPAZON;

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setGIBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void setGIBigCountObject(void) {
//записать к-во обектов
  int cntObj = current_config.n_meander;  //Кількість генераторів меандру
  if(cntObj<0) return;
  if(cntObj>TOTAL_OBJ) return;
  gibigcomponent->countObject = cntObj;
}//
void preGIBigReadAction(void) {
//action до чтения
  gibigcomponent->operativMarker[0] = -1;
  gibigcomponent->operativMarker[1] = -1;//оперативный маркер
  gibigcomponent->isActiveActualData = 1;
}//
void postGIBigReadAction(void) {
//action после чтения
  if(gibigcomponent->operativMarker[0]<0) return;//не было чтения
}//
void preGIBigWriteAction(void) {
//action до записи
  gibigcomponent->operativMarker[0] = -1;
  gibigcomponent->operativMarker[1] = -1;//оперативный маркер
  gibigcomponent->isActiveActualData = 1;
}//
int postGIBigWriteAction(void) {
//action после записи
  if(gibigcomponent->operativMarker[0]<0) return 0;//не было записи
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countRegister = gibigcomponent->operativMarker[1]-gibigcomponent->operativMarker[0]+1;
  if(gibigcomponent->operativMarker[1]<0) countRegister = 1;

   __settings_for_MEANDER *arr  = (__settings_for_MEANDER*)(sca_of_p[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
   __settings_for_MEANDER *arr1 = (__settings_for_MEANDER*)(sca_of_p_edit[ID_FB_MEANDER - _ID_FB_FIRST_VAR]);
  for(int i=0; i<countRegister; i++) {
  int offset = i+gibigcomponent->operativMarker[0]-BEGIN_ADR_REGISTER;
  int idxSubObj = offset/REGISTER_FOR_OBJ;//индекс субобъекта

   arr1[idxSubObj].set_delay[0] = arr[idxSubObj].set_delay[0] = (tempWriteArray[offsetTempWriteArray+i])*100;

  }//for
  config_settings_modified |= MASKA_FOR_BIT(BIT_CHANGED_SETTINGS);
  restart_timeout_idle_new_settings = true;
 return 0;
}//

int privateGIBigGetReg1(int adrReg)
{
  //проверить внутренний периметр
  int count_register = gibigcomponent->countObject*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg1(int adrReg)
int privateGIBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  int count_register = TOTAL_OBJ*REGISTER_FOR_OBJ;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)
