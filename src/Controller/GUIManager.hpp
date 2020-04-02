#pragma once

#include <SDL.h>
#include <imgui.h>
#include <map>
#include <string>

#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_sdl.h>

class GUIManager {
  public:
    GUIManager();

    ~GUIManager();
    void initialiseImGUI(SDL_Window *window, void *context);
    void displayInputRebindWindow();
    void displayEscapeMenu();
    void startWindowFrame();
    void endWindowFrame();
    void toggleWindow(std::string windowName);

  private:
    static constexpr int windowMax = 30;
    std::map<std::string, bool> windowOpenMap;
    bool windowOpen[windowMax];
    void initialiseWindowOpenMap();
};