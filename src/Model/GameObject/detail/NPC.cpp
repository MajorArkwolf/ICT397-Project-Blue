	/// Definition Include
#include "../NPC.hpp"

	/// Internal Dependencies
#include "Controller/Engine/Engine.hpp"
#include "Controller/PhysicsManager.hpp"
#include "../Types.hpp"

GameObj_NPC::GameObj_NPC(size_t model_in, BlueEngine::ID physBody_in, BlueEngine::ID context_in)
	: GameObj_Base(model_in, physBody_in), GameObj_Character() {
	// Store the NPC's FSM identifier
	contextID = context_in;
}

GameObj_Type GameObj_NPC::type() const {
	// Return the GameObject's type
	return GameObj_Type::NPC;
}

void GameObj_NPC::addToDraw() {
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

void GameObj_NPC::draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos [[maybe_unused]]) {
	// Attempt to gather the Game Object's physics body
	auto phys_world = Physics::PhysicsManager::GetInstance().GetDynamicsWorld();
	auto phys_body = phys_world->GetRigidBody(physBody);

	// Generate and configure the GameObject's model matrix
	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, phys_body->GetPosition());
	model_matrix = model_matrix * glm::mat4_cast(phys_body->GetOrientation());

	// Enable the shader and pass it the values for its uniforms
	program->use();
	program->setMat4("projection", projection);
	program->setMat4("view", view);
	program->setMat4("model", model_matrix);
    if (animator != nullptr) {
        //TODO: REMOVE THIS. THIS IS A HACK!!!!!!!!! MAKE THE UPDATE FUNCTION WORK
        animator->BoneTransform(BlueEngine::Engine::get().getDt());
        program->setBool("isAnimated", true);
        program->setMat4Array("jointTransforms", animator->Transforms);
    } else {
	    program->setBool("isAnimated", false);
    }

	// Get the resource manager and call for it to draw the model
	auto& res_manager = ResourceManager::getInstance();
	res_manager.drawModel(model, program.get());
}

BlueEngine::ID GameObj_NPC::context() {
	// Return a copy of the locally stored identifier
	return contextID;
}

void GameObj_NPC::lua_init_register() {
	// Register the NPC GameObject class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.deriveClass<GameObj_NPC, GameObj_Character>("GameObj_NPC")
			.addProperty("context", &GameObj_NPC::contextID, false)
		.endClass();
}
void GameObj_NPC::update(double t, double dt) {
    GameObj_Character::update(t, dt);
}
