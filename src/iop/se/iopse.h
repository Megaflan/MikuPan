#ifndef IOPSE_H_
#define IOPSE_H_
#include "os/eeiop/eeiop.h"
#include "typedefs.h"
#include <SDL3/SDL_audio.h>

enum GHOST_SE_ID {
    SG000_HENREI = 0,
    SG001_JYOREI = 1,
    SG002_SAKKA = 2,
    SG003_DUMMY = 3,
    SG004_MAYOIGO1 = 4,
    SG005_DUMMY = 5,
    SG006_DUMMY = 6,
    SG007_DUMMY = 7,
    SG008_DUMMY = 8,
    SG009_KOMUSO = 9,
    SG010_DUMMY = 10,
    SG011_DUMMY = 11,
    SG012_DUMMY = 12,
    SG013_DUMMY = 13,
    SG014_DUMMY = 14,
    SG015_DUMMY = 15,
    SG016_DUMMY = 16,
    SG017_DUMMY = 17,
    SG018_TENAGA = 18,
    SG019_DUMMY = 19,
    SG020_KAMIONNA = 20,
    SG021_KUBI = 21,
    SG022_DUMMY = 22,
    SG023_DUMMY = 23,
    SG024_DUMMY = 24,
    SG025_DUMMY = 25,
    SG026_DUMMY = 26,
    SE_GHOST_ID_MAX = 27
};


typedef struct { // 0x10
    /* 0x0 */ unsigned int adrs;
    /* 0x4 */ short unsigned int attribute;
    /* 0x6 */ short unsigned int pitch;
    /* 0x8 */ short unsigned int adsr1;
    /* 0xa */ short unsigned int adsr2;
    /* 0xc */ char efct;
    /* 0xd */ char vol;
    /* 0xe */ char pan;
} SE_PARAM;

typedef struct { // 0x20
    /* 0x00 */ SE_PARAM* param;
    /* 0x00 */ unsigned int attribute;
    /* 0x08 */ short int v_no;
    /* 0x0a */ short int prm_no;
    /* 0x0c */ short unsigned int pitch;
    /* 0x0e */ short unsigned int vol_l;
    /* 0x10 */ short unsigned int vol_r;
    /* 0x12 */ short unsigned int adsr1;
    /* 0x14 */ short unsigned int adsr2;
    /* 0x16 */ short unsigned int tgt_vol_l;
    /* 0x18 */ short unsigned int tgt_vol_r;
    /* 0x1a */ char inc_vol_l;
    /* 0x1b */ char inc_vol_r;
    /* 0x1c */ unsigned char buf_no;

    SDL_AudioStream *stream;
} SE_WRK_SET;

typedef struct { // 0x32
    /* 0x00 */ short int btlhit;
    /* 0x02 */ short int voice;
    /* 0x04 */ short int door[3];
    /* 0x0a */ short int foot[8];
    /* 0x1a */ short int srund[2];
    /* 0x1e */ short int ghost[3];
    /* 0x24 */ short int event[2];
    /* 0x28 */ short int wide;
    /* 0x2a */ short int jidou[4];
} SE_START_POINT;

enum SE_VOICE_STAT {
    VOICE_FREE = 0,
    VOICE_USE = 1,
    VOICE_LOOP = 2,
    VOICE_RESERVED = 3
};

extern u_int se_start_flg;
extern u_int se_stop_flg;

extern u_int snd_buf_top[];

void ISeInit(int mode);
void ISeCmd(IOP_COMMAND* icp);
void ISeMain();

u_int SeGetSndBufTop(int pos);
void SeSetStartPoint(u_char type, u_int no);
int ICdvdTransSeEnd();
void SeSetMasterVol(u_short mvol);

SE_PARAM * SeGetSeParamTbl(int num);
int GetSeAdrs(int se_no);

#endif // IOPSE_H_