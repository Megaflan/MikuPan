#ifndef MIKUPAN_MEMORY_ADDRESSES_H
#define MIKUPAN_MEMORY_ADDRESSES_H

#include <stdint.h>

extern unsigned char ps2_virtual_ram[1024*1024*64];
extern unsigned char ps2_virtual_scratchpad[1024*16];

int64_t MikuPan_GetHostAddress(int offset);
void* MikuPan_GetHostPointer(int offset);
void MikuPan_InitPs2Memory();
int MikuPan_IsPs2MemoryPointer(int64_t address);
int MikuPan_ConvertHostToPs2MemoryOffset(void* ptr);
int MikuPan_SanitizePs2Address(int address);
int MikuPan_IsPs2AddressMainMemoryRange(int address);
int MikuPan_GetPs2OffsetFromHostPointer(void* ptr);

#define FontTextAddress     0x01e30000
//extern void* FontTextAddress; #define PK2 font texture pack

#define ImgHdAddress        0x012f0000
//extern void* ImgHdAddress; #define IMG_HD.BIN

#define IG_MSG_OBJ_ADDRESS  0x0084a000
//extern void* IG_MSG_OBJ_ADDRESS; #define

#define EFFECT_ADDRESS      0x01e90000
//extern void* EFFECT_ADDRESS; #define

// #define PBUF_ADDRESS        0x00720000
//extern void* PBUF_ADDRESS; #define Packet buffer

/// 10682368
#define SPRITE_ADDRESS 0xa30000
//extern void* SPRITE_ADDRESS;

#define PL_BGBG_PK2_ADDRESS 0x1d05140
//extern void* PL_BGBG_PK2_ADDRESS;

#define PL_STTS_PK2_ADDRESS 0x1ce0000
//extern void* PL_STTS_PK2_ADDRESS;

#define PL_PSVP_PK2_ADDRESS 0x1d59630
//extern void* PL_PSVP_PK2_ADDRESS;

#define PL_SAVE_PK2_ADDRESS 0x1d15600
//extern void* PL_SAVE_PK2_ADDRESS;

#define SV_PHT_PK2_ADDRESS 0x1d28c80
//extern void* SV_PHT_PK2_ADDRESS;

#define M_SLCT_CMN_PK2_ADDRESS 0xc80000
//extern void* M_SLCT_CMN_PK2_ADDRESS;

#define M_SLCT_STY_PK2_ADDRESS 0xcc0470
//extern void* M_SLCT_STY_PK2_ADDRESS;

#define PL_OPTI_PK2_ADDRESS 0xddc430
//extern void* PL_OPTI_PK2_ADDRESS;

#define M_SLCT_BTL_CHR_PK2_ADDRESS 0xd4a850
//extern void* M_SLCT_BTL_CHR_PK2_ADDRESS;

#define M_SLCT_BTL_MSN_PK2_ADDRESS 0xdcb100
//extern void* M_SLCT_BTL_MSN_PK2_ADDRESS;

#define PL_SMAP_PK2_ADDRESS 0x1e05b00
//extern void* PL_SMAP_PK2_ADDRESS;

#define PL_PLAY_PK2_ADDRESS 0x1e2f700
//extern void* PL_PLAY_PK2_ADDRESS;

#define PL_PLDT_PK2_ADDRESS 0x1d266c0
//extern void* PL_PLDT_PK2_ADDRESS;

#define PL_MTOP_PK2_ADDRESS 0x1d15600
#define N_LOAD_PK2_ADDRESS 0x1f1c000
#define HAND_PK2_ADDRESS 0x1fc8000
#define PL_FNDR_PK2_ADDRESS 0x1d88100
#define PL_LIFE_PK2_ADDRESS 0x1df2100
#define ENEDMG_PK2_ADDRESS 0x1fa8000
#define PHOTO001_PK2_ADDRESS 0x1e85000
#define TEST2D_PK2_ADDRESS 0x04300000
#define TEST_ROOM_CHECK_ADDRESS 0x04610000
#define MPEG_WORK_ADDRESS 0x14b0000
#define MISSION_TITLE_CARD_ADDRESS 0x1e90000
#define PLYR_FILE_ADDRESS 0x9a0000
#define PL_ALBM_FSM_PK2_ADDRESS 0x0c80000
#define PL_ALBM_SIDE_1_ADDRESS 0x1dc8570
#define PL_PHOT_PK2_ADDRESS 0x1d573b0
#define PLAYER_ANM_ADDRESS 0x870000
//extern void* PLAYER_ANM_ADDRESS;
//extern void* PLYR_FILE_ACS_ADDRESS;
//extern void* PLYR_FILE_BWC_ADDRESS;
//extern void* PLYR_FILE_CLT_ADDRESS;
#define ENE_DMG_TEX_ADDRESS 0xac8000
#define SCENE_LOAD_ADDRESS 0x1090000
#define MSN_TITLE_DAT_ADDRESS 0x7F0000
#define MSN_TITLE_DAT_ADDRESS_1 (0x7E0000)
#define MSN_TITLE_DAT_ADDRESS_2 (0x7F8000)
#define MSN_TITLE_DAT_ADDRESS_3 (0xE00000)
#define MSN_TITLE_DAT_ADDRESS_4 (0xE80000)
#define MSN_TITLE_DAT_ADDRESS_5 (0xC40000)
#define MSN_TITLE_DAT_ADDRESS_6 (0xC4C000)
#define MSN_TITLE_DAT_ADDRESS_7 (0xC58000)
#define MSN_TITLE_DAT_ADDRESS_8 (0x1000000)
#define MSN_TITLE_DAT_ADDRESS_9 (0x1020000)

#define VNBufferAddress     0x00420000
#define CachedBuffer        0x20000000
#define UnCachedBuffer      0x30000000
#define VU0_ADDRESS         0x11000000
#define MC_WORK_ADDRESS     0x00420000



#endif //MIKUPAN_MEMORY_ADDRESSES_H