#ifndef __CONST_CHOOSE_COMMUNICATION_PARAMETERS_MENU2__
#define __CONST_CHOOSE_COMMUNICATION_PARAMETERS_MENU2__

enum __index_choose_comunication_parameters
{
  INDEX_CHCP_M2_NAME = 0,
  INDEX_CHCP_M2_SETTING_RS485,
  INDEX_CHCP_M2_SETTING_ETHERNET,
  
  MAX_ROW_CHCP_M2
};

#define MAX_ROW_FOR_VIEW_NAME_OF_CELL                (MAX_CHAR_IN_NAME_OF_CELL >> POWER_MAX_COL_LCD)

enum __index_choose_settings_RS485
{
  INDEX_CHSRS485_M2_PHY_LAYER = 0,
  INDEX_CHSRS485_M2_PROTOCOL,
  
  MAX_ROW_CHSRS485_M2
};

enum __index_phy_layer_RS485
{
  INDEX_PHY_LAYER_RS485_M2_BAUD = 0,
  INDEX_PHY_LAYER_RS485_M2_PARE,
  INDEX_PHY_LAYER_RS485_M2_STOP,
  INDEX_PHY_LAYER_RS485_M2_TIMEOUT,
  
  MAX_ROW_PHY_LAYER_RS485_M2
};

#define MAX_ROW_FOR_VIEW_BAUD_RS485                     1
#define MAX_ROW_FOR_VIEW_PARE_RS485                     1
#define MAX_ROW_FOR_VIEW_STOP_BITS_RS485                1
#define MAX_ROW_FOR_VIEW_TIMEOUT_RS485                  1


#define COL_TIMEOUT_RS485_BEGIN    3
#define COL_TIMEOUT_RS485_COMMA    5
#define COL_TIMEOUT_RS485_END      6

enum __index_protocol_RS485
{
  INDEX_PROTOCOL_RS485_M2_ADDRESS = 0,
  
  MAX_ROW_PROTOCOL_RS485_M2
};

#define MAX_ROW_ADDRESS_M2              1

#define COL_ADDRESS_BEGIN                6
#define COL_ADDRESS_END                  8

enum __index_choose_settings_Ethernet
{
  INDEX_CHSETH_M2_NETWORK_LAYER = 0,
  
  MAX_ROW_CHSETH_M2
};

enum __index_settings_network_layer_Ethernet
{
  INDEX_SNLETH_M2_IPV4 = 0,
  INDEX_SNLETH_M2_MASK,
  INDEX_SNLETH_M2_GATEWAY,
  
  MAX_ROW_SNLETH_M2
};

#define COL_IP4_GATEWAY_BEGIN           1
#define COL_IP4_GATEWAY_END             MAX_COL_LCD

#define COL_MASK_BEGIN                 7
#define COL_MASK_END                   8

#endif
