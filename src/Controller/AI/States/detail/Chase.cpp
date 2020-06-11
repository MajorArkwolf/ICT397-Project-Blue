	/// Declaration Include
#include "Controller/AI/States/Chase.hpp"

	/// External Dependencies
#include "glm/gtx/quaternion.hpp"

	/// Internal Dependencies
#include "Controller/PhysicsManager.hpp"
#include "Controller/Factory/TerrainFactory.hpp"
#include "Controller/Factory/GameAssetFactory.hpp"

void State_Chase::start(std::shared_ptr<GameObj_Base> context) {
	// Set the GameObject's animation
	if (context->animator_has())
		context->animator_changeAnimation("RUN", false);
	
	// Get the entirety of the contextual NPC's properties
	std::shared_ptr<GameObj_NPC> npc = std::dynamic_pointer_cast<GameObj_NPC>(context);
}

void State_Chase::run(std::shared_ptr<GameObj_Base> context, double t [[maybe_unused]], double dt) {
	// Get the NPC's collision body
	auto npc_phys = Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(context->physBody);

	// Get the Player's GameObject and collision body
	std::shared_ptr<GameObj_Base> player_obj = Controller::Factory::get().GameObject(GameObj_Type::Player);
	auto player_phys = Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(player_obj->physBody);

	// Make sure the NPC's physical body is at a stand-still
	npc_phys->SetSleeping(true);

	// Make sure the NPC is oriented towards the player
	glm::vec3 npc_pos = glm::vec3(npc_phys->GetPosition().x, 0.0f, npc_phys->GetPosition().z);
	glm::vec3 player_pos = glm::vec3(player_phys->GetPosition().x, 0.0f, player_phys->GetPosition().z);
	glm::quat rotationToPlayer = glm::quatLookAt(glm::normalize(npc_pos - player_pos), glm::vec3(0.0f, 1.0f, 0.0f));
	npc_phys->SetOrientation(rotationToPlayer);

	// The NPC is running, move it forward
	glm::vec3 new_position = npc_phys->GetPosition() + (npc_phys->GetOrientation() * (glm::vec3(0.0f, 0.0f, 4.0f * float(dt))));
	new_position.y = Controller::TerrainFactory::LuaBLHeight(new_position.x, new_position.z) + 0.1f;
	npc_phys->SetPosition(new_position);
}

void State_Chase::end(std::shared_ptr<GameObj_Base> context [[maybe_unused]] ) {
	// No behaviour
}

void State_Chase::read(std::shared_ptr<GameObj_Base> context [[maybe_unused]], BlueEngine::ID msg_sender [[maybe_unused]], Message_Type msg_type [[maybe_unused]], float msg_attachment [[maybe_unused]] ) {
	// No behaviour
}
