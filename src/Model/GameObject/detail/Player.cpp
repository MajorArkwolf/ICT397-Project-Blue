	/// Definition Include
#include "../Player.hpp"

	/// Internal Dependencies
#include "../Types.hpp"
#include "Controller/Engine/Engine.hpp"

GameObj_Player::GameObj_Player(BlueEngine::ID model_in, BlueEngine::ID physBody_in)
	: GameObj_Base(model_in, physBody_in) {
	// GameObj_Player has no unique construction procedure yet.
}

GameObj_Player::~GameObj_Player() {
	// GameObj_Player has no unique destruction procedure yet.
}

BlueEngine::ID GameObj_Player::type() const {
	// Return the GameObject's type
	return BlueEngine::ID(GameObj_Type::Player);
}

void GameObj_Player::draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
	// Generate and configure the GameObject's model matrix
	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, gameObj_pos);
	model_matrix = glm::rotate(model_matrix, glm::radians(gameObj_rotation[0]), glm::vec3(0.0f, 1.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(gameObj_rotation[1]), glm::vec3(1.0f, 0.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(gameObj_rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
	model_matrix = glm::scale(model_matrix, gameObj_scale);

	// Enable the shader and pass it the values for its uniforms
	program.use();
	program.setMat4("projection", projection);
	program.setMat4("view", view);
	program.setMat4("model", model_matrix);

	// Get the resource manager and call for it to draw the model
	auto& res_manager = ResourceManager::getInstance();
	res_manager.drawModel(model, &program);
}
