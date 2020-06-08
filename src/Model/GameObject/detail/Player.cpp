	/// Definition Include
#include "../Player.hpp"

	/// Internal Dependencies
#include "Controller/Engine/Engine.hpp"
#include "Controller/PhysicsManager.hpp"
#include "../Types.hpp"

GameObj_Player::GameObj_Player(BlueEngine::ID model_in, BlueEngine::ID physBody_in)
	: GameObj_Base(model_in, physBody_in), GameObj_Character() {
	// GameObj_Player has no unique construction procedure yet.
}

GameObj_Type GameObj_Player::type() const {
	// Return the GameObject's type
	return GameObj_Type::Player;
}

void GameObj_Player::addToDraw() {
	// Create a function pointer of the GameObject's draw call for the DrawItem
	std::function<void(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos)> e = [&](const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
		this->draw(projection, view, cameraPos);
	};

	// Here the DrawItem for the GameObject is generated and configured
	View::Data::DrawItem drawItem = {};
	drawItem.drawPointer = e;
	drawItem.pos = Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(physBody)->GetPosition();

	// Finally the DrawItem is added to the renderer queue
	auto& renderer = BlueEngine::Engine::get().renderer;
	renderer.AddToQue(drawItem);
}

void GameObj_Player::draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos [[maybe_unused]]) {
	// Attempt to gather the Game Object's physics body
	auto phys_world = Physics::PhysicsManager::GetInstance().GetDynamicsWorld();
	auto phys_body = phys_world->GetRigidBody(physBody);

	// Generate and configure the GameObject's model matrix
	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, phys_body->GetPosition());
	model_matrix = glm::scale(model_matrix, scale);
	model_matrix = model_matrix * glm::mat4_cast(phys_body->GetOrientation());

	// Enable the shader and pass it the values for its uniforms
	program.get()->use();
	program.get()->setMat4("projection", projection);
	program.get()->setMat4("view", view);
	program.get()->setMat4("model", model_matrix);

	// Get the resource manager and call for it to draw the model
	auto& res_manager = ResourceManager::getInstance();
	res_manager.drawModel(model, program.get());
}
