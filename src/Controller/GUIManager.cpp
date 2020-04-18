#include "GUIManager.hpp"

#include "Controller/Engine/Engine.hpp"
#include "Controller/InputManager.hpp"
#include "Controller/TextureManager.hpp"
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
        ImGui::SetNextWindowPos(ImVec2(0.5, 0.5), ImGuiCond_Always, ImVec2(-0.5, -0.5));
        ImGui::Begin(resManager.getString("OptionMenu_title").c_str(), &windowOpen,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
        if (ImGui::Button("Controls")) {
            toggleWindow("constrols");
        }
        if (ImGui::Button("Instructions")) {
            toggleWindow("instructions");
        }
        if (ImGui::Button("Dev Menu")) {
            toggleWindow("dev");
        }
        if (ImGui::Button("Textures")) {
            toggleWindow("texture");
        }
        if (ImGui::Button("Exit")) {
            toggleWindow("exit");
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

void GUIManager::displayQuitScreen() {
    auto &textures   = TextureManager::getInstance();
    auto &texture    = textures.getTexture("dirt");
    bool &windowOpen = windowOpenMap.at("exit");
    auto &engine     = BlueEngine::Engine::get();

    if (windowOpen) {
        int height = 0, width = 0;
        glfwGetWindowSize(engine.window, &width, &height);
        ImGui::SetNextWindowPos(ImVec2(width / 2, height / 2), ImGuiCond_Always, ImVec2(0.5, 0.5));
        ImGui::Begin("###Exit", &windowOpen,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize |
                         ImGuiWindowFlags_NoTitleBar);

        ImGui::Text("Thank you for playing our game. Click the image to exit.");
        if (ImGui::ImageButton((void *)(intptr_t)texture.TextureID,
                               ImVec2(texture.width / 4, texture.height / 4))) {
            engine.endEngine();
        }

        ImGui::End();
    }
}

void GUIManager::displayDevScreen(Camera &camera) {
    // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    bool &windowOpen = windowOpenMap.at("dev");
    if (windowOpen) {
        auto key = camera.getLocation();
        ImGui::Begin("Dev Menu", &windowOpen, ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Camera Position: %f, %f, %f", camera.Position.x, camera.Position.y,
                    camera.Position.z);
        ImGui::SliderFloat("Camera Speed", &camera.MovementSpeed, 0.001f, 2.0f);
        ImGui::Text("Camera Location Key: %d, %d", key.x, key.y);
        ImGui::End();
    }
}

void GUIManager::displayTextureManager() {
    auto &textureManager = TextureManager::getInstance();
    bool &windowOpen     = windowOpenMap.at("texture");
    auto &texMap         = textureManager.textureMap;
    if (windowOpen) {
        textureRebind();
        ImGui::Begin("Terrain Textures", &windowOpen, ImGuiWindowFlags_NoCollapse);

        /*auto *currentSelection = &(*texMap.begin());
        if (ImGui::BeginCombo("asd", currentSelection->first.c_str())) {
            for (auto &n : texMap) {
                ImGui::PushID(n.first.c_str());
                bool isSelected = currentSelection->first == n.first;
                if (ImGui::Selectable(n.first.c_str(), isSelected)) {
                    currentSelection = &n;
                }
                ImGui::PopID();
            }
            ImGui::EndCombo();
        }*/

        for (auto &n : texMap) {
            static char text[255];
            std::string currentTexture;
            ImGui::Image((void *)(intptr_t)n.second.TextureID, ImVec2(100, 100));
            ImGui::SameLine();
            ImGui::Text(n.first.c_str());
            std::string buttonName = "Rebind###" + n.first;
            if (ImGui::Button(buttonName.c_str())) {
                texName                           = n.first;
                windowOpenMap.at("textureRebind") = true;
            }

            ImGui::Separator();
        }
        ImGui::End();
    }
}
void GUIManager::textureRebind() {
    bool &windowOpen = windowOpenMap.at("textureRebind");
    auto &texManager = TextureManager::getInstance();
    if (windowOpen) {
        static char text[255];
        std::string windowTitle = "New Texture Path for '" + texName + "'";
        ImGui::Begin(windowTitle.c_str(), &windowOpen, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::InputText(" ", text, IM_ARRAYSIZE(text));
        if (ImGui::Button("Set")) {
            std::string asd(text);
            texManager.textureMap.erase(texName);
            texManager.loadTextureFromFile(text, texName);
        }
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
    if (windowOpenMap.find(windowName) != windowOpenMap.end()) {
        bool &open = windowOpenMap.at(windowName);
        open       = open ? false : true;
    }
}

void GUIManager::initialiseWindowOpenMap() {
    windowOpenMap.insert(std::make_pair(std::string("menu"), false));
    windowOpenMap.insert(std::make_pair(std::string("controls"), false));
    windowOpenMap.insert(std::make_pair(std::string("instructions"), false));
    windowOpenMap.insert(std::make_pair(std::string("exit"), false));
    windowOpenMap.insert(std::make_pair(std::string("dev"), false));
    windowOpenMap.insert(std::make_pair(std::string("texture"), false));
    windowOpenMap.insert(std::make_pair(std::string("textureRebind"), false));
}
