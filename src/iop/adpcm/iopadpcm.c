#include "iopadpcm.h"
#include "typedefs.h"

void IAdpcmPlay(ADPCM_CMD* acp)
{
    u_char channel = acp->channel;

    if (iop_adpcm[channel].stat == ADPCM_STAT_PRELOAD_END) {
        iop_adpcm[channel].loop_end = 0;
        sceSdSetCoreAttr(iop_adpcm[channel].core | 4, 0);
        IaSetWrkVolPanPitch(channel, acp->pan, acp->vol, acp->pitch);
        IaSetRegVol(channel);
        IaSetRegPitch(channel);
        IaSetRegAdsr(channel);
        IaSetRegSsa(channel);
        sceSdSetTransIntrHandler(channel, AdpcmTransCB, 0);
        sceSdSetSpu2IntrHandler((sceSdSpu2IntrHandler)AdpcmSpu2IntrHander, iop_adpcm);
        sceSdSetAddr(iop_adpcm[channel].core | SD_A_IRQA, (u_int)(AdpcmSpuBuf[channel] + 2048) & 0xFFFFFFF0);
        IaSetRegKon(channel);
        sceSdSetCoreAttr(iop_adpcm[channel].core | 4, 1u);
        iop_adpcm[channel].stat = ADPCM_STAT_PLAY;

        return;
    }
}

void IAdpcmStop(ADPCM_CMD* acp)
{
    u_char channel;

    channel = acp->channel;
    sceSdSetCoreAttr(iop_adpcm[channel].core | 4, 0);
    IaSetWrkFadeInit(channel);

    if (iop_adpcm[channel].stat == ADPCM_STAT_NOPLAY) {
        if (iop_adpcm[channel].use) {
            iop_adpcm[channel].use = 0;
        }
    } else {
        if (iop_adpcm[channel].stat == ADPCM_STAT_PRELOAD) {
            ICdvdBreak();
            iop_adpcm[channel].use = 0;
        } else if (iop_adpcm[channel].stat == ADPCM_STAT_PRELOAD_END) {
            iop_adpcm[channel].use = 0;
        } else {
            if (cdvd_stat.stat == ADPCM_STAT_LOOPEND_STOP)
                ICdvdBreak();
            IaSetRegKoff(channel);
            sceSdSetTransIntrHandler(channel, 0, 0);
            sceSdVoiceTransStatus(channel, 1);
            iop_adpcm[channel].use = 0;
        }
    }

    if (IAdpcmChkCmdExist()) {
        iop_adpcm[channel].stat = ADPCM_STAT_NOPLAY;
    } else {
        iop_adpcm[channel].stat = ADPCM_STAT_NOPLAY;
    }

    iop_adpcm[channel].tune_no = 0;
}

static void IAdpcmFadeVol(IOP_COMMAND* iop) {}

static void IAdpcmPos(IOP_COMMAND* icp)
{
    int channel;

    channel = icp->data3;
    IaSetWrkVolPanPitch(channel, (icp->data5 >> 16) & 0xffff, icp->data5 & 0xffff, icp->data6 & 0xffff);
    IaSetRegVol(channel);
    IaSetRegPitch(channel);
}

static void IAdpcmMvol(IOP_COMMAND* icp)
{
    u_short mvol = icp->data1 & 0xffff;

    IaSetMasterVol(mvol);
}

static void AdpcmSpu2IntrHander(int core_bit, void* data)
{
    IOP_ADPCM* ia = data;

    if (iop_adpcm[0].stat == ADPCM_STAT_PLAY)
        sceSdSetCoreAttr(iop_adpcm[0].core | SD_C_IRQ_ENABLE, 0);

    if (iop_adpcm[1].stat == ADPCM_STAT_PLAY)
        sceSdSetCoreAttr(iop_adpcm[1].core | SD_C_IRQ_ENABLE, 0);

    if ((core_bit & 1) != 0)
        iWakeupThread(ia[0].thread_id);

    if ((core_bit & 2) != 0)
        iWakeupThread(ia[1].thread_id);
}

static int AdpcmTransCB(int channel, void* common)
{
    if (iop_adpcm[channel].stat == ADPCM_STAT_LTRANS) {
        iop_adpcm[channel].pos += 2048;
        iop_adpcm[channel].str_tpos += 2048;
        iop_adpcm[channel].stat = ADPCM_STAT_RTRANS;
        while (sceSdVoiceTrans(
                   channel,
                   0,
                   &AdpcmIopBuf[channel][iop_adpcm[channel].pos],
                   (u_int)((iop_adpcm[channel].dbids * 2048) + AdpcmSpuBuf[channel] + 4096),
                   0x800u)
            < 0)
            ;
    } else if (iop_adpcm[channel].stat == ADPCM_STAT_RTRANS) {
        iop_adpcm[channel].pos += 2048;
        iop_adpcm[channel].str_tpos += 2048;
        sceSdSetAddr(
            iop_adpcm[channel].core | SD_A_IRQA,
            ((u_int)AdpcmSpuBuf[channel] + (iop_adpcm[channel].dbids * 2048)) & 0xFFFFFFF0);
        iop_adpcm[channel].dbids ^= 1u;
        iop_adpcm[channel].stat = ADPCM_STAT_PLAY;
        sceSdSetCoreAttr(iop_adpcm[channel].core | 4, 1u);

        if (iop_adpcm[channel ^ 1].stat >= 4)
            sceSdSetCoreAttr(iop_adpcm[channel ^ 1].core | 4, 1u);
    } else {
    }

    return 1;
}

void IAdpcmReadCh0()
{
    int count = 0;
    int start;
    u_int remain_t;
    u_int remain_l;
    u_short tmp_tune_no;
    ADPCM_CMD cmd;
    u_char loop_ok;

    while (1) {
        SleepThread();
        if (iop_adpcm[0].stat >= ADPCM_STAT_PRELOAD_TRANS) {
            iop_adpcm[0].count++;

            remain_t = iop_adpcm[0].szFile - iop_adpcm[0].str_tpos;
            if (remain_t > 0x1000) {
                if (iop_adpcm[0].pos == (iop_adpcm[0].dbidi + 1) * 0x20000) {
                    remain_l = iop_adpcm[0].szFile - iop_adpcm[0].str_lpos;
                    start = iop_adpcm[0].start;

                    if (remain_l > 0x20000) {
                        iop_adpcm[0].lreq_size = 0x20000;
                        ICdvdLoadReqAdpcm(
                            start,
                            iop_adpcm[0].lreq_size,
                            (u_int*)&AdpcmIopBuf[0][0x20000 * iop_adpcm[0].dbidi],
                            0,
                            2u,
                            0);
                    } else if (remain_l) {
                        iop_adpcm[0].lreq_size = remain_l;
                        ICdvdLoadReqAdpcm(
                            start,
                            iop_adpcm[0].lreq_size,
                            (u_int*)&AdpcmIopBuf[0][0x20000 * iop_adpcm[0].dbidi],
                            0,
                            2u,
                            1u);
                    }

                    if (iop_adpcm[0].dbidi)
                        iop_adpcm[0].pos = 0;

                    iop_adpcm[0].dbidi ^= 1;
                }

                // ????
                if (iop_adpcm[0].stat != ADPCM_STAT_PLAY) {
                }

                if (!sceSdVoiceTransStatus(0, SD_TRANS_STATUS_CHECK))
                    sceSdVoiceTransStatus(0, SD_TRANS_STATUS_WAIT);

                iop_adpcm[0].stat = ADPCM_STAT_LTRANS;

                while (sceSdVoiceTrans(
                           0,
                           0,
                           &AdpcmIopBuf[0][iop_adpcm[0].pos],
                           (u_int)((iop_adpcm[0].dbids * 0x800) + AdpcmSpuBuf[0]),
                           0x800u)
                    < 0) {

                    count++;
                    if (count > 100000)
                        count = 0;
                }
            } else {
                loop_ok = 0;
                if (!IAdpcmChkCmdExist()) {
                    loop_ok = 1;
                }

                cmd.cmd_type = 3;
                cmd.fade_flm = 0;
                cmd.tune_no = 0;
                cmd.channel = 0;
                tmp_tune_no = iop_adpcm[0].tune_no;
                IAdpcmStop(&cmd);
                if (iop_adpcm[0].loop && loop_ok) {
                    if (iop_adpcm[0].fade_mode == ADPCM_FADE_NO) {
                        if (!IAdpcmChkCmdExist()) {
                            cmd.cmd_type = AC_PLAY;
                            cmd.fade_flm = 0;
                            cmd.start_cnt = 0;
                            cmd.tune_no = tmp_tune_no;
                            cmd.vol = iop_adpcm[0].vol;
                            cmd.target_vol = cmd.vol;
                            cmd.pan = iop_adpcm[0].pan;
                            cmd.pitch = iop_adpcm[0].pitch;
                            cmd.loop = 1;
                            cmd.channel = 0;
                            cmd.first = iop_adpcm[0].first;
                            cmd.size = iop_adpcm[0].szFile_bk;
                            now_cmd = cmd;
                        }
                    } else {
                        if (iop_adpcm[0].target_vol && !IAdpcmChkCmdExist()) {
                            cmd.cmd_type = AC_PLAY;
                            cmd.fade_flm = 0;
                            cmd.start_cnt = 0;
                            cmd.tune_no = tmp_tune_no;
                            cmd.vol = iop_adpcm[0].target_vol;
                            cmd.target_vol = cmd.vol;
                            cmd.pan = iop_adpcm[0].pan;
                            cmd.pitch = iop_adpcm[0].pitch;
                            cmd.loop = 1;
                            cmd.channel = 0;
                            cmd.first = iop_adpcm[0].first;
                            cmd.size = iop_adpcm[0].szFile_bk;

                            now_cmd = cmd;
                        }
                    }
                } else {
                    iop_adpcm[0].loop_end = 1;
                }
            }
        } else {
        }
    }
}

void IAdpcmTuneEndStop(u_char channel)
{
    ADPCM_CMD cmd;

    cmd.cmd_type = 3;
    cmd.fade_flm = 0;
    cmd.tune_no = 0;
    cmd.channel = channel;
    IAdpcmStop(&cmd);
}

void IAdpcmTuneEndLoop(u_char channel, u_char fade, u_short tune_no)
{
    ADPCM_CMD cmd;

    cmd.cmd_type = AC_PLAY;
    cmd.fade_flm = 0;
    cmd.start_cnt = 0;
    cmd.tune_no = tune_no;

    if (fade) {
        cmd.vol = iop_adpcm[channel].target_vol;
        cmd.target_vol = cmd.vol;
    } else {
        cmd.vol = iop_adpcm[channel].vol;
        cmd.target_vol = cmd.vol;
    }

    cmd.pan = iop_adpcm[channel].pan;
    cmd.pitch = iop_adpcm[channel].pitch;
    cmd.loop = 1;
    cmd.channel = channel;
    cmd.first = iop_adpcm[channel].first;
    cmd.size = iop_adpcm[channel].szFile_bk;

    now_cmd = cmd;
}

void IAdpcmReadCh1()
{
    int count = 0;
    int start;
    u_int remain_t;
    u_int remain_l;
    u_short tmp_tune_no;
    ADPCM_CMD cmd;
    u_char loop_ok;

    while (1) {
        SleepThread();
        if (iop_adpcm[1].stat >= ADPCM_STAT_PRELOAD_TRANS) {
            iop_adpcm[1].count++;

            remain_t = iop_adpcm[1].szFile - iop_adpcm[1].str_tpos;
            if (remain_t > 0x1000) {
                if (iop_adpcm[1].pos == (iop_adpcm[1].dbidi + 1) * 0x20000) {
                    remain_l = iop_adpcm[1].szFile - iop_adpcm[1].str_lpos;
                    start = iop_adpcm[1].start;

                    if (remain_l > 0x20000) {
                        iop_adpcm[1].lreq_size = 0x20000;
                        ICdvdLoadReqAdpcm(
                            start,
                            iop_adpcm[1].lreq_size,
                            (u_int*)&AdpcmIopBuf[1][0x20000 * iop_adpcm[1].dbidi],
                            1,
                            2u,
                            0);
                    } else if (remain_l) {
                        iop_adpcm[1].lreq_size = remain_l;
                        ICdvdLoadReqAdpcm(
                            start,
                            iop_adpcm[1].lreq_size,
                            (u_int*)&AdpcmIopBuf[1][0x20000 * iop_adpcm[1].dbidi],
                            1,
                            2u,
                            1u);
                    }

                    if (iop_adpcm[1].dbidi)
                        iop_adpcm[1].pos = 0;

                    iop_adpcm[1].dbidi ^= 1;
                }

                // ????
                if (iop_adpcm[1].stat != ADPCM_STAT_PLAY) {
                }

                if (!sceSdVoiceTransStatus(1, SD_TRANS_STATUS_CHECK))
                    sceSdVoiceTransStatus(1, SD_TRANS_STATUS_WAIT);

                iop_adpcm[1].stat = ADPCM_STAT_LTRANS;

                while (sceSdVoiceTrans(
                           1,
                           0,
                           &AdpcmIopBuf[1][iop_adpcm[1].pos],
                           (u_int)((iop_adpcm[1].dbids * 0x800) + AdpcmSpuBuf[1]),
                           0x800u)
                    < 0) {

                    count++;
                    if (count > 100000)
                        count = 0;
                }
            } else {
                loop_ok = 0;
                if (!IAdpcmChkCmdExist()) {
                    loop_ok = 1;
                }

                cmd.cmd_type = 3;
                cmd.fade_flm = 0;
                cmd.tune_no = 0;
                cmd.channel = 1;
                tmp_tune_no = iop_adpcm[1].tune_no;
                IAdpcmStop(&cmd);
                if (iop_adpcm[1].loop && loop_ok) {
                    if (iop_adpcm[1].fade_mode == ADPCM_FADE_NO) {
                        if (!IAdpcmChkCmdExist()) {
                            cmd.cmd_type = AC_PLAY;
                            cmd.fade_flm = 0;
                            cmd.start_cnt = 0;
                            cmd.tune_no = tmp_tune_no;
                            cmd.vol = iop_adpcm[1].vol;
                            cmd.target_vol = cmd.vol;
                            cmd.pan = iop_adpcm[1].pan;
                            cmd.pitch = iop_adpcm[1].pitch;
                            cmd.loop = 1;
                            cmd.channel = 1;

                            now_cmd = cmd;
                        }
                    } else {
                        if (iop_adpcm[1].target_vol && !IAdpcmChkCmdExist()) {
                            cmd.cmd_type = AC_PLAY;
                            cmd.fade_flm = 0;
                            cmd.start_cnt = 0;
                            cmd.tune_no = tmp_tune_no;
                            cmd.vol = iop_adpcm[1].target_vol;
                            cmd.target_vol = cmd.vol;
                            cmd.pan = iop_adpcm[1].pan;
                            cmd.pitch = iop_adpcm[1].pitch;
                            cmd.loop = 1;
                            cmd.channel = 1;

                            now_cmd = cmd;
                        }
                    }
                }
            }
        } else {
        }
    }
}

static void SetLoopFlag(u_int* st_addr, u_int szvag, u_char st_end)
{
    int i;
    u_char* lpflgp = (u_char*)st_addr;

    lpflgp++;
    for (i = 0; i < szvag >> 4; ++i) {
        *lpflgp = 2;
        lpflgp += 16;
    }

    if ((st_end & 2) != 0) {
        lpflgp -= 16;
        *lpflgp |= 1u;
    }

    if ((st_end & 1) != 0) {
        lpflgp = (u_char*)st_addr;
        lpflgp++;
        *lpflgp |= 4;
    }
}

static void SetLoopFlgAll(u_short core)
{
    u_char* pos;
    int i;
    int times;

    pos = 0;
    times = 32;
    for (i = 0; i < times; i++, pos += 0x2000) {
        SetLoopFlag(&AdpcmIopBuf[core][(u_int)pos] + 0x0000, 0x800u, 1u);
        SetLoopFlag(&AdpcmIopBuf[core][(u_int)pos] + 0x0800, 0x800u, 1u);
        SetLoopFlag(&AdpcmIopBuf[core][(u_int)pos] + 0x1000, 0x800u, 2u);
        SetLoopFlag(&AdpcmIopBuf[core][(u_int)pos] + 0x1800, 0x800u, 2u);
    }
}

static void SetLoopFlgAll2(u_short core)
{
    u_char* pos;
    int i;
    int times;

    pos = 0;
    times = 32;
    for (i = 0; i < times; i++, pos += 0x2000) {
        SetLoopFlag(&AdpcmIopBuf[core][(u_int)pos] + 0x0000, 0x800u, 1u);
        SetLoopFlag(&AdpcmIopBuf[core][(u_int)pos] + 0x0800, 0x800u, 1u);
        SetLoopFlag(&AdpcmIopBuf[core][(u_int)pos] + 0x1000, 0x800u, 2u);
        SetLoopFlag(&AdpcmIopBuf[core][(u_int)pos] + 0x1800, 0x800u, 2u);
    }
}

void SetLoopFlgSize(u_int size_byte, u_int* start, u_short core)
{
    int i;
    int j;
    int k;
    int lt0;
    int lt1;
    u_char* lpflgp;

    lpflgp = (u_char*)start;
    lt0 = size_byte / 0x2000;
    lt1 = 0x80;
    lpflgp++;

    for (i = 0; i < lt0; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < lt1; k++) {
                if (!k)
                    *lpflgp = 6;
                else
                    *lpflgp = 2;

                lpflgp += 16;
            }
        }
        for (j = 0; j < 2; j++) {
            for (k = 0; k < lt1; k++) {
                if (k == lt1 - 1)
                    *lpflgp = 3;
                else
                    *lpflgp = 2;

                lpflgp += 16;
            }
        }
    }
}

void IAdpcmLoadEndStream(int channel)
{
    iop_adpcm[channel].str_lpos += iop_adpcm[channel].lreq_size;
    iop_adpcm[channel].start += (iop_adpcm[channel].lreq_size + 2047) / 2048;
}

void IAdpcmLoadEndPreOnly(int channel)
{
    IAdpcmPreLoadEnd(channel);
}