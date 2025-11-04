#include "common.h"

#ifdef MATCHING_DECOMP
#define INCLUDING_FROM_CAMERA_C
#include "mdlwork.h"
#undef INCLUDING_FROM_CAMERA_C
#else
#include "camera.h"

/* sdata 356f1a */ u_char DBG_cam_id_move_chk;

void CameraMain()
{
}

void KonwakuCamCtrl()
{
}

void FinderInCameraCtrl()
{
}

void NormalCameraCtrl()
{
}

int GetCameraInfo(MAP_CAM_INFO* mci)
{
}

void GetCameraData(u_char kind)
{
}

void SetCamPos0(SgCAMERA* tc)
{
}

void SetCamPos1(SgCAMERA* tc)
{
}

void SetCamPos2(SgCAMERA* tc)
{
}

void SetCamPos3(SgCAMERA* tc)
{
}

void SetCamPos4(SgCAMERA* tc)
{
}

void SetCamPos5(SgCAMERA* tc)
{
}

float GetMCLocalPosPer(u_short cn, u_char kind, u_char id)
{
}

void CompleCameraPos(SgCAMERA* tc, SgCAMERA* oc)
{
}

u_char CompleReqChk()
{
}

void FinderModeCameraCtrl()
{
}

void PlyrCamCondChk()
{
}

void PconMahiCameraCtrl()
{
}

void PconTebureCameraCtrl()
{
}

int FinderModePadChk(char* pad_x, char* pad_y, float* ax, float* ay, u_char* jpad_on)
{
}

void SetFinderRot()
{
}

void CameraIdMoveCtrl()
{
}

u_char SetMapCamDat0(MAP_CAM_DAT* mcd)
{
}

u_char SetMapCamDat1(MAP_CAM_DAT* mcd)
{
}

u_char SetMapCamDat2(MAP_CAM_DAT* mcd, u_char id)
{
}

u_char SetMapCamDat3(MAP_CAM_DAT* mcd, u_char id)
{
}

u_char SetMapCamDat4(MAP_CAM_DAT* mcd, u_char id)
{
}

u_char SetMapCamDat5(MAP_CAM_DAT* mcd)
{
}

void SaveCamDat(u_char kind, u_char mn)
{
}

void ReqFinderInOverRap(u_short time)
{
}

void FinderInOverRapCtrl()
{
}

void PlyrDmgCameraCtrl()
{
}

void ReqDramaCamera(u_char req, u_short no, u_short time)
{
}

void DramaCameraReqCtrl()
{
}

void ClearDramaCamReq()
{
}
#endif
