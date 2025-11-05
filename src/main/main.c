#include "common.h"
#include "typedefs.h"
#include "enums.h"
#include "main.h"

#include <string.h>

#include "main/glob.h"
#include "main/gamemain.h"
#include "outgame/title.h"
#include "os/system.h"
#include "os/eeiop/eeiop.h"
#include "os/eeiop/eese.h"
#include "os/eeiop/se_cmd.h"
#include "graphics/mov/movie.h"
#include "graphics/graph2d/tim2_new.h"
#include "graphics/graph2d/g2d_main.h"
#include "graphics/graph3d/sgdma.h"
#include "graphics/graph3d/gra3d.h"
#include "os/eeiop/adpcm/ea_cmd.h"
// #include "os/eeiop/adpcm/ea_cmd.h"

int sceGsSyncPath(int mode, u_short timeout);

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

/// CPP Extern Functions ///
void InitImGuiWindow(SDL_Window *window, SDL_Renderer *renderer);
void ShutDownImGuiWindow();
void RenderImGuiWindow(SDL_Renderer *renderer);
void DrawImGuiWindow();
void NewFrameImGuiWindow();
void ProcessEventImGui(SDL_Event *event);
/// CPP Extern Functions ///

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("MikuPan", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    InitImGuiWindow(window, renderer);

    /// GAME LOGIC ///
    SDL_Log("Initializing Systems");
    InitSystem();

    SDL_Log("Initializing Game");
    InitGameFirst();

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    ProcessEventImGui(event);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    NewFrameImGuiWindow();
    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

    if (!SoftResetChk())
    {
        if (!PlayMpegEvent())
        {
            EiMain();
            GameMain();
            CheckDMATrans();
            sceGsSyncPath(0, 0);
            vfunc();
            //DrawAll2DMes_P2();
            //FlushModel(1);
            //ClearTextureCache();
            //SeCtrlMain();
        }
    }
    else
    {
        InitGameFirst();
    }

    DrawImGuiWindow();
    RenderImGuiWindow(renderer);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
    ShutDownImGuiWindow();
}

void InitGameFirst()
{
    sys_wrk.reset = 0;
    gra3dInitFirst();
    gra2dInitBG();
    MovieInitWrk();
    realtime_scene_flg = 0;
    sys_wrk.game_mode = GAME_MODE_INIT;
    outgame_wrk.mode = 0;
    outgame_wrk.mode_next = 4;
    memset(&ingame_wrk, 0, sizeof(INGAME_WRK));
    sys_wrk.sreset_ng = 0;
    opening_movie_type = 0;
}

void CallSoftReset()
{
    int lcount;

    lcount = 0;
    
    SeStopAll();
    InitSe();
    SetIopCmdSm(1, 0, 0, 0);
    EAdpcmCmdStop(0, 0, 0);
    
    sys_wrk.reset = 0;
    
    SetSysBackColor(0, 0, 0);
    
    scene_bg_color = 0;
    
    while (1)
    {
        EiMain();
        
        if (EAGetRetStat() == 1 || EAGetRetStat() == 2)
        {
            EAdpcmCmdInit(1);
            break;
        }
        
        lcount++;
        
        if (lcount > 30)
        {
            EAdpcmCmdStop(0, 0, 0);
            lcount = 0;
        }
        
        vfunc();
    }
}

int SoftResetChk()
{
    /// TODO: Re-enable once pad is implemented
    //if (
    //    *key_now[8] && *key_now[9] && *key_now[10] &&
    //    *key_now[11] && *key_now[12] && *key_now[13]
    //)
    //{
    //    // Re-enabled for debug purposes
    //    sys_wrk.sreset_count = 1;
    //}
    //else
    //{
    //    sys_wrk.sreset_count = 0;
    //}
    
    if (sys_wrk.sreset_ng != 0)
    {
        sys_wrk.sreset_count = 0;
    }

    if (sys_wrk.sreset_count >= 60)
    {
        sys_wrk.reset = 1;
    }
    
    if (sys_wrk.reset == 1)
    {
        sys_wrk.sreset_count = 0;
        CallSoftReset();
        return 1;
    }
    
    return 0;
}
