#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "platform.h"

#define MAKE_YUYV_VALUE(y,u,v)  ((y) << 24) | ((u) << 16) | ((y) << 8) | (v)
#define YUYV_BLACK                  MAKE_YUYV_VALUE(0,128,128)

#include "SAT070CP50_1024x600.h"

int sstar_panel_init(MI_DISP_Interface_e eType)
{
    MI_PANEL_LinkType_e eLinkType;
    MI_DISP_PubAttr_t stDispPubAttr;
    MI_DISP_InputPortAttr_t stInputPortAttr;

    if (E_MI_DISP_INTF_LCD == eType)
    {
        stDispPubAttr.stSyncInfo.u16Vact       = stPanelParam.u16Height;
        stDispPubAttr.stSyncInfo.u16Vbb        = stPanelParam.u16VSyncBackPorch;
        stDispPubAttr.stSyncInfo.u16Vfb        = stPanelParam.u16VTotal - (stPanelParam.u16VSyncWidth +
                                                 stPanelParam.u16Height + stPanelParam.u16VSyncBackPorch);
        stDispPubAttr.stSyncInfo.u16Hact       = stPanelParam.u16Width;
        stDispPubAttr.stSyncInfo.u16Hbb        = stPanelParam.u16HSyncBackPorch;
        stDispPubAttr.stSyncInfo.u16Hfb        = stPanelParam.u16HTotal - (stPanelParam.u16HSyncWidth +
                                                  stPanelParam.u16Width + stPanelParam.u16HSyncBackPorch);
        stDispPubAttr.stSyncInfo.u16Bvact      = 0;
        stDispPubAttr.stSyncInfo.u16Bvbb       = 0;
        stDispPubAttr.stSyncInfo.u16Bvfb       = 0;
        stDispPubAttr.stSyncInfo.u16Hpw        = stPanelParam.u16HSyncWidth;
        stDispPubAttr.stSyncInfo.u16Vpw        = stPanelParam.u16VSyncWidth;
        stDispPubAttr.stSyncInfo.u32FrameRate  = stPanelParam.u16DCLK * 1000000 / (stPanelParam.u16HTotal * stPanelParam.u16VTotal);
        stDispPubAttr.eIntfSync                = E_MI_DISP_OUTPUT_USER;
        stDispPubAttr.eIntfType                = E_MI_DISP_INTF_LCD;
        stDispPubAttr.u32BgColor               = YUYV_BLACK;

        eLinkType = E_MI_PNL_LINK_TTL;

        MI_DISP_SetPubAttr(0, &stDispPubAttr);
        MI_DISP_Enable(0);
        MI_DISP_BindVideoLayer(0, 0);
        MI_DISP_EnableVideoLayer(0);

        memset(&stInputPortAttr, 0, sizeof(MI_DISP_InputPortAttr_t));
        stInputPortAttr.u16SrcWidth             = PANEL_MAX_W;
        stInputPortAttr.u16SrcHeight            = PANEL_MAX_H;
        stInputPortAttr.stDispWin.u16X          = 0;
        stInputPortAttr.stDispWin.u16Y          = 0;
        stInputPortAttr.stDispWin.u16Width      = PANEL_MAX_W;
        stInputPortAttr.stDispWin.u16Height     = PANEL_MAX_H;

        MI_DISP_SetInputPortAttr(0, 0, &stInputPortAttr);
        MI_DISP_EnableInputPort(0, 0);
        MI_DISP_SetInputPortSyncMode(0, 0, E_MI_DISP_SYNC_MODE_FREE_RUN);

        MI_PANEL_Init(eLinkType);
        MI_PANEL_SetPanelParam(&stPanelParam);
    }
    
    return MI_SUCCESS;
}

int sstar_panel_deinit(MI_DISP_Interface_e eType)
{
    MI_DISP_DisableInputPort(0, 0);
    MI_DISP_DisableVideoLayer(0);
    MI_DISP_UnBindVideoLayer(0, 0);
    MI_DISP_Disable(0);

    switch(eType)
    {
        case E_MI_DISP_INTF_VGA:
            break;

        case E_MI_DISP_INTF_LCD:
            MI_PANEL_DeInit();
            break;

        default: break;
    }

    return MI_SUCCESS;
}

void sstar_getpanel_wh(int *width, int *height)
{
    MI_DISP_PubAttr_t stPubAttr;
    MI_DISP_GetPubAttr(0,&stPubAttr);
    *width = stPubAttr.stSyncInfo.u16Hact;
    *height = stPubAttr.stSyncInfo.u16Vact;
    printf("sstar_getpanel_wh = [%d %d]\n", *width, *height);
}

//调节亮度
int sstar_panel_setluma(uint32_t luma)
{
    if (luma > 100 || luma < 0) {
        printf("parameter error, luma value range [0~100]\n");
        return -1;
    }

    MI_DISP_LcdParam_t stLcdParam;

    MI_DISP_GetLcdParam(0, &stLcdParam);
    printf("get panel luma [%u], set value [%u]\n", stLcdParam.stCsc.u32Luma, luma);

    stLcdParam.stCsc.u32Luma = luma;
    MI_DISP_SetLcdParam(0, &stLcdParam);

    return 0;
}

//调整对比度
int sstar_panel_setcontrast(uint32_t contrast)
{
    if (contrast > 100 || contrast < 0) {
        printf("parameter error, luma value range [0~100]\n");
        return -1;
    }

    MI_DISP_LcdParam_t stLcdParam;

    MI_DISP_GetLcdParam(0, &stLcdParam);
    printf("get panel contrast [%u], set value [%u]\n", stLcdParam.stCsc.u32Contrast, contrast);

    stLcdParam.stCsc.u32Contrast = contrast;
    MI_DISP_SetLcdParam(0, &stLcdParam);

    return 0;
}

int sstar_sys_init(void)
{
    MI_SYS_Version_t stVersion;
    MI_U64 u64Pts = 0;

    MI_SYS_Init();

    memset(&stVersion, 0x0, sizeof(MI_SYS_Version_t));

    MI_SYS_GetVersion(&stVersion);

    MI_SYS_GetCurPts(&u64Pts);

    u64Pts = 0xF1237890F1237890;
    MI_SYS_InitPtsBase(u64Pts);

    u64Pts = 0xE1237890E1237890;
    MI_SYS_SyncPts(u64Pts);

    return MI_SUCCESS;
}

int sstar_sys_deinit(void)
{
    MI_SYS_Exit();
    return MI_SUCCESS;
}


