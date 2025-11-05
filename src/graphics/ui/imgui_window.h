#ifndef MIKUPAN_IMGUI_WINDOW_H
#define MIKUPAN_IMGUI_WINDOW_H
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

extern "C" void InitImGuiWindow(SDL_Window *window, SDL_Renderer *renderer);
extern "C" void RenderImGuiWindow(SDL_Renderer *renderer);
extern "C" void NewFrameImGuiWindow();
extern "C" void DrawImGuiWindow();
extern "C" void ShutDownImGuiWindow();
extern "C" void ProcessEventImGui(SDL_Event *event);
#endif //MIKUPAN_IMGUI_WINDOW_H