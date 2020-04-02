#include "GUIManager.hpp"

#include <Controller/Engine/Engine.hpp>
#include <Controller/InputManager.hpp>

GUIManager::GUIManager() {}

GUIManager::~GUIManager() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void GUIManager::initialiseImGUI(SDL_Window *window, void *context) {

    // Setup ImGui.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init();
}

void GUIManager::displayInputRebindWindow() {
    auto &inputManager = Controller::Input::InputManager::getInstance();
    auto &inputMap     = inputManager.getInputMap();
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    ImGui::NewFrame();
    ImGui::Begin("Controls"); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

    for (auto &n : inputMap) {
        switch (n.first) {
            case Controller::Input::BLUE_InputAction::INPUT_DEFAULT:
            case Controller::Input::BLUE_InputAction::INPUT_LOOK_UP:
            case Controller::Input::BLUE_InputAction::INPUT_LOOK_DOWN:
            case Controller::Input::BLUE_InputAction::INPUT_LOOK_LEFT:
            case Controller::Input::BLUE_InputAction::INPUT_LOOK_RIGHT: {
            } break;
            default: {
                auto scancodeString = inputManager.hashScancodeToString(n.second);
                auto actionString   = inputManager.hashInputActionToString(n.first);
                ImGui::Text(actionString.c_str());
                ImGui::SameLine();
                if (ImGui::Button(scancodeString.c_str())) {
                    auto &scancodePairs = inputManager.getStringScancodePairs();
                    for (auto &i : scancodePairs) {
                        if (state[i.second]) {

                            inputManager.bindKey(n.first, i.second);
                        }
                    }
                }
            } break;
        }
    }

    ImGui::End();
}

void GUIManager::startWindowFrame() {
    auto &engine = BlueEngine::Engine::get();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(engine.window.get());
}

void GUIManager::endWindowFrame() {

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
