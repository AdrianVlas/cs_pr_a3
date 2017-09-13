//#include <QtWidgets>
//#include "loghandler.h"

#include "variables_external_m.h"

/**************************************/
//��������� ������������� �����������
/**************************************/
void global_component_installation(void) {
  constructorDVBigComponent(&(config_array[DVBIGCOMPONENT]));//���������� ���������� ��
  constructorDVSmallComponent(&(config_array[DVSMALLCOMPONENT]));//���������� ���������� ��
  constructorDOUTSmallComponent(&(config_array[DOUTSMALLCOMPONENT]));//���������� ���������� rele
  constructorDOUTBigComponent(&(config_array[DOUTBIGCOMPONENT]));//���������� ���������� rele
  constructorSDISmallComponent(&(config_array[SDISMALLCOMPONENT]));//���������� ���������� sdi
  constructorSDIBigComponent(&(config_array[SDIBIGCOMPONENT]));//���������� ���������� sdi
  constructorRMTKeySmallComponent(&(config_array[RMTKEYSMALLCOMPONENT]));//���������� ���������� rmt key
//  constructorSDI3ColorSmallComponent(&(config_array[SDI3COLORSMALLCOMPONENT]));//���������� ���������� sdi
 // constructorRESDBigComponent(&(config_array[RESDBIGCOMPONENT]));//���������� ���������� esd
//  constructorBASDBigComponent(&(config_array[BASDBIGCOMPONENT]));//���������� ���������� esd
  constructorConfigBigComponent(&(config_array[CONFIGBIGCOMPONENT]));//���������� ���������� config
  constructorGIBigComponent(&(config_array[GIBIGCOMPONENT]));//���������� ���������� gi
  constructorSZSBigComponent(&(config_array[SZSBIGCOMPONENT]));//���������� ���������� szs
  constructorCGSBigComponent(&(config_array[CGSBIGCOMPONENT]));//���������� ���������� cgs
  constructorMFTBigComponent(&(config_array[MFTBIGCOMPONENT]));//���������� ���������� mft
  constructorDTRBigComponent(&(config_array[DTRBIGCOMPONENT]));//���������� ���������� dtr
  constructorTSSmallComponent(&(config_array[TSSMALLCOMPONENT]));//���������� ���������� ts
  constructorTSBigComponent(&(config_array[TSBIGCOMPONENT]));//���������� ���������� ts
  constructorTUSmallComponent(&(config_array[TUSMALLCOMPONENT]));//���������� ���������� tu
  constructorTUBigComponent(&(config_array[TUBIGCOMPONENT]));//���������� ���������� tu
  constructorANDBigComponent(&(config_array[ANDBIGCOMPONENT]));//���������� ���������� and
  constructorORBigComponent(&(config_array[ORBIGCOMPONENT]));//���������� ���������� or
  constructorXORBigComponent(&(config_array[XORBIGCOMPONENT]));//���������� ���������� xor
  constructorNOTBigComponent(&(config_array[NOTBIGCOMPONENT]));//���������� ���������� not
  constructorCommonSmallComponent(&(config_array[COMMONSMALLCOMPONENT]));//���������� ���������� common
  constructorCommonBigComponent(&(config_array[COMMONBIGCOMPONENT]));//���������� ���������� common
  constructorMEBigComponent(&(config_array[MEBIGCOMPONENT]));//���������� ���������� me
  constructorRegBigComponent(&(config_array[REGBIGCOMPONENT]));//���������� ���������� reg
  constructorRegProBigComponent(&(config_array[REGPROBIGCOMPONENT]));//���������� ���������� regPro
  constructorRPRBigComponent(&(config_array[RPRBIGCOMPONENT]));//���������� ���������� rpr
  constructorRPRSmallComponent(&(config_array[RPRSMALLCOMPONENT]));//���������� ���������� rpr
  constructorKEYSmallComponent(&(config_array[KEYSMALLCOMPONENT]));//���������� ���������� key
  constructorAISmallComponent(&(config_array[AISMALLCOMPONENT]));//���������� ���������� ai
  constructorPKVBigComponent(&(config_array[PKVBIGCOMPONENT]));//���������� ���������� pkv
  constructorIUSmallComponent(&(config_array[IUSMALLCOMPONENT]));//���������� ���������� iu
  constructorYustBigComponent(&(config_array[YUSTBIGCOMPONENT]));//���������� ���������� yust
//  constructorRPOBigComponent(&(config_array[RPOBIGCOMPONENT]));//���������� ���������� rpo
}//global_vareiables_installation_bo(void)

