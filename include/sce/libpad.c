#include "libpad.h"

int scePadPortOpen(int port, int slot, void* addr)
{
    return 1;
}

int scePadInit(int mode)
{
    return 1;
}

int scePadGetState(int port, int slot)
{
    /// TODO : Implement PAD
    return scePadStateDiscon;
}

int scePadRead(int port, int slot, unsigned char* rdata)
{
}

int scePadInfoMode(int port, int slot, int term, int offs)
{
}

int scePadSetMainMode(int port, int slot, int offs, int lock)
{
}

int scePadInfoAct(int port, int slot, int actno, int term)
{
}

int scePadSetActAlign(int port, int slot, const unsigned char* data)
{
}

int scePadGetReqState(int port, int slot)
{
}

int scePadInfoPressMode(int port, int slot)
{
}

int scePadEnterPressMode(int port, int slot)
{
}

int scePadSetActDirect(int port, int slot, const unsigned char* data)
{
}
