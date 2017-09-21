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
//  constructorSDI3ColorSmallComponent(&(config_array[SDI3COLORSMALLCOMPONENT]));//подготовка компонента sdi
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
  constructorRegProBigComponent(&(config_array[REGPROBIGCOMPONENT]));//подготовка компонента regPro
  constructorRPRBigComponent(&(config_array[RPRBIGCOMPONENT]));//подготовка компонента rpr
  constructorRPRSmallComponent(&(config_array[RPRSMALLCOMPONENT]));//подготовка компонента rpr
  constructorKEYSmallComponent(&(config_array[KEYSMALLCOMPONENT]));//подготовка компонента key
  constructorAISmallComponent(&(config_array[AISMALLCOMPONENT]));//подготовка компонента ai
  constructorPKVBigComponent(&(config_array[PKVBIGCOMPONENT]));//подготовка компонента pkv
  constructorIUSmallComponent(&(config_array[IUSMALLCOMPONENT]));//подготовка компонента iu
  constructorYustBigComponent(&(config_array[YUSTBIGCOMPONENT]));//подготовка компонента yust
//  constructorRPOBigComponent(&(config_array[RPOBIGCOMPONENT]));//подготовка компонента rpo
}//global_vareiables_installation_bo(void)

