#include "PrototypeScene.hpp"

#include <glm/glm.hpp>

#include "Controller/Engine/Engine.hpp"
#include "Model/Models/Model.hpp"
#include "Model/Models/ModelManager.hpp"
#include "View/Renderer/OpenGL.hpp"
#include "View/Renderer/Renderer.hpp"
#include "Controller/TextureManager.hpp"
#include "Model/GameObject/Manager.hpp"
#include "Controller/Engine/LuaManager.hpp"
#include "Controller/Factory/GameAssetFactory.hpp"

using Controller::Input::BLUE_InputAction;
using Controller::Input::BLUE_InputType;

PrototypeScene::PrototypeScene() {
	Init();
}

auto PrototypeScene::update([[maybe_unused]] double t, double dt) -> void {
	if (moveForward) {
		camera.ProcessKeyboard(Camera_Movement::FORWARD, dt);
	}
	if (moveBackward) {
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, dt);
	}
	if (moveLeft) {
		camera.ProcessKeyboard(Camera_Movement::LEFT, dt);
	}
	if (moveRight) {
		camera.ProcessKeyboard(Camera_Movement::RIGHT, dt);
	}
	//auto test = glm::vec2(camera.Position.x, camera.Position.z);
    //std::cout << Controller::Factory::get().terrain.getHeightAtCord(test) << "\n";
    //Controller::Factory::get().terrain.crashTest(test);
	terrain.Update(camera.getLocation());
}

void PrototypeScene::Init() {
	camera = View::Camera(glm::vec3(0.0f, 150.0f, 3.0f));
	models.emplace_back("res/model/player_male.obj", false);

	// Temporarily hard-code the external Lua script file while a proper implementation of Lua integration is on hold
	GameObj_Manager::init();
	luaL_dofile(LuaManager::getInstance().getLuaState(), "res/scripts/gameobjsSet.lua");
}

void PrototypeScene::handleWindowEvent() {
	View::OpenGL::ResizeWindow();
}

void PrototypeScene::handleInputData(Controller::Input::InputData inputData) {
	auto& engine = BlueEngine::Engine::get();
	auto& guiManager = engine.getGuiManager();
	auto handledMouse = false;

	switch (inputData.inputType) {
	case BLUE_InputType::KEY_PRESS: { //  Key Press events

		switch (inputData.inputAction) {
		case BLUE_InputAction::INPUT_MOVE_FORWARD: {
			moveForward = true;
		} break;
		case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
			moveBackward = true;
		} break;
		case BLUE_InputAction::INPUT_MOVE_LEFT: {
			moveLeft = true;
		} break;
		case BLUE_InputAction::INPUT_MOVE_RIGHT: {
			moveRight = true;
		} break;
		case BLUE_InputAction::INPUT_ESCAPE: {
			guiManager.toggleWindow("menu");
		} break;

		default: break;
		}

	} break;
	case BLUE_InputType::KEY_RELEASE: { // Key Release events
		switch (inputData.inputAction) {
		case BLUE_InputAction::INPUT_MOVE_FORWARD: {
			moveForward = false;
		} break;
		case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
			moveBackward = false;
		} break;
		case BLUE_InputAction::INPUT_MOVE_LEFT: {
			moveLeft = false;
		} break;
		case BLUE_InputAction::INPUT_MOVE_RIGHT: {
			moveRight = false;
		} break;
        case BLUE_InputAction::INPUT_ACTION_2: {
            auto &renderer = BlueEngine::Engine::get().renderer;
            renderer.ToggleWireFrame();
        } break;
        case BLUE_InputAction::INPUT_ACTION_3: {
            guiManager.toggleWindow("instructions");
        } break;
        case BLUE_InputAction::INPUT_ACTION_4: {
            guiManager.toggleWindow("exit");
        } break;
		default: break;
		}
	} break;
	case BLUE_InputType::MOUSE_MOTION: { // Mouse motion event
		if (!engine.getMouseMode()) {
			auto x = static_cast<double>(inputData.mouseMotionRelative.x);
			auto y = static_cast<double>(inputData.mouseMotionRelative.y);
			y = y * -1.0;
			camera.ProcessMouseMovement(x, y);
			handledMouse = true;
		}

	} break;
	case BLUE_InputType::MOUSE_WHEEL: { // Mouse Wheel event
		double amountScrolledY = static_cast<double>(inputData.mouseWheelMotion);
		camera.ProcessMouseScroll(amountScrolledY);
	} break;
	case BLUE_InputType::WINDOW_RESIZE: {
		this->handleWindowEvent();
	} break;
	default: break;
	}
	if (!handledMouse) {
		engine.mouse = { 0.0f, 0.0f };
	}
}

auto PrototypeScene::display() -> void {
    auto &renderer = BlueEngine::Engine::get().renderer;
    renderer.SetCameraOnRender(camera);
	terrain.AddToDraw();
	GameObj_Manager::addAllToDraw();
}

void PrototypeScene::unInit() {}

