#include "common.h"
#include "plyr_ctl.h"

u_short photo_dmg_tbl[0];
/* sdata 357300 */ u_char plyr_vib_time;

void PlyrCtrlMain()
{
}

int PlyrDoorOpenChk()
{
}

u_char ShortPauseChk()
{
}

void PlyrCondChk()
{
}

void PlyrDmgChk()
{
}

void PlyrVibCtrl(u_char time)
{
}

void PlyrFinderModeChk()
{
}

void FinderInSet()
{
}

void FinderEndSet()
{
}

void ClrEneSta()
{
}

void PlyrHeightCtrl(float* tv)
{
}

void PlyrNormalCtrl()
{
}

void PlyrSpotMoveCtrl()
{
}

void PlyrFinderCtrl()
{
}

void PlyrCamRotCngChk()
{
}

void EneHPchk()
{
}

void FModeScreenEffect()
{
}

void PlyrDmgCtrl()
{
}

u_char LeverGachaChk()
{
}

void PlyrFinderEnd()
{
}

void PlyrNAnimeCtrl()
{
}

void SetPlyrAnime(u_char anime_no, u_char frame)
{
}

void PlyrTrembleChk()
{
}

void ReqPlyrHPdown(u_short deg, u_char prio)
{
}

void PlyrHPdwonCtrl()
{
}

void PlyrSpotLightOnChk()
{
}

void SetPlyrSpotLight(u_char id)
{
}

void PlyrSubAtkChk()
{
}

u_char PSAchk0()
{
}

u_char PSAchk1()
{
}

u_char PSAchk3()
{
}

u_char PSAchk2()
{
}

void PSAchk4(u_char id)
{
}

void PSAchk5()
{
}

void PlyrPhotoChk()
{
}

void EneFrameHitChk()
{
}

void PlyrChargeCtrl(u_char req)
{
}

void PhotoFlyChk()
{
}

int FrameInsideChk(float* tv, float* tx, float* ty)
{
}

int FrameInsideChkFurn(float* degree, u_int fsta)
{
}

int FrameInsideChkRare(int wrk_no, float* degree)
{
}

u_short PhotoDmgChk()
{
}

u_short PhotoDmgChkSub()
{
}

void PhotoPointSet()
{
}

void PhotoPointChkEne()
{
}

void PhotoPointChkFurn()
{
}

void PhotoPointChkRare()
{
}

void PhotoPointCulcEne()
{
}

void PhotoPointCulcFurn(float dist, float degree, u_int stts)
{
}

void PhotoPointCulcRare(u_char wrk_no, float dist, float degree)
{
}

void PlyrMpRecoverChk(u_int recov)
{
}

void PlyrFModeMoveCtrl()
{
}

void PlyrActionChk()
{
}

void PlyrNModeMoveCtrl()
{
}

void PlyrHitTurnChk(float* tv)
{
}

u_char PlyrSpecialMoveChk2(float* mv)
{
}

void PlyrSpecialMoveChk(float* mv)
{
}

void PlyrPosSet(float* tv)
{
}

void PlyrKonwakuMove(float* tv)
{
}

void PlyrMovePad(float* tv)
{
}

void GetMoveSpeed(float* tv)
{
}

void PlyrMovePadV(float* tv)
{
}

void CngPlyrRotRapid(float rot0)
{
}

void PlyrMovePadFind(float* tv)
{
}

float GetMovePad(u_char id)
{
}

int MovePadEnableChk(u_char* dir_save)
{
}

void PadInfoTmpSave(u_char* dir_save, u_char dir_now, float* rot_save, float rot_now)
{
}

u_char PlyrMoveStaChk(float pad_chk)
{
}

u_int PlyrLeverInputChk()
{
}

u_char PlyrMoveHitChk(float* tv, u_char id)
{
}

void InitPhotoWrk()
{
}

void InitSubjectWrk()
{
}

void PlyrBattleChk()
{
}

void PlyrLightSet()
{
}

void PlyrMessageDisp()
{
}

int ReqPlyrSpeAnime(u_char anime_no, u_char frame)
{
}

void PlyrSpeAnimeCtrl()
{
}

void PlyrDWalkTmCtrl()
{
}

float GetEnePowerDegree()
{
}

float CulcEP(float* v0, float* v1)
{
}

float CulcEP2(float* v0, float* v1)
{
}

int ChkPhotoAble()
{
}

int SearchRareEne()
{
}

int SearchFurnHint()
{
}

int GetFurnHintPos(float* tv, u_int* fsta)
{
}

float GetPlyrSpd()
{
}

int PlyrNeckDirectionChk(float* p)
{
}

u_char NeckTargetEneChk(float* p)
{
}

u_char NeckTargetItemChk(float* p)
{
}

u_char NeckTargetDoorChk(float* p)
{
}

u_char PlyrNoticeObjectChk(float* ov, float* dist)
{
}

void ReqPlayerStop(u_char frame)
{
}

void PlayerWarpReq(u_char dat_no)
{
}

int PlayerWarpCtrl()
{
}

void PlayerWarpRoomLoadReq()
{
}

int ShutterChanceChk()
{
}

void PlayerWarpReq2(u_char dat_no)
{
}
