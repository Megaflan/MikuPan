#include "common.h"

#ifdef MATCHING_DECOMP
#define INCLUDING_FROM_IG_ALBUM_C
#include "ig_album.h"
#undef INCLUDING_FROM_IG_ALBUM_C
#else
#include "ig_album.h"

void NewgameMenuAlbumInit()
{
}

void LoadgameMenuAlbumInit()
{
}

void StartAlbumModeInit()
{
}

void IngameMenuAlbum(char is_outgame)
{
}

void IngameAlbumAllPad(u_char* csr, u_char* csr_top, u_char* mode)
{
}

void IngameAlbumLstPad(u_char* csr, u_char* csr_top, u_char* mode)
{
}

void IngameAlbumBigPad(u_char* csr, u_char* csr_top, u_char* mode)
{
}

void IngameAlbumDispPhotoLarge(u_char csr)
{
}

void IngameAlbumDisp(u_char csr, u_char csr_top, u_char mode, char is_outgame)
{
}

u_char* GetSubjectNameAddr(u_short kind, u_short no, u_short show)
{
}

u_char TimeIsMoney(u_char hexhex)
{
}

u_char MoneyIsTime(u_char time)
{
}

void OutGameInitPhoto()
{
}

int isPhotoEnd()
{
}

float GetPhtDispAlpha()
{
}
#endif
