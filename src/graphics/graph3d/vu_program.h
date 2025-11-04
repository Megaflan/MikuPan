#ifndef MIKUPAN_VU_PROGRAM_H
#define MIKUPAN_VU_PROGRAM_H
#include "sglib.h"

extern unsigned int dma /* __attribute__((section(".vutext"))) */;
extern void DRAWTYPE2() /* __attribute__((section(".vutext"))) */;
extern void DRAWTYPE2W() __attribute__((section(".vutext")));
extern void DRAWTYPE0() __attribute__((section(".vutext")));
extern void MULTI_PROLOGUE() __attribute__((section(".vutext")));

extern SgSourceChainTag SgSu_dma_start() __attribute__((section(".vutext")));
extern SgSourceChainTag SgSuP0_dma_start() __attribute__((section(".vutext")));
extern SgSourceChainTag SgSuP2_dma_start() __attribute__((section(".vutext")));
extern SgSourceChainTag SgSu_dma_starts() __attribute__((section(".vutext")));
extern void DIVP0_PROLOGUE_and_DIVP2_PROLOGUE() __attribute__((section(".vutext")));
extern void MULTIP_PROLOGUE() __attribute__((section(".vutext")));
extern void DP0_PROLOGUE() __attribute__((section(".vutext")));
extern void DP2_PROLOGUE() __attribute__((section(".vutext")));

extern void SHADOWDRAWTYPE0() __attribute__((section(".vutext")));
extern void SHADOWDRAWTYPE2() __attribute__((section(".vutext")));
extern void DIVPS_PROLOGUE() __attribute__((section(".vutext")));
extern void DPS_PROLOGUE() __attribute__((section(".vutext")));


#endif //MIKUPAN_VU_PROGRAM_H