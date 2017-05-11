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



 