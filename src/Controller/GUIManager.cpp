#include "GUIManager.hpp"

#include "Controller/Engine/Engine.hpp"
#include "Controller/InputManager.hpp"
#include "Controller/TerrainManager.hpp"
#include "Controller/TextureManager.hpp"
#include "Model/LuaGuiWrapper.h"
#include "Model/TextManager.hpp"

GUIManager::GUIManager() {
    initialiseWindowOpenMap();

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .addFunction("toggleGUIWindow", &GUIManager::luaToggleWindow);

    LuaGUIWrapper::RegisterWithLua();
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
    ImGui_ImplOpenGL3_Init("#version 150");
}

void GUIManager::displayInputRebindWindow() {
    auto &inputManager = Controller::Input::InputManager::getInstance();
    auto &inputMap     = inputManager.getInputMap();
    auto &windowOpen   = windowOpenMap.at("controls");
    auto &resManager   = ResourceManager::getInstance();
    const auto *state        = inputManager.getKeyStates();

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
                        const auto &scancodePairs = inputManager.getStringScancodePairs();
                        for (const auto &i : scancodePairs) {
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
            toggleWindow("controls");
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
        if (ImGui::Button("Terrain Settings")) {
            toggleWindow("terrainSettings");
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
    auto &windowOpen = windowOpenMap.at("instructions");
    if (windowOpen) {
        ImGui::Begin(resManager.getString("InstructionMenu_title").c_str(), &windowOpen,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text(resManager.getString("InstructionMenu_instructions").c_str());
        ImGui::End();
    }
}

void GUIManager::displayQuitScreen() {
    auto &textures   = ResourceManager::getInstance().GetTextureManager();
    auto &texture    = textures.getTexture("exitScreen");
    auto &windowOpen = windowOpenMap.at("exit");
    auto &engine     = BlueEngine::Engine::get();

    if (windowOpen) {
        int height = 0, width = 0;
        glfwGetWindowSize(engine.window, &width, &height);
        ImGui::SetNextWindowPos(ImVec2(width / 2, height / 2), ImGuiCond_Always, ImVec2(0.5, 0.5));
        ImGui::Begin("###Exit", &windowOpen,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize |
                         ImGuiWindowFlags_NoTitleBar);

        ImGui::Text("Thank you for playing our game. Click the image to exit.");
        if (ImGui::ImageButton(reinterpret_cast<void *>(intptr_t(texture.TextureID)),
                               ImVec2(texture.width / 4, texture.height / 4))) {
            engine.endEngine();
        }

        ImGui::End();
    }
}

void GUIManager::displayDevScreen(View::Camera &camera) {
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
    auto &textureManager = ResourceManager::getInstance().GetTextureManager();
    auto &windowOpen     = windowOpenMap.at("texture");
    auto &texMap         = textureManager.textureMap;
    if (windowOpen) {
        ImGui::Begin("Textures", &windowOpen, ImGuiWindowFlags_NoCollapse);

        for (auto &n : texMap) {
            ImGui::Image(reinterpret_cast<void *>(static_cast<intptr_t>(n.second.TextureID)), ImVec2(100, 100));
            ImGui::SameLine();
            ImGui::Text("Texture Name: %s\nTexture ID: %d\nWidth: %d\nHeight: %d", n.first.c_str(),
                        n.second.TextureID, n.second.width, n.second.height);
            ImGui::Separator();
        }
        ImGui::End();
    }
}

void GUIManager::displayTerrainSettings() {
    auto &texManager = ResourceManager::getInstance().GetTextureManager();

    if (terrainManager != nullptr) {

        auto &windowOpen        = windowOpenMap.at("terrainSettings");
        constexpr auto textLimit = 1000;

        const auto snowID  = terrainManager->getSnowTextureId();
        const auto grassID = terrainManager->getGrassTextureId();
        const auto sandID  = terrainManager->getSandTextureId();
        const auto dirtID  = terrainManager->getDirtTextureId();
        const auto waterID = terrainManager->getWaterTextureId();

        const auto snowHeight  = terrainManager->getSnowHeight();
        const auto grassHeight = terrainManager->getGrassHeight();
        const auto sandHeight  = terrainManager->getSandHeight();
        const auto dirtHeight  = terrainManager->getDirtHeight();
        const auto waterHeight = terrainManager->getWaterHeight();

        static auto snowSlider  = snowHeight;
        static auto grassSlider = grassHeight;
        static auto sandSlider  = sandHeight;
        static auto dirtSlider  = dirtHeight;
        static auto waterSlider = waterHeight;

        static char snowMap[textLimit];
        static char grassMap[textLimit];
        static char dirtMap[textLimit];
        static char waterMap[textLimit];
        static char sandMap[textLimit];

        auto showTextureInfo = [&](const unsigned int textureID, const std::string &textureName,
                                   char text[textLimit], const std::function<void(unsigned int)> &
                                   setTex) {
            ImGui::Image(reinterpret_cast<void *>(intptr_t(textureID)), ImVec2(100, 100));
            ImGui::SameLine();
            ImGui::Text("%s Texture \nTexture ID: %d", textureName.c_str(), textureID);
            std::string inputTextName = "ID ###" + textureName;
            ImGui::InputText(textureName.c_str(), text, textLimit);
            const std::string buttonName = "Set Texture ###" + textureName;
            if (ImGui::Button(buttonName.c_str())) {
                const auto id = texManager.getTexture(text);
                setTex(id.TextureID);
            }
            ImGui::Separator();
        };

        const std::function<void(int)> setSnow = [&](unsigned id) { terrainManager->setSnowTextureId(id); };
        const std::function<void(int)> setGrass = [&](unsigned id) {
            terrainManager->setGrassTextureId(id);
        };
        const std::function<void(int)> setWater = [&](unsigned id) {
            terrainManager->setWaterTextureId(id);
        };
        const std::function<void(int)> setDirt = [&](unsigned id) { terrainManager->setDirtTextureId(id); };
        const std::function<void(int)> setSand = [&](unsigned id) { terrainManager->setSandTextureId(id); };

        constexpr const auto minHeight = 0;
        constexpr const auto maxHeight = 255;

        if (windowOpen) {
            ImGui::Begin("Terrain Settings", &windowOpen, ImGuiWindowFlags_AlwaysAutoResize);

            showTextureInfo(snowID, "Snow", snowMap, setSnow);
            showTextureInfo(grassID, "Grass", grassMap, setGrass);
            showTextureInfo(sandID, "Sand", sandMap, setSand);
            showTextureInfo(dirtID, "Dirt", dirtMap, setDirt);
            showTextureInfo(waterID, "Water", waterMap, setWater);

            ImGui::SliderFloat("Water Height", &waterSlider, minHeight, maxHeight);
            ImGui::SliderFloat("Sand Height", &sandSlider, minHeight, grassSlider);
            ImGui::SliderFloat("Grass Height", &grassSlider, sandSlider, dirtSlider);
            ImGui::SliderFloat("Dirt Height", &dirtSlider, grassSlider, snowSlider);
            ImGui::SliderFloat("Snow Height", &snowSlider, dirtSlider, maxHeight);

            if (ImGui::Button("Submit")) {
                terrainManager->setSandHeight(sandSlider);
                terrainManager->setGrassHeight(grassSlider);
                terrainManager->setDirtHeight(dirtSlider);
                terrainManager->setSnowHeight(snowSlider);
                terrainManager->setWaterHeight(waterSlider);
                terrainManager->UpdateInfo();
            }
            ImGui::End();
        }
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

void GUIManager::toggleWindow(const std::string &windowName) {
    if (windowOpenMap.find(windowName) != windowOpenMap.end()) {
        bool &open = windowOpenMap.at(windowName);
        open       = open ? false : true;
    }
}

void GUIManager::setTerrainManager(Controller::TerrainManager *terrain) {
    terrainManager = terrain;
}

void GUIManager::initialiseWindowOpenMap() {
    windowOpenMap.insert(std::make_pair(std::string("menu"), false));
    windowOpenMap.insert(std::make_pair(std::string("controls"), false));
    windowOpenMap.insert(std::make_pair(std::string("instructions"), false));
    windowOpenMap.insert(std::make_pair(std::string("exit"), false));
    windowOpenMap.insert(std::make_pair(std::string("dev"), false));
    windowOpenMap.insert(std::make_pair(std::string("texture"), false));
    windowOpenMap.insert(std::make_pair(std::string("textureRebind"), false));
    windowOpenMap.insert(std::make_pair(std::string("terrainSettings"), false));
}

void GUIManager::luaToggleWindow(std::string window) {

    auto &guiManager = BlueEngine::Engine::get().getGuiManager();
    guiManager.toggleWindow(window);
}
