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
    CounterLocalIteration = 0;MarkerIteration = 0;
        int i = 0;
    while(i < N;){
        state_curr_el = el(i); 
        el(i).calc;

        if( (el(i)_link == 0) || (state_curr_el == el(i)) ){
            i++;
        }else{

            j = i + 1;
    
            while( (j<= N) && (el(j)._link == el(i)._link) ){
             el(j).calc;
             j++;
            }
            i = el(i)._link;
            if( MarkerLinkIteration != i ){
                //Start 
                CounterLocalIteration = 0;
                MarkerLinkIteration = i;
            }
            else{
                CounterLocalIteration++;
                if(CounterLocalIteration > MAX_AMOUNT_ITERATION)
                    FixFault;//No Stable State;
            }

        }
    }

}
Рефлізація алгоритму сортування
1)В перший прохід знаходиш максимальне(мінімальне) число. І формуєш список двонаправлений котрий вже на 1 менший
2)Далі проглядаєш вже список. Знайшов максимальне(мінімальне) число -Вставляєш індекс у вже сформований список
і виймаєш його із списку початкових елементів.
Знову продивляєшся список і виймаєш індекс його максимальне(мінімальне)

Для експерименту візьмемо Масив розміром 4,10, 50, 100, 1000.
const short SH_SIZE_ARR = 4;

typedef struct {
//    long lVal;
	long lIdx;
    void *next;
}NodeS;

typedef struct {
    long lVal;
	long lIdx;
    void *next;
	void *prev;
}NodeB; 
 NodeS *pNodeS;
 NodeB *pNodeB,pNodeHead, pNodeTail;
 long arLong[SH_SIZE_ARR];
 NodeS arNodeS[SH_SIZE_ARR];
 NodeB arNodeB[SH_SIZE_ARR];
 NodeB arNodeB[SH_SIZE_ARR];
 
 long lEtalonMax = arLong[0];
 long lEtalonMin = arLong[0];
 
 pNodeS = &arNodeS[0];
// pNodeS->(void *)0;
 
 pNodeB = &arNodeB[0];
 pNodeB ->next = &arNodeB[1];
 pNodeB ->prev = (void*)0;
 pNodeB ->lVal = lEtalonObj;
 pNodeB ->lIdx = 0;
 pNodeHead = &arNodeB[0];
 pNodeTail = 
	for(long i = 1, NodeB *plocNodeB = pNodeB; i++; i<(SH_SIZE_ARR-1)){
		if(arLong[i]< lEtalonObj)
		lEtalonMin = arLong[i];
        //pNextNodeB = &arNodeB[i];
        if(arLong[i]> lEtalonObj)
        lEtalonMax = arLong[i];
		   

		plocNodeB ->lVal = arLong[i];
		plocNodeB ->lIdx = i;
		plocNodeB ->next = &arNodeB[i+1];
		plocNodeB ->prev = &arNodeB[i-1];
		
		
	}
	long lIdx = SH_SIZE_ARR -1;
	pNodeB = &arNodeB[lIdx];
	pNodeTail = pNodeB;
	pNodeB ->next = (void *)0;
	pNodeB ->prev = &arNodeB[lIdx-1];
	pNodeB ->lVal = arLong[i];
	pNodeB ->lIdx = lIdx;
	
    pNodeB =  pNodeHead;
	while(pNodeB ->next){
		if(pNodeB ->lVal < lEtalonObj)
		lEtalonObj = pNodeB ->lVal;
        if(arLong[i]> lEtalonObj)
        lEtalonMax = arLong[i];
	
	
	}
                if ((rsLV.pCLURef->shShemasIdLUStng == static_cast<short>(locSBitFld.bfInfo_IdLUStng)) &&
                        (rsLV.pCLURef->shShemasOrdNumStng == static_cast<short>(locSBitFld.bfInfo_OrdNumStng))
                        ) {//Set UP Logic
                    //rsLV.pCh = static_cast<char*>(rsLV.pCLURef->pOut);
                    //rsLV.pCh += static_cast<unsigned char>(locSBitFld.bfInfo_OrdNumOut - 1); //As Idx
                    rsLV.chVal = 1;
//                     asm volatile(
//                    "bkpt 1"
//                    );
                    break;
                }    
 Попробуй поработать сразу с Max and Min
 Второй список можно привести к масиву индексов
 


