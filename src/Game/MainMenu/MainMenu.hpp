#pragma once
#include "Model/BaseState.hpp"
#include "Controller/InputManager.hpp"
#include "View/EulerCamera.hpp"
#include "Game/MainMenu/StaticModel.hpp"

class MainMenu : public BaseState {
public:
    MainMenu();
    ~MainMenu() override;
    auto display() -> void override;
    auto update(double t, double dt) -> void override;

    void Init() override;
    void unInit() override;

    void handleInputData(Controller::Input::InputData inputData, double deltaTime) override;

    void startGame();

private:
    void handleWindowEvent();
    View::Camera camera;
    std::vector<MainMenuObject::StaticModel> sModels = {};
};


