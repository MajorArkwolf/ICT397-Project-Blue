	/// Declaration Include
#include "Controller/AI/States/Die.hpp"

	/// Internal Dependencies
#include "Controller/PhysicsManager.hpp"
#include "Controller/Factory/GameAssetFactory.hpp"

void State_Die::start(std::shared_ptr<GameObj_Base> context) {
	// Set the GameObject's animation
	if (context->animator_has())
		context->animator_changeAnimation("DEATH", true);
}

void State_Die::run(std::shared_ptr<GameObj_Base> context, double t [[maybe_unused]], double dt [[maybe_unused]]) {
	// Make sure the NPC's physical body is at a stand-still
	auto npc_phys = Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(context->physBody);
	npc_phys->SetSleeping(true);

	// Make sure the NPC is not falling through the ground
	glm::vec3 positionFix = npc_phys->GetPosition();
	positionFix.y = Controller::TerrainFactory::LuaBLHeight(positionFix.x, positionFix.z);
	npc_phys->SetPosition(positionFix);
}

void State_Die::end(std::shared_ptr<GameObj_Base> context [[maybe_unused]]) {
	// No behaviour
}

void State_Die::read(std::shared_ptr<GameObj_Base> context [[maybe_unused]], BlueEngine::ID msg_sender [[maybe_unused]], Message_Type msg_type [[maybe_unused]], float msg_attachment [[maybe_unused]]) {
	// No behaviour
}
