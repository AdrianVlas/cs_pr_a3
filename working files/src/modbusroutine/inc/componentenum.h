#ifndef __COMPONENTENUM_H
#define __COMPONENTENUM_H

enum {
 DVBIGCOMPONENT          ,//0
 DVSMALLCOMPONENT        ,//1
 DOUTSMALLCOMPONENT      ,//2
 DOUTBIGCOMPONENT        ,//3
 SDISMALLCOMPONENT       ,//4
 SDIBIGCOMPONENT         ,//5
 CONFIGBIGCOMPONENT      ,//6
 GIBIGCOMPONENT          ,//7
 CGSBIGCOMPONENT         ,//8
 SZSBIGCOMPONENT         ,//9
 MFTBIGCOMPONENT         ,//10
 DTRBIGCOMPONENT         ,//11
 TSSMALLCOMPONENT        ,//12
 TSBIGCOMPONENT          ,//13
 TUSMALLCOMPONENT        ,//14
 TUBIGCOMPONENT          ,//15
 ANDBIGCOMPONENT         ,//16
 ORBIGCOMPONENT          ,//17
 XORBIGCOMPONENT         ,//18
 NOTBIGCOMPONENT         ,//19
 COMMONSMALLCOMPONENT    ,//20
 COMMONBIGCOMPONENT      ,//21
 MEBIGCOMPONENT          ,//22
// REGBIGCOMPONENT         ,//23
 RPRBIGCOMPONENT         ,//23
 RPRSMALLCOMPONENT       ,//24
 KEYSMALLCOMPONENT       ,//25
 RMTKEYSMALLCOMPONENT    ,//26
 AISMALLCOMPONENT        ,//27
 PKVBIGCOMPONENT         ,//28
 IUSMALLCOMPONENT        ,//29
 YUSTBIGCOMPONENT        ,//30
// RPOBIGCOMPONENT         ,//32
 REGPROBIGCOMPONENT      ,//31
 TOTAL_COMPONENT         ,//32

 MARKER_OUTPERIMETR   = 100000,
 MARKER_ERRORPERIMETR = 100001,
 MARKER_ERRORDIAPAZON = 100002,
};

//���� �-�� ������ � ���������
#define MAXIMUMI 5
//���� ������ ������ ������
#define MAXIMUMTW 128

#endif
