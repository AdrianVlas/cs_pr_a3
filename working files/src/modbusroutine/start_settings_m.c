//#include <QtWidgets>
//#include "loghandler.h"

#include "variables_external_m.h"

/**************************************/
//Стартовая инициализация компонентов
/**************************************/
void global_component_installation(void) {
  constructorDVBigComponent(&(config_array[DVBIGCOMPONENT]));//подготовка компонента ДВ
  constructorDVSmallComponent(&(config_array[DVSMALLCOMPONENT]));//подготовка компонента ДВ
  constructorDOUTSmallComponent(&(config_array[DOUTSMALLCOMPONENT]));//подготовка компонента rele
  constructorDOUTBigComponent(&(config_array[DOUTBIGCOMPONENT]));//подготовка компонента rele
  constructorSDISmallComponent(&(config_array[SDISMALLCOMPONENT]));//подготовка компонента sdi
  constructorSDIBigComponent(&(config_array[SDIBIGCOMPONENT]));//подготовка компонента sdi
  constructorRMTKeySmallComponent(&(config_array[RMTKEYSMALLCOMPONENT]));//подготовка компонента rmt key
  constructorSDI3ColorSmallComponent(&(config_array[SDI3COLORSMALLCOMPONENT]));//подготовка компонента sdi
 // constructorRESDBigComponent(&(config_array[RESDBIGCOMPONENT]));//подготовка компонента esd
//  constructorBASDBigComponent(&(config_array[BASDBIGCOMPONENT]));//подготовка компонента esd
  constructorConfigBigComponent(&(config_array[CONFIGBIGCOMPONENT]));//подготовка компонента config
  constructorGIBigComponent(&(config_array[GIBIGCOMPONENT]));//подготовка компонента gi
  constructorSZSBigComponent(&(config_array[SZSBIGCOMPONENT]));//подготовка компонента szs
  constructorCGSBigComponent(&(config_array[CGSBIGCOMPONENT]));//подготовка компонента cgs
  constructorMFTBigComponent(&(config_array[MFTBIGCOMPONENT]));//подготовка компонента mft
  constructorDTRBigComponent(&(config_array[DTRBIGCOMPONENT]));//подготовка компонента dtr
  constructorTSSmallComponent(&(config_array[TSSMALLCOMPONENT]));//подготовка компонента ts
  constructorTSBigComponent(&(config_array[TSBIGCOMPONENT]));//подготовка компонента ts
  constructorTUSmallComponent(&(config_array[TUSMALLCOMPONENT]));//подготовка компонента tu
  constructorTUBigComponent(&(config_array[TUBIGCOMPONENT]));//подготовка компонента tu
  constructorANDBigComponent(&(config_array[ANDBIGCOMPONENT]));//подготовка компонента and
  constructorORBigComponent(&(config_array[ORBIGCOMPONENT]));//подготовка компонента or
  constructorXORBigComponent(&(config_array[XORBIGCOMPONENT]));//подготовка компонента xor
  constructorNOTBigComponent(&(config_array[NOTBIGCOMPONENT]));//подготовка компонента not
  constructorCommonSmallComponent(&(config_array[COMMONSMALLCOMPONENT]));//подготовка компонента common
  constructorCommonBigComponent(&(config_array[COMMONBIGCOMPONENT]));//подготовка компонента common
  constructorMEBigComponent(&(config_array[MEBIGCOMPONENT]));//подготовка компонента me
  constructorRegBigComponent(&(config_array[REGBIGCOMPONENT]));//подготовка компонента reg
  constructorRPRBigComponent(&(config_array[RPRBIGCOMPONENT]));//подготовка компонента rpr
  constructorRPRSmallComponent(&(config_array[RPRSMALLCOMPONENT]));//подготовка компонента rpr
  constructorKEYSmallComponent(&(config_array[KEYSMALLCOMPONENT]));//подготовка компонента key
  constructorAISmallComponent(&(config_array[AISMALLCOMPONENT]));//подготовка компонента ai
  constructorPKVBigComponent(&(config_array[PKVBIGCOMPONENT]));//подготовка компонента pkv
  constructorIUSmallComponent(&(config_array[IUSMALLCOMPONENT]));//подготовка компонента iu
  constructorYustBigComponent(&(config_array[YUSTBIGCOMPONENT]));//подготовка компонента yust
  constructorRPOBigComponent(&(config_array[RPOBIGCOMPONENT]));//подготовка компонента rpo
}//global_vareiables_installation_bo(void)

/**************************************/
//Подготовка компонентов после конфигурации
/**************************************/
/*
void global_component_prepared(void) {
//  config_array[DVBIGCOMPONENT].setCountObject(128);//подготовка компонента ДВ
//  config_array[DVSMALLCOMPONENT].setCountObject(128);//подготовка компонента ДВ

//  config_array[DOUTBIGCOMPONENT].setCountObject(100);//подготовка компонента rele
//  config_array[DOUTSMALLCOMPONENT].setCountObject(100);//подготовка компонента rele

//  config_array[SDIBIGCOMPONENT].setCountObject(21);//подготовка компонента sdi
//  config_array[SDISMALLCOMPONENT].setCountObject(21);//подготовка компонента sdi

  config_array[TSBIGCOMPONENT].setCountObject(22);//подготовка компонента ts
  config_array[TSSMALLCOMPONENT].setCountObject(22);//подготовка компонента ts

  config_array[TUBIGCOMPONENT].setCountObject(23);//подготовка компонента tu
  config_array[TUSMALLCOMPONENT].setCountObject(23);//подготовка компонента tu

  config_array[GIBIGCOMPONENT].setCountObject(24);//подготовка компонента gi

  config_array[SZSBIGCOMPONENT].setCountObject(25);//подготовка компонента szs

  config_array[MFTBIGCOMPONENT].setCountObject(26);//подготовка компонента mft

  config_array[DTRBIGCOMPONENT].setCountObject(27);//подготовка компонента dtr

  config_array[ANDBIGCOMPONENT].setCountObject(28);//подготовка компонента and
  config_array[ORBIGCOMPONENT].setCountObject(29);//подготовка компонента or
  config_array[XORBIGCOMPONENT].setCountObject(30);//подготовка компонента xor
  config_array[NOTBIGCOMPONENT].setCountObject(31);//подготовка компонента not
}//global_vareiables_installation_bo(void)
*/
