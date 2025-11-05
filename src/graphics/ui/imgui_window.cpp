#include "imgui_window.h"

#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

void InitImGuiWindow(SDL_Window *window, SDL_Renderer *renderer)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void RenderImGuiWindow(SDL_Renderer* renderer)
{
    ImGui::Render();

    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void NewFrameImGuiWindow()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void DrawImGuiWindow()
{
    ImGui::Begin("Hello, world!");
    ImGui::Text("Welcome to Dear ImGui with SDL3!");
    ImGui::End();

    ImGui::ShowDemoWindow();
}

void ShutDownImGuiWindow()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void ProcessEventImGui(SDL_Event *event)
{
    ImGui_ImplSDL3_ProcessEvent(event);
}
