	/// Definition Include
#include "../Static.hpp"

	/// Internal Dependencies
#include "Controller/Engine/Engine.hpp"
#include "View/Renderer/Renderer.hpp"
#include "../GameObject.hpp"

GameObj_Static::GameObj_Static()
	: GameObj_Base() {
	// Configure the initial Shader
	gameObj_shader = std::make_shared<Shader>(Shader("res/shader/vertshader.vs", "res/shader/fragshader.fs"));
}

GameObj_Static::GameObj_Static(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: GameObj_Base(path, physBody, position, rotation, scale) {
	// Configure the initial Shader
	gameObj_shader = std::make_shared<Shader>(Shader("res/shader/vertshader.vs", "res/shader/fragshader.fs"));
}

GameObj_Static::~GameObj_Static() {
	// GameObj_Static has no unique destruction procedure yet.
}

GameObjType GameObj_Static::gameObj_getTypeID() const {
	// Return a copy of the class's unique type identifier
	return _gameObj_getTypeID();
}

GameObjType GameObj_Static::_gameObj_getTypeID() {
	// Always return error indicator GAMEOBJ_STATIC, never return anything else.
	return GAMEOBJ_STATIC;
}

void GameObj_Static::gameObj_addToDraw() {
	// Create a function pointer of the GameObject's draw call for the DrawItem
	std::function e = [&](const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
		this->Draw(projection, view, cameraPos);
	};

	// Here the DrawItem for the GameObject is generated and configured
	View::Data::DrawItem drawItem = {};
	drawItem.drawPointer = e;
	drawItem.pos = gameObj_pos;

	// Finally the DrawItem is added to the renderer queue
	auto& renderer = BlueEngine::Engine::get().renderer;
	renderer.AddToQue(drawItem);
}

void GameObj_Static::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
	// Catch attempting to render the GameObject with an invalid shader
	if (gameObj_shader == nullptr) {
		std::cerr << "Cannot render GameObj_Static " << gameObj_getUniqueID() << " (with Model " << gameObj_getModelID() << ") as it's shader is invalid!\n";
		return;
	}

	// Generate and configure the GameObject's model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, gameObj_pos);
	model = glm::rotate(model, glm::radians(gameObj_rotation[0]), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(gameObj_rotation[1]), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(gameObj_rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, gameObj_scale);

	// Enable the shader and pass it the values for its uniforms
	gameObj_shader->use();
	gameObj_shader->setMat4("projection", projection);
	gameObj_shader->setMat4("view", view);
	gameObj_shader->setMat4("model", model);

	// Get the resource manager and call for it to draw the model
	auto& res_manager = ResourceManager::getInstance();
	res_manager.drawModel(gameObj_modelId, gameObj_shader.get());
}
