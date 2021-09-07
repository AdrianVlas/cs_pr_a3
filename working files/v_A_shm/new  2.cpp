https://github.com/AdrianVlas/cs_pr_a3
https://github.com/AdrianVlas/cs_pr_a3.git
index//
p_param = &(((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index]);

            unsigned int id_input   = (param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;//Тип Функціонального блоку
            unsigned int n_input    = (param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;//Порядковий номер
            unsigned int out_input  = (param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;//Номер виходу
			
void Mft_Op_dbg(void *pObj){

    register long i, r,j,k;
    //register char* pCh;
    union{
    char  arChEC[4];
    short arrShEC[2];
    long  lEC;
    } U_EC;
    U_EC.lEC = 0;
    CMft& rCMft = *(static_cast<CMft*>(pObj));
     	if(rCMft.shShemasOrdNumStng == chMftCmpVal){
            asm(
            "bkpt 1"
            );
        }
        
    i = static_cast<long>(*(rCMft.arrPchIn[MFT_IN_NAME__MFTIN-1]));
    j = static_cast<long>(*(rCMft.arrPchIn[MFT_IN_NAME__RESET_I-1]));
    
                
    if(CLUBase::m_AuxInfo.ch > 0){
        U_EC.arChEC[0]++;
        //j = static_cast<long>(*(rCMft.arrPchIn[1]));
        if(j == rCMft.arrStateIn[MFT_IN_NAME__RESET_I-1]){
            U_EC.arChEC[0]++;
            if(i == rCMft.arrStateIn[MFT_IN_NAME__MFTIN-1])
                U_EC.arChEC[0]++;
            return;//May be not Operation    
        }    
        
    }
    
    rCMft.arrStateIn[MFT_IN_NAME__MFTIN-1]    = i;
    rCMft.arrStateIn[MFT_IN_NAME__RESET_I-1]  = r = j; 
     

    rCMft.m_chOR3 = j || i;
    //--i = static_cast<long>(*(rCMft.arrPchIn[0]));
    j = rCMft.TPauseMftDir(i);
    //rCMft.m_chOR3 = r || i;// 
    if(rCMft.m_chOR3 != 0){
        
        rCMft.m_D5Q = 0;
    }
    else{
        if((i == 0) &&(rCMft.m_D5_In == 0)){
            rCMft.m_D5Q = 1;
        }
    }
    rCMft.m_D5_In = !i;
    k = rCMft.TPauseMftInv(rCMft.m_D5Q);
    if(j == 1 && rCMft.m_chInPulsDir == 0){
        rCMft.m_chInPulsDir = j;
        U_EC.arChEC[2] = j;
    }
    else{
        if(j == 0)
            rCMft.m_chInPulsDir = j;
        U_EC.arChEC[2] = 0;    
    }
    if(k == 1 && rCMft.m_chInPulsInv == 0){
        rCMft.m_chInPulsInv = k;
        U_EC.arChEC[3] = k;
    }
    else{
        if(k == 0)
            rCMft.m_chInPulsInv = k;
         U_EC.arChEC[3] = 0;    
    }
    i = static_cast<long>(*(rCMft.arrPchIn[1]));//Reset

    rCMft.arrOut[MFT_OUT_NAME__MFT_IMP_DIR_OUT-1] = 
    rCMft.TWorkMftDir(i,U_EC.arChEC[2]);
    rCMft.arrOut[MFT_OUT_NAME__MFT_DEL_OUT-1] = 
    rCMft.TDelayMftDir(i,j);
    rCMft.arrOut[MFT_OUT_NAME__MFT_IMP_INV_OUT-1] = 
    rCMft.TWorkMftInv(i,U_EC.arChEC[3]);
   
register __LN_TIMER *pLN_TIMER = reinterpret_cast<__LN_TIMER*>(rCMft.pvCfgLN);
    i = rCMft.arrOut[MFT_OUT_NAME__MFT_IMP_DIR_OUT-1];
    j = rCMft.arrOut[MFT_OUT_NAME__MFT_DEL_OUT-1]    ;
    k = rCMft.arrOut[MFT_OUT_NAME__MFT_IMP_INV_OUT-1];
    
    pLN_TIMER->active_state[(TIMER_OUT_RISE_IMPULSE /8) ] = i<< ( TIMER_OUT_RISE_IMPULSE %8);
    pLN_TIMER->active_state[(TIMER_OUT_RISE_DELAY /8)   ] = j<< ( TIMER_OUT_RISE_DELAY   %8)  ;
    pLN_TIMER->active_state[(TIMER_OUT_FALL_IMPULSE /8) ] = k<< ( TIMER_OUT_FALL_IMPULSE %8);    
   

    
}