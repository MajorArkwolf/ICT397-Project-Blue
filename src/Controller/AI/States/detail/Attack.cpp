    /// Declaration Include
#include "Controller/AI/States/Attack.hpp"

	/// Internal Dependencies
#include "Controller/PhysicsManager.hpp"

void State_Attack::start(std::shared_ptr<GameObj_Base> context) {
	// Get the NPC's collision body
	auto npc_phys = Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(context->physBody);

	// Make sure the NPC's physical body is at a stand-still, and correctly orientated
	npc_phys->SetSleeping(true);
	npc_phys->SetOrientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
}

void State_Attack::run(std::shared_ptr<GameObj_Base> context, double t, double dt) {
	// Make sure the NPC's physical body is at a stand-still
	Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(context->physBody)->SetSleeping(true);
}

void State_Attack::end(std::shared_ptr<GameObj_Base> context) {

}

void State_Attack::read(std::shared_ptr<GameObj_Base> context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) {

}
