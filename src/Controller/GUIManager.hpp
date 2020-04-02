#pragma once

#include <imgui.h>
#include <examples/imgui_impl_sdl.h>
#include <examples/imgui_impl_opengl3.h>
#include <SDL.h>


class GUIManager {
  public:
    GUIManager();

    ~GUIManager();
    void initialiseImGUI(SDL_Window *window, void *context);
    void displayInputRebindWindow();
    void startWindowFrame();
    void endWindowFrame();
};