void CBGSig::CalcBusGrSigSchematic(void) {
    register unsigned long  rUl_1,rUl_2;
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
      unsigned int  PO_Inew:1;
      unsigned int  PO_DeltaIbusFix:1;
      unsigned int  PO_DeltaIbusNew:1;
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
    //long  lRamainderNNP, lRamainderNNC;
struct{
long Ii,Ip,Ifix,It_02;
void* pv;
char chNotImp6ms;//,chIdxGrupSamplesFix
}sLV;    
    volatile bool boolWl, boolTzatr;
    wrp.lVl = 0;
    unnBF1.ulVal = 0;
    m_Iteration++;
    
   
//#pragma data_alignment=4 
//    char arChIntermediaResult[(TOTAL_BGS_LU)];
memset(static_cast<void*>(arrOut),0,sizeof(char  )*TOTAL_BGS_VISIO_OUT);
    sLV.pv = static_cast<void*>(CBGSig::measbuf);
    sLV.It_02 = *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (CBGSig::m_chIdxGrupSamples*I_U*1) );   
    
    boolWl = false;    
    do{
        register long i_l, j_l,Ii,Ip;
        i_l = CBGSig::m_chIdxGrupSamples;
        i_l++;
        if(i_l > 2)
            i_l = 0;
        Ip =  *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (i_l*I_U*1) );//I_U-Means index U- last number
        i_l = CBGSig::m_chIdxGrupSamples;
        if(i_l == 0)
            i_l = 2;
        else i_l--;     
        Ii = *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (i_l*I_U*1) );
    
//        if((chBkpt != 0) && (m_chNumberAnalogChanell==1))
//            asm(
//            "bkpt 1"
//            );
        sLV.Ii = Ii;sLV.Ip = Ip;m_lIti = Ii;
         
        if (Ii > Ip) {
           j_l = Ii - Ip;
        } else {
            j_l = Ip - Ii;
        }
        i_l = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        m_lKcDeltaIy = i_l;
        i_l*=9;i_l/=10;//i *    
        if (j_l > i_l) {//Novyi New-made
            if(m_chDeltaIBus == 0 ){//if(m_chDeltaIBus == 0){
                wrp.bool_vars.PO_DeltaIbus = true;sLV.Ifix = Ip;m_chDeltaIBus = 1;
            }else{
                m_chDeltaIBus = 0;
            }    
        }
        else{
            i_l = CBGSig::m_chIdxGrupSamples;
            Ip =  *(static_cast<long*>(sLV.pv)+m_chNumberAnalogChanell+ (i_l*I_U*1) );
            //ArrBGSigDbgRec[uiIdxArrBGSigDbgRec].luIt_02 = sLV.Ip;
            sLV.Ip = Ip;
            if (Ii > Ip) {
                j_l = Ii - Ip;
            } else {
                j_l = Ip - Ii;
            }
            i_l = m_lKcDeltaIy;
            i_l*=9;i_l/=10;
            if (j_l > i_l) {//Novyi New-made
                //if(m_chDeltaIBus != i_l){
                if(m_chDeltaIBus == 0){
                    wrp.bool_vars.PO_DeltaIbus = true;sLV.Ifix = Ip;m_chDeltaIBus = 1;
                }else{
                m_chDeltaIBus = 0;
                }
            }else{
                m_chDeltaIBus = 0;//wrp.bool_vars.PO_DeltaIbus = false;// !!! Only for Dbg
            }
            
        }
            
            
       // boolWl = false;    

    }while(boolWl);
    
     
    
    if(TClrTrg(chTzatrState))
        ch_DTrg = 0;//Clear Trigger
    else if (ch_C1 == 0 && (wrp.bool_vars.PO_DeltaIbus) == 1) {
        ch_DTrg = 1;//DTrgInv = !ch_DTrg;
        
    }
    
    //wrp.bool_vars.DTrgInv = !ch_DTrg;
    rUl_2 = (~static_cast<unsigned long>(ch_DTrg))&1;
    //i++;//
    //i &= 1;
    wrp.bool_vars.DTrgInv = rUl_2;
    
    ch_C1 = wrp.bool_vars.PO_DeltaIbus;
    rUl_1 = (TElongation(wrp.bool_vars.DTrgInv));
    rUl_1 &= wrp.bool_vars.PO_DeltaIbus;
    //if(i && wrp.bool_vars.PO_DeltaIbus){
    if(rUl_1 != 0 && chTzatrState == 0){
        if (m_chWRIfix == 0) {//chTzatrState == 0 <-This is early code chahged to chTzatrState
                //m_lIfix =  sLV.Ip;//!????
                m_lIfix = sLV.Ifix; 
                m_chWRIfix = 1;
                m_lInew = sLV.Ii;//m_lIti
                wrp.bool_vars.PO_Ifix = true;
            };
    }else{
        ;//Clr Ifix Module
        m_chWRIfix = 0;//wrp.bool_vars.PO_Ifix = false;
    }
    
    if (ch_DTrg == 1 ) {//&& wrp.bool_vars.PO_Ifix
        long i_l,j_l, Iti;
        //!????Iti = measurement[m_chNumberAnalogChanell];<<== Error//
        Iti = sLV.Ii;
        if (Iti > m_lIfix) {
            j_l = Iti - m_lIfix;
        } else {
            j_l = m_lIfix - Iti;
        }
        i_l = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        i_l *=9; i_l/=10;
        if (j_l > i_l){
            wrp.bool_vars.PO_DeltaIbusFix = rUl_1 = 1;//i_l = 1;
        }    
        else
            rUl_1 = 0;
        if (Iti > m_lInew) {
            j_l = Iti - m_lInew;
        } else {
            j_l = m_lInew - Iti;
        }
        i_l = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
        i_l *=9; i_l/=10;
        if (j_l > i_l){
            wrp.bool_vars.PO_DeltaIbusNew = 1;//i_l = 1;
        }    
        else
            rUl_2 = 0;
        //if(rUl_2 == 0 && rUl_1 == 0)
        //asm(
        //       "bkpt 1"
        //       );
        
    
    }
    
    rUl_1 = wrp.bool_vars.PO_DeltaIbusFix;
    rUl_1 |= wrp.bool_vars.PO_DeltaIbusNew;
    rUl_2 = (~rUl_1)&1;
    unnBF1.ushAr[0] |= (rUl_2) << BGS_NOT7_STATE_BIT;
    
    
    
    rUl_1 = (lTWait(rUl_1));
    //if()
    unnBF1.ulVal |= (rUl_1)<< BGS_TWAIT_STATE_BIT;
    chTzatrState = rUl_1;
    rUl_2 &= ch_DTrg;//(unnBF1.ulVal&( 1<< BGS_NOT7_STATE_BIT)) && ch_DTrg==1; 
    
    if(TClrTrg(rUl_1|rUl_2))
        ch_DTrg = 0;//Clear Trigger
        
    
    rUl_1 = ( 1<< BGS_TWAIT_STATE_BIT);
    rUl_1 &= unnBF1.ulVal;
    rUl_2 =  (TImp6ms(rUl_1));
    //Inversion cmd
    rUl_1 = (~rUl_2)&1;
    unnBF1.ulVal |= rUl_1 << BGS_NOT26_STATE_BIT;
    sLV.chNotImp6ms = rUl_1;
    //if((unnBF1.ulVal&( 1<< BGS_TWAIT_STATE_BIT))&& m_chWRIp == 0){
    boolTzatr = chTzatrState;

    if( boolTzatr && m_chWRIp == 0){
        long  lRamainderNNP, lRamainderNNC;
        m_lIp = m_lIfix;
        //m_lIc = measurement[m_chNumberAnalogChanell];//!???
        m_lIc = sLV.Ii;
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
        rUl_1 = 0;
        long d = m_lNNC - m_lNNP;
        if (d > 0){
            if(sLV.chNotImp6ms){
                rUl_1 = 1;
            }
        }else{
            rUl_2 = d;
        }
        rUl_2 =  (TImpNNP(rUl_1));
        arrOut[BGS_OUT_NAME_NNP - 1] = rUl_2;
        rUl_1 = 0;
        d = m_lNNP - m_lNNC;
        if (d > 0){
            if(sLV.chNotImp6ms){
                rUl_1 = 1;
            }
            
        }
        rUl_2 =  (TImpNNM(rUl_1));    
        arrOut[BGS_OUT_NAME_NNM - 1] = rUl_2;
        if (m_lNNC >= 1){
        
            arrOut[BGS_OUT_NAME_CC - 1] = 1;
        }    
        arrOut[BGS_OUT_NAME_NNC_INF-1] = m_lNNC;
        

        
        if (m_BGSigSuit.chCheckBgs > 0){
            rUl_2 = m_lKcDeltaIy;//(m_lKcDeltaIy*58981)>>16;
            rUl_2 *= 9;rUl_2 /= 10;
            
            if (measurement[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rUl_2) ){//!???
                m_chStdpCE = 1;
            }
            else{
                rUl_2 *= 11;rUl_2 /= 10;
                if( (measurement[m_chNumberAnalogChanell] <= static_cast<unsigned long>(rUl_2))//!??? 
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
        
        
        
        if (measurement[m_chNumberAnalogChanell] > 2000){//!???
            m_chStdpOV = 1;
            
        }
        else{
            if( (m_chStdpOV == 1) && (measurement[m_chNumberAnalogChanell] > 1800) )//!???
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
    
   rUl_2 = 0;
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNP -1])<<( GROUP_ALARM_OUT_NNP%8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_NNM -1])<<( GROUP_ALARM_OUT_NNM%8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_CC  -1])<<( GROUP_ALARM_OUT_CC %8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_OC  -1])<<( GROUP_ALARM_OUT_OC %8);
    rUl_2 |= static_cast<bool>(arrOut[BGS_OUT_NAME_CE  -1])<<( GROUP_ALARM_OUT_CE %8);
    pLN_GROUP_ALARM->active_state[(GROUP_ALARM_OUT_OC /8) ] = rUl_2;
    pLN_GROUP_ALARM->NNC = 0;
    if(m_BGSigSuit.chStateGS){
         rUl_1 = m_lNNC;
        if(m_lNNC < 0)
            pLN_GROUP_ALARM->NNC = 0;//arrOut[BGS_OUT_NAME_NNC_INF-1];
        else
            pLN_GROUP_ALARM->NNC = rUl_1;//arrOut[BGS_OUT_NAME_NNC_INF-1];
    }    
    rUl_2 = 0;
    
    if(m_chStateTWait)
        rUl_2 |= 1;
   if(m_chStateTReset)
        rUl_2 |= 1<<1;//Be Careful you don`t difer bits of each LU
    if( (m_chSttElongation&3) != 3)
        rUl_2 |= 1<<2;
    if(m_chStt6MsImp)
        rUl_2 |= 1<<3;
    if(m_chSttImpNNP)
        rUl_2 |= 1<<4;
    if(m_chSttImpNNM)
        rUl_2 |= 1<<5;        
    rUl_1 = CBGSig::chNeedTimerCalculated;
    if(rUl_2>0)
        rUl_1 |= 1<<shShemasOrdNumStng;
    else
        rUl_1 &= ~(1<<shShemasOrdNumStng);
    CBGSig::chNeedTimerCalculated = rUl_1;//It`s Need for Call recalc because Timer work

}