#include <View/Renderer/OpenGL.hpp>
#include <Controller/Engine/Engine.hpp>
#include "MainMenu.hpp"
#include "Game/Prototype/PrototypeScene.hpp"

using Controller::Input::BLUE_InputAction;
using Controller::Input::BLUE_InputType;

MainMenu::MainMenu() {
    auto &window = BlueEngine::Engine::get().window;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

MainMenu::~MainMenu() {}

void MainMenu::Init() {
    camera = View::Camera();
    camera.Position = glm::vec3(0.0f, 10.0f, 0.0f);
    sModels.emplace_back("res/model/ClothedMan.gltf");
    sModels.emplace_back("res/model/ClothedMan.gltf");
    sModels.at(0).position.x = 20.0f;
    sModels.at(0).position.z = 2.0f;
    sModels.at(0).animator = std::make_shared<Controller::Animator>();
    sModels.at(0).animator->LinkToModel(static_cast<unsigned>(sModels.at(0).getModel()));
    sModels.at(0).animator->LoadAnimation("PUNCH");
    sModels.at(0).rotation = glm::quat(glm::vec3(0.0f, glm::radians(180.0f) ,0.0f));
    sModels.at(1).position.x = 20.5f;
    sModels.at(1).position.z = -2.0f;
    sModels.at(1).animator = std::make_shared<Controller::Animator>();
    sModels.at(1).animator->LinkToModel(static_cast<unsigned>(sModels.at(1).getModel()));
    sModels.at(1).animator->LoadAnimation("PUNCH");
    sModels.at(1).rotation = glm::quat(glm::vec3(0.0f, 0.0f ,0.0f));
    camera.Pitch -= 20.0f;
    camera.updateCameraVectors();
}

auto MainMenu::display() -> void {
    auto &engine   = BlueEngine::Engine::get();
    auto &renderer = BlueEngine::Engine::get().renderer;
    renderer.SetCameraOnRender(camera);
    for (auto& m : sModels) {
        m.addToDraw();
    }
}

auto MainMenu::update(double t, double dt) -> void {
    for (auto & m : sModels) {
        m.update(t, dt);
    }
}

void MainMenu::unInit() {

}

void MainMenu::handleWindowEvent() {
    auto &engine = BlueEngine::Engine::get();
    engine.renderer.ResizeWindow();
}

void MainMenu::handleInputData(Controller::Input::InputData inputData, double deltaTime) {
    auto &engine      = BlueEngine::Engine::get();
    auto &guiManager  = engine.getGuiManager();
    auto handledMouse = false;

    switch (inputData.inputType) {
        case BLUE_InputType::KEY_PRESS: { //  Key Press events

            switch (inputData.inputAction) {
                case BLUE_InputAction::INPUT_MOVE_FORWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_LEFT: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_RIGHT: {
                } break;
                default: break;
            }
        } break;
        case BLUE_InputType::KEY_RELEASE: { // Key Release events
            switch (inputData.inputAction) {
                case BLUE_InputAction::INPUT_MOVE_FORWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_LEFT: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_RIGHT: {
                } break;
                case BLUE_InputAction::INPUT_JUMP: {
                } break;
                case BLUE_InputAction::INPUT_CROUCH: {
                } break;
                case BLUE_InputAction::INPUT_ACTION_2: {
                } break;
                case BLUE_InputAction::INPUT_ACTION_3: {
                } break;
                case BLUE_InputAction::INPUT_ACTION_4: {
                } break;
                default: break;
            }
        } break;
        case BLUE_InputType::MOUSE_MOTION: { // Mouse motion event
            if (!engine.getMouseMode()) {
//                 auto x = static_cast<double>(inputData.mouseMotionRelative.x);
//                 auto y = static_cast<double>(inputData.mouseMotionRelative.y);
//                 y      = y * -1.0;
//                 camera.ProcessMouseMovement(x, y);
//                 handledMouse = true;
            }
        } break;
        case BLUE_InputType::MOUSE_WHEEL: { // Mouse Wheel event
            auto amountScrolledY = static_cast<double>(inputData.mouseWheelMotion);
            //camera.ProcessMouseScroll(amountScrolledY);
        } break;
        case BLUE_InputType::WINDOW_RESIZE: {
            this->handleWindowEvent();
        } break;
        default: break;
    }
    if (!handledMouse) {
        engine.mouse = {0.0f, 0.0f};
    }
}

void MainMenu::startGame(Model::Difficulty newDifficulty) {
    auto &engine = BlueEngine::Engine::get();
    Model::GameState::getInstance().setDifficulty(newDifficulty);
    engine.gameStack.AddToStack(std::make_shared<PrototypeScene>());
}

void MainMenu::GUIStart() {
    auto &engine  = BlueEngine::Engine::get();
    GUIManager::startWindowFrame();
    MainMenuGUI();
    if (displayDifficultyMenu) {
        DifficultyMenu();
    }
}

void MainMenu::MainMenuGUI() {
    auto &engine = BlueEngine::Engine::get();
    ImGui::SetNextWindowSize(ImVec2(300, 500), 1);
    //ImGui::SetNextWindowPosCenter(1);

    ImGui::Begin("Menu", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Separator();
    ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
    ImGui::Text("Project Blue: Run and Gun");
    if (ImGui::Button("Play Game", ImVec2(285, 40))) {
        //startGame(Difficulty::easy);
        displayDifficultyMenu = true;
    }
    ImGui::Separator();

    ImGui::Text("Other options");
    if (ImGui::Button("Settings", ImVec2(285, 40))) {
        engine.showSettingsMenu = !engine.showSettingsMenu;
    }
    if (ImGui::Button("Quit", ImVec2(285, 40))) {
        engine.endEngine();
    }

    if (engine.showSettingsMenu) {
        engine.SettingMenu();
    }

    ImGui::End();
}

void MainMenu::DifficultyMenu() {
    auto &engine = BlueEngine::Engine::get();
    ImVec2 buttonSize(150, 30);
    ImGui::SetNextWindowFocus();
    ImGui::SetNextWindowSize(ImVec2(500, 100), 1);
    ImGui::Begin("Difficulty", &displayDifficultyMenu,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Separator();
    ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
    ImGui::Text("Select Difficulty");
    if (ImGui::Button("Easy", buttonSize)) {
        startGame(Model::Difficulty::easy);
        displayDifficultyMenu = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Medium", buttonSize)) {
        startGame(Model::Difficulty::medium);
        displayDifficultyMenu = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Hard", buttonSize)) {
        startGame(Model::Difficulty::hard);
        displayDifficultyMenu = false;
    }
    ImGui::End();
}

void MainMenu::GUIEnd() {
    GUIManager::endWindowFrame();
}
