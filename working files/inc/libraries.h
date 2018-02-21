#ifndef __LIBRARIES_H
#define __LIBRARIES_H

#pragma section = "variables_RAM1"

#include "stm32f2xx.h"
#include "stm32f2xx_it.h"
#include "platform_config.h"
#include "hw_config.h"
#include "macroses.h"

#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"

#include  <intrinsics.h>
#include <stdbool.h>
#include <math.h>
#include <arm_math.h>
#include <stdlib.h>

#ifdef SYSTEM_VIEWER_ENABLE
#include "SEGGER_SYSVIEW.h"
#endif


#endif
