https://github.com/AdrianVlas/cs_pr_a3
https://github.com/AdrianVlas/cs_pr_a3.git
index//
p_param = &(((__LN_TIMER*)spca_of_p_prt[ID_FB_TIMER - _ID_FB_FIRST_VAR] + (number_logical_node - 1))->settings.param[index]);

            unsigned int id_input   = (param >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;//Тип Функціонального блоку
            unsigned int n_input    = (param >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;//Порядковий номер
            unsigned int out_input  = (param >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;//Номер виходу
0x200001C9 0x2000A8CA
   [LSS_OUT_NAME_ALARM]         
   [LSS_OUT_NAME_MUTE ]
   Set Lss == 20 && bft == 20
   And 2 on 1 Led =
   Not 1 on 1 Led
   And 2 on 1BGS
   Not 1 no 1BGS
   D-TRG as BIN
   or 1Timer 1Or 1D-Trg 1Not + 2 And as Bin
   1Timer 1Or 1D-Trg 1Not + 2 And as BSS
   4- Bss 19-20 BIN 
   Typical Situation (4+20)* 1Timer 1Or 1D-Trg 1Not + 2 And
5-8
enum PBGS_BIT_POS { 

m_chSttElongation = m_chStt6MsImp = 0;
m_chSttImpNNP = m_chSttImpNNM = 0;





,
BGS_TMR_3U0_STATE_BIT,
TOTAL_BGS_BITS//30
//LU_GEN_OP_EV_FIX_IBUS
};

void CBGSig::CalcBusGrSigSchematic(void) {
    register long  rl_Val,i;
//    register unsigned long u32_bit_hld1 = 0;  
    union 
	{
		unsigned char   uchAr [4];
		unsigned short  ushAr [2];
        unsigned long   ulVal;
	}unnBF1;//,unnBF2;
 union { //register
   struct {
      unsigned int  PO_DeltaIbus: 1;
	  unsigned int  DTrgInv:1;
	  unsigned int  PO_Ifix:1;
	  unsigned int  PO_DeltaIbusFix:1;
	  unsigned int  Delay1ms:1;
	  unsigned int  Imp6ms :1;
	  unsigned int  PoIp:1;
	  unsigned int  PoIc:1;
	  unsigned int  PO_NNC_NCH:1;
	  unsigned int  PO_NNP_NCH:1;
	  unsigned int  PO_NNC_CH :1;
	  unsigned int  PO_NNP_CH :1;
      
   } bool_vars;
  long lVl;
  
}wrp;
    long  lRamainderNNP, lRamainderNNC;
struct{
long Ii,Ip;
//long k;
}sLV;    
    volatile bool boolWl;
    wrp.lVl = 0;
    unnBF1.ulVal = 0;
//#pragma data_alignment=4 
//    char arChIntermediaResult[(TOTAL_BGS_LU)];
memset(static_cast<void*>(arrOut),0,sizeof(char  )*TOTAL_BGS_VISIO_OUT);
    
    do{
        register long i_l, i_j,Ii,Ip;
        i_l = CBGSig::m_chIdxGrupSamples;
        Ip =  *(static_cast<long*>(CBGSig::measbuf)+m_chNumberAnalogChanell+ (i_l*I_U*1) );
        if(i_l == 0)
            i_l = 2;
        else i_l--;     
        Ii = *(static_cast<long*>(CBGSig::measbuf)+m_chNumberAnalogChanell+ (i_l*I_U*1) );
    
//        if((chBkpt != 0) && (m_chNumberAnalogChanell==1))
//            asm(
//            "bkpt 1"
//            );
        sLV.Ii = Ii;sLV.Ip = Ip;
        if (Ii > Ip) {
           j_l = Ii - Ip;
        } else {
            j_l = Ip - Ii;
        }
        i_l = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        m_lKcDeltaIy = i_l;
        i_l*=9;i_l/=10;//i *    
        if (j_l > i_l) {//Novyi New-made
            wrp.bool_vars.PO_DeltaIbus = true;
        }
        else{
            i_l = CBGSig::m_chIdxGrupSamples;
            i_l++;
            if(i_l > 2)
            i_l = 0;
            Ip =  *(static_cast<long*>(CBGSig::measbuf)+m_chNumberAnalogChanell+ (i_l*I_U*1) );
            
            sLV.Ip = Ip;
            if (Ii > Ip) {
                j_l = Ii - Ip;
            } else {
                j_l = Ip - Ii;
            }
            i_l = m_lKcDeltaIy;
            i_l*=9;i/=10;
            if (j_l > i_l) {//Novyi New-made
            wrp.bool_vars.PO_DeltaIbus = true;
            }else{
                //wrp.bool_vars.PO_DeltaIbus = false;// !!! Only for Dbg
            }
            
        }
            
            
        boolWl = false;
    }while(boolWl);
    
    
    if (ch_C1 == 0 && (wrp.bool_vars.PO_DeltaIbus) == 1) {
        ch_DTrg = 1;//DTrgInv = !ch_DTrg;
    }
    wrp.bool_vars.DTrgInv = !ch_DTrg;
    ch_C1 = wrp.bool_vars.PO_DeltaIbus;
    i = TElongation(DTrgInv);
    if(i && wrp.bool_vars.PO_DeltaIbus){
        if (m_chWRIfix == 0) {
                m_lIfix =  sLV.Ip;
                m_chWRIfix = 1;
                wrp.bool_vars.PO_Ifix = true;
            };
    }else{
        ;//Clr Ifix Module
        m_chWRIfix = 0;//wrp.bool_vars.PO_Ifix = false;
    }
    if (ch_DTrg == 1 && wrp.bool_vars.PO_Ifix) {
        long i_l,j_l, Iti;
        Iti = measurement[m_chNumberAnalogChanell];
        if (Iti > m_lIfix) {
            j_l = Iti - m_lIfix;
        } else {
            j_l = m_lIfix - Iti;
        }
        i_l = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        i_l *=9; i_l/=10;
        if (j_l > i_l){
            wrp.bool_vars.PO_DeltaIbusFix = i = 1;//i_l = 1;
        }    
        else
            i = 0;
    
    }
    unnBF1.ushAr[0] |= (!i) << BGS_NOT7_STATE_BIT;
    
    
	rl_Val = lTWait(i);
    //if()
    unnBF1.ulVal |= (rl_Val!=0)<< BGS_TWAIT_STATE_BIT;
    
    i = (unnBF1.ulVal&( 1<< BGS_NOT7_STATE_BIT)) 
    && ch_DTrg==1; 
    
    if(lTClrTrg(i||rl_Val))
        ch_DTrg = 0;//Clear Trigger
    i= unnBF1.ulVal&( 1<< BGS_TWAIT_STATE_BIT)
    rl_Val = lTImp6ms((i!=0));
    //wrp.bool_vars.Imp6ms = rl_Val;
    unnBF1.ulVal |= (!rl_Val)<< BGS_NOT26_STATE_BIT;
    if((unnBF1.ulVal&( 1<< BGS_TWAIT_STATE_BIT))&& m_chWRIp == 0){
        m_lIp = m_lIfix;
        m_lIc = measurement[m_chNumberAnalogChanell];
        m_lIcMulUnom  = m_lIc*lU_NOM;
        m_lIpMulUnom  = m_lIp*lU_NOM;
        m_lIyMulU     = m_BGSigSuit.lIust * measurement[4];
        
        m_lNNC = ( m_lIcMulUnom )/(m_lIyMulU);//(m_lKcDeltaIy);
        m_lNNP = ( m_lIpMulUnom )/(m_lIyMulU);//(m_lKcDeltaIy);
        
        lRamainderNNC   = (m_lIcMulUnom) % m_lIyMulU;  //lRamainderNNC  = m_lIc % (m_lKcDeltaIy);
        if(lRamainderNNC>=(m_lIyMulU>>1))              //if(lRamainderNNC>=(m_lKcDeltaIy>>1))
            m_lNNC++;                                  //    m_lNNC++;
        lRamainderNNP  =  (m_lIpMulUnom )%(m_lIyMulU); //lRamainderNNP = m_lIp % (m_lKcDeltaIy);
        if(lRamainderNNP>=(m_lIyMulU>>1))              //if(lRamainderNNP>=(m_lKcDeltaIy>>1))
            m_lNNP++;                                  //    m_lNNP++;
        
        if (m_BGSigSuit.chCheckBgs > 0) {
			if(m_lNNC>0)
				m_lNNC--;
			//else{}
			if(m_lNNP>0)
				m_lNNP--;
            
            
        }  

        m_chWRIp = 1;
	
    }
    else {
        if ((unnBF1.ulVal&( 1<< BGS_TWAIT_STATE_BIT)) == 0)
        m_chWRIp = 0;
    }

//   rl_Val = (unnBF1.ulVal&( 1<< )|( 1<< ))!= 0; //OR operation
//   rl_Val = unnBF1.ulVal&(( 1<< )|( 1<< )) == ( 1<< )|( 1<< ); 
//   unnBF1.ulVal |= (rl_Val)<<  
    
    if(m_BGSigSuit.chStateGS){
        rl_Val = m_lNNC - m_lNNP;
        if (rl_Val > 0)
            arrOut[BGS_OUT_NAME_NNP - 1] = 1;
        rl_Val = m_lNNP - m_lNNC;
        if (rl_Val > 0)
            arrOut[BGS_OUT_NAME_NNM - 1] = 1;
        if (m_lNNC >= 1)
            arrOut[BGS_OUT_NAME_CC - 1] = 1;
        arrOut[BGS_OUT_NAME_NNC_INF-1] = m_lNNC;
        

        
        if (m_BGSigSuit.chCheckBgs > 0){
            rl_Val = m_lKcDeltaIy;//(m_lKcDeltaIy*58981)>>16;
            rl_Val *= 9;rl_Val /= 10;
            
            if (measurement[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rl_Val) ){
                m_chStdpCE = 1;
            }
            else{
                rl_Val *= 11;rl_Val /= 10;
                if( (measurement[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rl_Val)) 
                &&  (m_chStdpCE == 1) )
                    m_chStdpCE = 1;
                else
                    m_chStdpCE = 0;
            }
            
            if( m_chStdpCE == 1)
                arrOut[BGS_OUT_NAME_CE - 1] = 1;
            else
                arrOut[BGS_OUT_NAME_CE - 1] = 0;
        }else{
            arrOut[BGS_OUT_NAME_CE - 1] = 0;
        }
        
        
        
        if (measurement[m_chNumberAnalogChanell] > 2000){
            m_chStdpOV = 1;
            
        }
        else{
            if( (m_chStdpOV == 1) && (measurement[m_chNumberAnalogChanell] > 1800) )
                m_chStdpOV = 1;
            else
                m_chStdpOV = 0;
        }
        
        if( m_chStdpOV == 1)
            arrOut[BGS_OUT_NAME_OC  - 1] = 1;
        else
            arrOut[BGS_OUT_NAME_OC  - 1] = 0;
            
    }
    else{
        arrOut[BGS_OUT_NAME_NNP - 1] = 0;
        arrOut[BGS_OUT_NAME_NNM - 1] = 0;
        arrOut[BGS_OUT_NAME_CC  - 1] = 0;
        arrOut[BGS_OUT_NAME_NNC_INF-1] = 0;
        arrOut[BGS_OUT_NAME_CE  - 1] = 0;
        arrOut[BGS_OUT_NAME_OC  - 1] = 0;
    }
    register __LN_GROUP_ALARM *pLN_GROUP_ALARM = static_cast<__LN_GROUP_ALARM *>(pvCfgLN);
    
   rl_Val = 0;
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNP -1])<<( GROUP_ALARM_OUT_NNP%8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNM -1])<<( GROUP_ALARM_OUT_NNM%8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_CC  -1])<<( GROUP_ALARM_OUT_CC %8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_OC  -1])<<( GROUP_ALARM_OUT_OC %8);
    rl_Val |= static_cast<bool>(arrOut[BGS_OUT_NAME_CE  -1])<<( GROUP_ALARM_OUT_CE %8);
    pLN_GROUP_ALARM->active_state[(GROUP_ALARM_OUT_OC /8) ] = rl_Val;
    pLN_GROUP_ALARM->NNC = 0;
    if(m_BGSigSuit.chStateGS){
         i = m_lNNC;
        if(i < 0)
            pLN_GROUP_ALARM->NNC = 0;//arrOut[BGS_OUT_NAME_NNC_INF-1];
        else
            pLN_GROUP_ALARM->NNC = i;//arrOut[BGS_OUT_NAME_NNC_INF-1];
    }    
    rl_Val = 0;
    
    if(m_chStateTWait)
        rl_Val |= 1;
   if(m_chStateTReset)
        rl_Val |= 1<<1;//Be Careful you don`t difer bits of each LU
        
    i = CBGSig::chNeedTimerCalculated;
    if(rl_Val>0)
        i |= 1<<shShemasOrdNumStng;
    else
        i &= ~(1<<shShemasOrdNumStng);
    CBGSig::chNeedTimerCalculated = i;//It`s Need for Call recalc because Timer work

}


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


 