#include "GUIManager.hpp"

#include "Controller/Engine/Engine.hpp""
#include "Controller/InputManager.hpp"
#include "Model/TextManager.hpp"

GUIManager::GUIManager() {
    initialiseWindowOpenMap();
}

GUIManager::~GUIManager() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUIManager::initialiseImGUI(GLFWwindow *window) {

    // Setup ImGui.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void GUIManager::displayInputRebindWindow() {
    auto &inputManager = Controller::Input::InputManager::getInstance();
    auto &inputMap     = inputManager.getInputMap();
    bool &windowOpen   = windowOpenMap.at("controls");
    auto &resManager   = ResourceManager::getInstance();
    auto *state        = inputManager.getKeyStates();

    if (windowOpen) {
    
     ImGui::Begin(resManager.getString("ControlMenu_title").c_str(), &windowOpenMap.at("controls"),
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGui::Text("Click on a button while holding a key to map an action to that key");
        ImGui::Separator();

        for (auto &n : inputMap) {
            switch (n.first) {
                case Controller::Input::BLUE_InputAction::INPUT_DEFAULT:
                case Controller::Input::BLUE_InputAction::INPUT_LOOK_UP:
                case Controller::Input::BLUE_InputAction::INPUT_LOOK_DOWN:
                case Controller::Input::BLUE_InputAction::INPUT_LOOK_LEFT:
                case Controller::Input::BLUE_InputAction::INPUT_LOOK_RIGHT: {
                } break;
                default: {
                    auto scancodeString = inputManager.hashGLFWKeyToString(n.second);
                    auto actionString   = inputManager.hashInputActionToString(n.first);
                    ImGui::Text(actionString.c_str());
                    ImGui::SameLine(ImGui::GetWindowWidth() - 80);

                    if (ImGui::Button(scancodeString.c_str())) {
                        auto &scancodePairs = inputManager.getStringScancodePairs();
                        for (auto &i : scancodePairs) {
                            if (state[i.second]) {
                                inputManager.bindKey(n.first, i.second);
                                break;
                            }
                        }
                    }

                } break;
            }
        }

        ImGui::End();
    }
    
}

void GUIManager::displayEscapeMenu() {
    // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    bool &windowOpen = windowOpenMap.at("menu");
    auto &resManager = ResourceManager::getInstance();

    if (windowOpen) {
        ImGui::SetNextWindowPos(ImVec2(0.5,0.5), ImGuiCond_Always, ImVec2(-0.5,-0.5));
        ImGui::Begin(resManager.getString("OptionMenu_title").c_str(), &windowOpen,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
        if (ImGui::Button("Controls")) {
            auto &isControlsOpen = windowOpenMap.at("controls");
            isControlsOpen       = isControlsOpen ? false : true;
        }
        if (ImGui::Button("Instructions")) {
            auto &isControlsOpen = windowOpenMap.at("instructions");
            isControlsOpen       = isControlsOpen ? false : true;
        }
        if (ImGui::Button("Exit")) {
            auto &engine = BlueEngine::Engine::get();
            engine.endEngine();
        }
        ImGui::End();
    }
}

void GUIManager::displayInstructionMenu() {
    auto &resManager = ResourceManager::getInstance();
    // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    bool &windowOpen = windowOpenMap.at("instructions");
    if (windowOpen) {
        ImGui::Begin(resManager.getString("InstructionMenu_title").c_str(), &windowOpen,
                     ImGuiWindowFlags_NoCollapse);
        ImGui::Text(resManager.getString("InstructionMenu_instructions").c_str());
        ImGui::End();
    }
}

void GUIManager::startWindowFrame() {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUIManager::endWindowFrame() {

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::toggleWindow(std::string windowName) {
    bool &open = windowOpenMap.at(windowName);
    open       = open ? false : true;
}

void GUIManager::initialiseWindowOpenMap() {
    windowOpenMap.insert(std::make_pair(std::string("menu"), true));
    windowOpenMap.insert(std::make_pair(std::string("controls"), false));
    windowOpenMap.insert(std::make_pair(std::string("instructions"), false));
}
