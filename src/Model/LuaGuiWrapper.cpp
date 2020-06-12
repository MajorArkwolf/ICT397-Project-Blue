#include "LuaGuiWrapper.h"

#include "Controller/Engine/Engine.hpp"

void LuaGUIWrapper::BeginWindow(const std::string &title) {
    ImGui::Begin(title.c_str(), nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoTitleBar);
    
}

void LuaGUIWrapper::SameLine() {
    ImGui::SameLine();
}

bool LuaGUIWrapper::Button(const std::string &text) {
    return ImGui::Button(text.c_str());
}

void LuaGUIWrapper::SetFontSize(float scale) {
    ImGui::SetWindowFontScale(scale);
}

void LuaGUIWrapper::Text(const std::string &text) {
    ImGui::Text(text.c_str());
}

void LuaGUIWrapper::EndWindow() {
    ImGui::End();
}

void LuaGUIWrapper::SetNextWindowPos(float x, float y, bool lock) {
    ImGuiCond_ Conditions = ImGuiCond_Once;
    if (lock) {
        Conditions = ImGuiCond_Always;
    }
    ImGui::SetNextWindowPos(ImVec2(x, y), Conditions);
}

glm::ivec2 LuaGUIWrapper::GetWindowSize() {

    int width, height;
    glfwGetWindowSize(BlueEngine::Engine::get().window, &width, &height);
    return glm::ivec2(width, height);
}


void LuaGUIWrapper::RegisterWithLua() {
    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginNamespace("GUIFunctions")
        .addFunction("BeginWindow", &LuaGUIWrapper::BeginWindow)
        .addFunction("SameLine", &LuaGUIWrapper::SameLine)
        .addFunction("Text", &LuaGUIWrapper::Text)
        .addFunction("EndWindow", &LuaGUIWrapper::EndWindow)
        .addFunction("SetNextWindowPos", &LuaGUIWrapper::SetNextWindowPos)
        .addFunction("GetWindowSize", &LuaGUIWrapper::GetWindowSize)
        .addFunction("Button", &LuaGUIWrapper::Button)
        .addFunction("SetFontSize", &LuaGUIWrapper::SetFontSize);
}
