#pragma once
#include <string>

#include "Controller/Engine/LuaManager.hpp"
#include "imgui.h"
#include "glm/vec2.hpp"

class LuaGUIWrapper {
private:
    LuaGUIWrapper() = default;
    static void BeginWindow(const std::string &title);

    static void SameLine();

    static void SetFontSize(float scale);

    static void Text(const std::string &text);

    static void EndWindow();

    static void SetNextWindowPos(float x, float y, bool lock);

    static glm::ivec2 GetWindowSize();

  public:
    static void RegisterWithLua();

};
