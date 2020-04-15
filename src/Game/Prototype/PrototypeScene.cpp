#include "PrototypeScene.hpp"

#include <glm/glm.hpp>

#include "Controller/Engine/Engine.hpp"
#include "Model/Models/Model.hpp"
#include "Model/Models/ModelManager.hpp"
#include "View/Renderer/OpenGLProxy.hpp"
#include "View/Renderer/Renderer.hpp"
#include "Controller/TextureManager.hpp"

using Controller::Input::BLUE_InputAction;
using Controller::Input::BLUE_InputType;

PrototypeScene::PrototypeScene() {
	Init();
}

auto PrototypeScene::update([[maybe_unused]] double t, double dt) -> void {
	if (moveForward) {
		camera.ProcessKeyboard(FORWARD, dt);
	}
	if (moveBackward) {
		camera.ProcessKeyboard(BACKWARD, dt);
	}
	if (moveLeft) {
		camera.ProcessKeyboard(LEFT, dt);
	}
	if (moveRight) {
		camera.ProcessKeyboard(RIGHT, dt);
	}

	terrain.Update(camera.getLocation());
}

void PrototypeScene::Init() {
	auto& resManager = ResourceManager::getInstance();
	BlueEngine::RenderCode::HardInit();
	terrain.Init();
	camera.Position.y = 100.0;
	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	models.push_back(resManager.getModelID("res/model/player_male.obj"));
    auto &texManager = TextureManager ::getInstance();

    texManager.loadTextureFromFile("res/images/dirt.jpg", "dirt");
}

void PrototypeScene::handleWindowEvent() {
	BlueEngine::RenderCode::ResizeWindow();
}

// SDLFIX
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
		default: break;
		}
	} break;
	case BLUE_InputType::MOUSE_MOTION: { // Mouse motion event
		if (engine.getMouseMode() == false) {
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
	// SDLFIX
	auto& engine = BlueEngine::Engine::get();
	BlueEngine::RenderCode::Display();
	auto& guiManager = engine.getGuiManager();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	guiManager.startWindowFrame();
	guiManager.displayInputRebindWindow();
	guiManager.displayEscapeMenu();
	guiManager.displayInstructionMenu();
    guiManager.displayQuitScreen();
	int width = 0, height = 0;
	glfwGetWindowSize(engine.window, &width, &height);
	// view/projection transformations
	glm::mat4 projection =
		glm::perspective(glm::radians(camera.Zoom),
			static_cast<double>(width) / static_cast<double>(height), 0.1, 100000.0);
	glm::mat4 view = camera.GetViewMatrix();

	//glm::mat4 model = glm::mat4(5.0f);

	//Renderer::addToDraw(model, models[0]);
	terrain.Draw(projection, view, camera.Position);
	//renderer.draw(view, projection);

	guiManager.endWindowFrame();

	BlueEngine::RenderCode::EndDisplay();
}

void PrototypeScene::unInit() {}

double PrototypeScene::getDeltaTime() {
	auto newTime = glfwGetTime();
	return (newTime - time);
}
