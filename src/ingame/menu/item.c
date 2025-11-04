#include "common.h"
#include "item.h"

void ItemCntInit(void) {
}

void NewgameItemInit()
{
}

void NewgameItemInit2()
{
}

void MissionSelectItemInit()
{
}

void MenuItemInit()
{
}

void LoadgameMenuItemInit()
{
}

void StartItemModeInit()
{
}

void ItemInitAtMenuOpen()
{
}

void FilmPossessionExp()
{
}

void IngameMenuItem()
{
}

void IngameMenuItemUseSlct()
{
}

void IngameMenuItemDisp()
{
}

void PlayerStatusYW(u_char alpha)
{
}

int LoadItem2D(u_char get_type, u_char get_no)
{
}

u_long VramItem2D(u_char mode, u_char type)
{
}

char DspItem2D(u_long tex_addr, float pos_x, float pos_y, int rgb, float alp, float scl_x, float scl_y, char pri)
{
}

void PkTm2(u_long tex_addr, short int pos_x, short int pos_y, short int w, short int h, u_char alp, int pri)
{
}

void PutSpriteYW(u_short top_label, u_short end_label, float pos_x, float pos_y, float rot, int rgb, float alp,
    float scl_x, float scl_y, u_char scl_mode, int pri, u_char by, u_char blnd, u_char z_sw)
{
}

void FlashStarYW(FLSH_CORE* flsh, u_char flsh_max, u_char flsh_min, u_char flsh_flm, u_char mode)
{
}

void CLRtoRGB(int* rgb, u_char r, u_char g, u_char b)
{
}

void RGBtoCLR(int rgb, u_char* r, u_char* g, u_char* b)
{
}

void PutStringYW(u_char msg_knd, u_char msg_no, short int pos_x, short int pos_y, int rgb, u_char alpha, int pri,
                 u_char type)
{
}

void RstMessageYW()
{
}

u_char PutMessageYW(u_char msg_knd, u_char msg_no, short int pos_x, short int pos_y, int rgb, u_char alpha, int pri)
{
}

char ChkChrNumYW(u_char msg_knd, u_char msg_no)
{
}

int ChkChrNumUS(u_char msg_knd, u_char msg_no)
{
}

char ChkPageYW(u_char msg_knd, u_char msg_no)
{
}

void PutPageYW(u_char msg_knd, u_char msg_no, u_char open_page, short int pos_x, short int pos_y, int rgb, u_char alpha,
    int pri)
{
}

void PutPage2YW(u_char msg_knd, u_char msg_no, u_char open_page, short int pos_x, short int pos_y, int rgb,
    u_char alpha, int pri)
{
}

void PutNumberYW(u_char font, int num, short int pos_x, short int pos_y, float sx, float sy, int rgb, short int alpha,
    int pri, int digit, int mode)
{
}

void PolySquareYW(float pos_x, float pos_y, u_short bar_l, u_short bar_h, int rgb, float alp, float scl_x, float scl_y,
    int pri, u_char blnd, u_char sw_z, short int rz)
{
}

void YesNoCrslOKR(int pri, float pos_x, float pos_y, int rgb, float alp, float scl)
{
}

void XYAdefaultYW(u_char no)
{
}

void BgFusumaYW(int rgb, float pos_x, float alpha, int pri)
{
}

u_int FromPKZ(u_int pkz_addr, u_char pk2_no)
{
}

void DcdCMP2PK2(u_int cmp_addr, u_int tmp_addr)
{
}
