#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "mi_common.h"
#include "mi_common_datatype.h"

#include "mi_sys.h"
#include "mi_sys_datatype.h"

#include "mi_disp.h"
#include "mi_disp_datatype.h"

#include "config.h"


#include "mi_panel.h"
#include "mi_panel_datatype.h"

#define  PANEL_MAX_W        1024
#define  PANEL_MAX_H        600



int sstar_panel_init(MI_DISP_Interface_e eType);
int sstar_panel_deinit(MI_DISP_Interface_e eType);

int sstar_hdmi_init(MI_DISP_Interface_e eType);
int sstar_hdmi_deinit(MI_DISP_Interface_e eType);

void sstar_getpanel_wh(int *width, int *height);
int sstar_panel_setluma(uint32_t luma);
int sstar_panel_setcontrast(uint32_t contrast);

int sstar_sys_init(void);
int sstar_sys_deinit(void);


#endif

