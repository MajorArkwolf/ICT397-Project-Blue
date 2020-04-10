//#include "GUIManager.hpp"
//
//#include <Controller/Engine/Engine.hpp>
//#include <Controller/InputManager.hpp>
//
//GUIManager::GUIManager() {
//    initialiseWindowOpenMap();
//}
//
//GUIManager::~GUIManager() {
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplSDL2_Shutdown();
//    ImGui::DestroyContext();
//}
//
//void GUIManager::initialiseImGUI(SDL_Window *window, void *context) {
//
//    // Setup ImGui.
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGui::StyleColorsDark();
//    ImGui_ImplSDL2_InitForOpenGL(window, context);
//    ImGui_ImplOpenGL3_Init();
//}
//
//void GUIManager::displayInputRebindWindow() {
//    auto &inputManager = Controller::Input::InputManager::getInstance();
//    auto &inputMap     = inputManager.getInputMap();
//    const Uint8 *state = SDL_GetKeyboardState(NULL);
//    bool &windowOpen   = windowOpenMap.at("controls");
//
//    // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//    if (windowOpen) {
//    
//     ImGui::Begin("Controls", &windowOpenMap.at("controls"),
//                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
//        ImGui::Text("Click on a button while holding a key to map an action to that key");
//        ImGui::Separator();
//
//        for (auto &n : inputMap) {
//            switch (n.first) {
//                case Controller::Input::BLUE_InputAction::INPUT_DEFAULT:
//                case Controller::Input::BLUE_InputAction::INPUT_LOOK_UP:
//                case Controller::Input::BLUE_InputAction::INPUT_LOOK_DOWN:
//                case Controller::Input::BLUE_InputAction::INPUT_LOOK_LEFT:
//                case Controller::Input::BLUE_InputAction::INPUT_LOOK_RIGHT: {
//                } break;
//                default: {
//                    auto scancodeString = inputManager.hashScancodeToString(n.second);
//                    auto actionString   = inputManager.hashInputActionToString(n.first);
//                    ImGui::Text(actionString.c_str());
//                    ImGui::SameLine(ImGui::GetWindowWidth() - 80);
//
//                    if (ImGui::Button(scancodeString.c_str())) {
//                        auto &scancodePairs = inputManager.getStringScancodePairs();
//                        for (auto &i : scancodePairs) {
//                            if (state[i.second]) {
//                                inputManager.bindKey(n.first, i.second);
//                                break;
//                            }
//                        }
//                    }
//
//                } break;
//            }
//        }
//
//        ImGui::End();
//    }
//    
//}
//
//void GUIManager::displayEscapeMenu() {
//    bool &windowOpen = windowOpenMap.at("menu");
//    // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//    if (windowOpen) {
//        ImGui::Begin("Menu", &windowOpen, ImGuiWindowFlags_NoCollapse);
//        if (ImGui::Button("Controls")) {
//            auto &isControlsOpen = windowOpenMap.at("controls");
//            isControlsOpen       = isControlsOpen ? false : true;
//        }
//        if (ImGui::Button("Exit")) {
//            auto &engine = BlueEngine::Engine::get();
//            engine.endEngine();
//        }
//        ImGui::End();
//    }
//}
//
//void GUIManager::startWindowFrame() {
//    auto &engine = BlueEngine::Engine::get();
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplSDL2_NewFrame(engine.window.get());
//    ImGui::NewFrame();
//}
//
//void GUIManager::endWindowFrame() {
//
//    ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//}
//
//void GUIManager::toggleWindow(std::string windowName) {
//    bool &open = windowOpenMap.at(windowName);
//    open       = open ? false : true;
//}
//
//void GUIManager::initialiseWindowOpenMap() {
//    windowOpenMap.insert(std::make_pair(std::string("menu"), false));
//    windowOpenMap.insert(std::make_pair(std::string("controls"), false));
//}
