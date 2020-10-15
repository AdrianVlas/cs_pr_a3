https://github.com/AdrianVlas/cs_pr_a3
https://github.com/AdrianVlas/cs_pr_a3.git
index//
Shematic::EvalSizeObj
p_param = &(((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index]);

            unsigned int id_input   = (param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;//Тип Функціонального блоку
            unsigned int n_input    = (param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;//Порядковий номер
            unsigned int out_input  = (param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;//Номер виходу
n_input_GOOSE_block;   
n_input_MMS_block;                 
n_network_output_block;            
__LN_INPUT_GOOSE_BLOCK          *pLN_GOOSE;
__LN_INPUT_MMS_BLOCK            *pLN_MMS;
__LN_NETWORK_OUTPUT_BLOCK       *pLN_LAN;             
locRef_CLUMms     
     "Goose__1_8_Op(void *)","Mms__2_8_Op(void *)","Lan__9_8_Op(void *)"

void Shematic::DoCalcLU(void) {

    register long i, j;
    register void* pv;

    struct {
        //long lId,lsizeobj;
        short shAmountCalcLU, shRes;
        void *pV;
        LUAreaListElem* arrLUAreaListElem;
        CLUBase* pCLUBase;
    } sLV;
    sLV.shAmountCalcLU = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    i = 0;
    
}

Блок для QT, щоб управляти файлом
QFile file("M:/test.doc");
if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
{
    ui->label->setText("Bad.");
    return;
}
else
{
    ui->label->setText("Good!");
    while(!file.atEnd())
    {
        QByteArray line = file.read(8).toHex();
       // ui->textEdit->setText(line.toHex());
       qDebug()<<line;
    }
}
//---------------------------------------------------------------

#include <QFile>
#include <QDataStream>
#include <QMessageBox>
QFile *myBinaryFile = new QFile(qApp->applicationDirPath() + "/myDataFile.dat" );
myBinaryFile->open(QIODevice::WriteOnly);
QDataStream binaryDataStream(myBinaryFile);
binaryDataStream.setVersion(QDataStream::Qt_5_9);
binaryDataStream << Qstring("This is a teast...");
myBinaryFile->close();
myBinaryFile->deleteLater();
QMessageBox::information(thsis,"Information","Binary file created",QMessageBox::OK);
    

vector<int> vec_d{ 10, 20, 30, 40 };
vector<int> list;
std::vector<double> collection{ 1.0, 3.5, 0.5, 7.2 };
std::vector<char> letters{ 'a', 'b', 'c' };

You can read this statement as “for each int n in vec, std::cout << n << '',” The colon (:)
therefore is pronounced “in.”
To represent the snake in memory, we thus need to keep track of its velocity and an ordered list of the
It's difficult to get a good feel for how iterators work without having a sense of how all the pieces fit together <-CS106A

Listing 11.10 (twodimvector.cpp) experiments with 2D vectors and takes advantage of the using type
alias statement to simplify the code <--©2017 Richard L. Halterman

When you declare a Vector variable, it starts out as an empty vector<-Eric S. Roberts

Representing Relationships with map  'if (keywords.count(word))' <-full Course
Розділи всі елементи на такі, стан яких фіксується при обрахунку і такі стан яких не фіксується(входи, генератори, ТУ, ТС)
У решти фіксується. Вводимо поле копія станів. В кінці функції обрахунку стану
елементу порівняти стан попередній і наявний. Якщо різні

Для надійності користувач, ще міг би вказати і порядок обробки елементів.
Для обрахунку зворотніх зв`язків міг би ще вказати і кількість ітерацій обходу
для кожного елемента. Щоб 1)даремно його не обраховувати 2)Коли є необхідність певні елементи
крутити декілька разів. При цьому перевіряти чи змінюються виходи і відповідно йде перехід в стаціонарний
стан.

G:\emb_pj\CS_Demo\demo3\cs_61850_A2\working files\v_A_shm\FixBlWrp.cpp
//    if(l&(1<<FIX_BLOCK_SCHEME_INCORRECT)){
//        rCFixBlockWrp.arrOut[SHCEMATIC_FAULT_CMD]          = 1;
//    }
//    else{
//        rCFixBlockWrp.arrOut[SHCEMATIC_FAULT_CMD]          = 0;
//    }
Для чого закоментовано?

G:\emb_pj\CS_Demo\demo3\cs_61850_A2\working files\v_A_shm\LUAlt.cpp

#if (SH_CLU_PULSE_ALTERNATOR_X_Y_AMT_IN > 0)  зроблено для сумісності з "класичним" ЦС, ну і якшо колись з"являться входи
  pIn = static_cast<void*>(arrPchIn);
#endif 

G:\emb_pj\CS_Demo\demo3\cs_pr_a\Device-2.12.x.y\working files\v_A_shm\LUAlt.hpp
const short shCLUPulseAlternator_x_y_AmtIn  = 0; 
char* arrPchIn[shCLUPulseAlternator_x_y_AmtIn ]; у 7.50 компілятор дозволяв такий запис і
сам контролював/викидав поле.
У 8.ХХ Довелося робити, бо компілятор забороняв


#define SH_CLU_PULSE_ALTERNATOR_X_Y_AMT_IN 0
const short shCLUPulseAlternator_x_y_AmtOut = 1;
const short shCLUPulseAlternator_x_y_AmtIn  = SH_CLU_PULSE_ALTERNATOR_X_Y_AMT_IN;


#if (SH_CLU_PULSE_ALTERNATOR_X_Y_AMT_IN > 0)
    char* arrPchIn[shCLUPulseAlternator_x_y_AmtIn ]; //
    
#endif   

G:\emb_pj\CS_Demo\demo3\cs_61850_A2\working files\v_A_shm\Schem_O.cpp
^^---|
void* Shematic::LUSelectorRV( long lIdxLU){//Selector Return Value
register void* pv;
register LUAreaListElem*pLUAreaListElem;
#pragma calls=  Mft_Op, XOR_Op_8_1,TU_Op,DTRG_Op_4_2,OR_Op_8_1,NOT_Op_1_1,LssOp,Log_Op,SET_LED_Op,FKey_Op,SET_OUT_Op,READ_DI_Op,BGSig_Op,AND_Op_8_1,PulseAlt_Op
pLUAreaListElem = static_cast<LUAreaListElem*>(this->pLUAreaList);
pv = (pLUAreaListElem[lIdxLU]).pvLU;
(static_cast<CLUBase*>( pv))->LogicFunc( pv);
    return pv;
}
#define MAX_AMOUNT_LINK_ITERATION 3
//Optimization Module Nazar
void Shematic::DoCalcLU_V01(void){
register union {
long* pLOrderCalcNum;
short* pShOrderCalcNum;
char  *pCh;
}P;
long lAmtProcessObj,lIdxCounter;
long i,l;
void* pv;
    struct {
    
    short shMarkerIteration;
    short shLocalIdxCounter;
    short shCounterLocalIteration;
    void *pV;
    LUAreaListElem* arrLUAreaListElem;
    CLUBase* pCLUBase;//SelectorCurrElem
//      bool bbStateChange;
    char chLUNumOut;
    short shLUStateOut,shLUStateOutChk;
    
      
    } sLV;
//?    TmrCalls();    
//?    UpdateStateDI();
if(chStateOptimisation == 1)
   asm volatile(
       "bkpt 1"
       );
       sLV.arrLUAreaListElem = static_cast<LUAreaListElem*>(this->pLUAreaList);
       //pLUAreaList = static_cast<void*>(&gLUAreaMem.headLUAreaList);
       sLV.shLocalIdxCounter = sLV.shMarkerIteration = sLV.shCounterLocalIteration = 0;
       sLV.chLUNumOut = sLV.shLUStateOutChk = sLV.shLUStateOut = 0;
    //DoCalcLUSources(); <- This function make Nazar Prg
    //P.pCh = const_cast<char*>(arrChCalcLUOrderNumsSchmPage2);
    P.pCh = static_cast<char*>(pExecSeq);

    //lAmtProcessObj = sizeof(arrChCalcLUOrderNumsSchmPage2)>>1;
    lAmtProcessObj = (shSizeExecSeq >> 2) - 1;
    lIdxCounter = 0;
    do {
         
         sLV.shLocalIdxCounter = lIdxCounter;
         i = P.pShOrderCalcNum[0] - 1;//Num Convert to Index
         l = P.pShOrderCalcNum[1]; 
//        j = i >> 8;//        i &= 0xff;//        i += arIdxLUAreaListElem[j-1];
        if (l>0){//Save State Outs
            pv = (sLV.arrLUAreaListElem[i]).pvLU;
            sLV.chLUNumOut = static_cast<CLUBase*>( pv)->chNumOutput;
            for (long lii = 0; lii < sLV.chLUNumOut;lii++)
            sLV.shLUStateOut |= static_cast<char*>((static_cast<CLUBase*>( pv)->pOut))[lii] << lii;
            //Read Out
        }
        pv = LUSelectorRV(i);
        if( l == 0 ){//|| sLV.shLocalIdxCounter == lIdxCounter
            lIdxCounter++;
            P.pLOrderCalcNum ++;//= lIdxCounter;
        }
        else{
            //Fix State            
            for (long lii = 0; lii < sLV.chLUNumOut;lii++)
            sLV.shLUStateOutChk |= static_cast<char*>((static_cast<CLUBase*>( pv)->pOut))[lii] << lii;
            
            if(sLV.shLUStateOutChk != sLV.shLUStateOut){
                long j = sLV.shLocalIdxCounter + 1;
                sLV.pV = static_cast<void*>(P.pCh);
                P.pLOrderCalcNum = &(static_cast<long*>(pExecSeq))[j];
                
                //
                while( j < lAmtProcessObj && P.pShOrderCalcNum[1] == l ){
                    pv = LUSelectorRV(j);
                    j++;
                    P.pLOrderCalcNum ++;//= j;
                }
                //Check State
                if(sLV.shMarkerIteration != lIdxCounter){
                    sLV.shCounterLocalIteration = 0;
                    sLV.shMarkerIteration = lIdxCounter;
                    
                }
                else{
                    sLV.shCounterLocalIteration++;
                    if(sLV.shCounterLocalIteration  > MAX_AMOUNT_LINK_ITERATION)
                        while(1);//Fix Fault
                        //Later insert in program Error
                        //Fix Schematic Error
                }
                P.pCh = static_cast<char*>(sLV.pV);//Restore pointer
                
            }
            else{//Defacto this is (state_curr_el == el(i)) 
                lIdxCounter++;
                P.pLOrderCalcNum = (static_cast<long*>(pExecSeq))+lIdxCounter;
                
            }
        }
        
        
        
        
        
    } while (lIdxCounter < lAmtProcessObj );
    
//    i = arIdxLUAreaListElem[LU_OUTPUT-1];
//    LUIterator((static_cast<__CONFIG* >(p_current_config_prt))->n_output,i);//


}
^^---  Ці зміни -- для підтримки алгоритму Назара
G:\emb_pj\CS_Demo\demo3\cs_61850_A2\working files\v_A_shm\I_Shm.c
void CheckingDIRegs(void) <<-- Очевидно, що для якоЇ - сь перевірки станів входів
для дослідження чи пошуків чогось.
Зараз Реально немає в вихідній програмі. Зараз незрозуміло для чого вона задумувалась.
Бо не зафіксовано жодного сліду використання. Судячи по коду якийсь реєстратор стану
дискретних входів.

G:\emb_pj\CS_Demo\demo3\cs_61850_A2\working files\v_A_shm\Shematic.h 

	void* pExecSeq;  Для алгоритму Назара зберігає вказівник на розміщену в пам"яті
	зону, де зберігається масмв послідовність обрахунку елементів схеми
    char chSumNTUPlusNLAN; Для "базового" чи "класичного" алгоритму обрахунку схеми

    short shIdxSumNTUPlusNLANSeq;

	short shSizeExecSeq;

public:
    Shematic(void);

    void DoCalcLU_V01(void);

    void* LUSelectorRV( long lIdxLU);

    long AllocateObj(void*pvObjImage);





