	/// Declaration Include
#include "Controller/AI/States/Wander.hpp"

	/// Internal Dependencies
#include "Controller/PhysicsManager.hpp"
#include "Controller/Factory/TerrainFactory.hpp"

void State_Wander::start(std::shared_ptr<GameObj_Base> context) {
	// Set the GameObject's animation
	if (context->animator_has())
		context->animator_changeAnimation("IDLE", false);

	// Register the GameObject's statuses for this state
	std::shared_ptr<GameObj_NPC> npc = std::dynamic_pointer_cast<GameObj_NPC>(context);
	if (!npc->status_has("Wander_IdleTimeMax")) {
		// Assign the critical status
		npc->status_assign("Wander_IdleTimeMax", 4.0f);
	}
	if (!npc->status_has("Wander_WalkTimeMax")) {
		// Assign the critical status
		npc->status_assign("Wander_WalkTimeMax", 9.0f);
	}

	// Configure the runtime status for the NPC
	npc->status_assign("Wander_ActionTime", 0.0f);
	npc->status_assign("Wander_ActionIsIdle", 1.0f);
}

void State_Wander::run(std::shared_ptr<GameObj_Base> context, double t, double dt) {
	// Get the NPC's collision body
	auto npc_phys = Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(context->physBody);

	// Make sure the NPC's physical body is at a stand-still, and correctly orientated
	npc_phys->SetSleeping(true);
	npc_phys->SetOrientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

	// Get the entirety of the contextual NPC's properties
	std::shared_ptr<GameObj_NPC> npc = std::dynamic_pointer_cast<GameObj_NPC>(context);

	// Increment the behaviour timer
	npc->status_assign("Wander_ActionTime", npc->status_get("Wander_ActionTime") + float(dt));

	// Determine the behaviour to apply for the wandering
	if (npc->status_get("Wander_ActionIsIdle") < 0.5f) {
		// The NPC is walking, move it forward
		glm::vec3 new_position = npc_phys->GetPosition() + (npc_phys->GetOrientation() * (glm::vec3(0.0f, 0.0f, 1.0f * float(dt))));
		new_position.y = Controller::TerrainFactory::LuaBLHeight(new_position.x, new_position.z) + 0.1f;
		npc_phys->SetPosition(new_position);

		// Catch if the wandering behaviour should swap
		if (npc->status_get("Wander_ActionTime") > npc->status_get("Wander_WalkTimeMax")) {
			// Change the direction that the AI will face
			//TODO: Implement this!

			// Change the NPC's animation to walking
			npc->animator_changeAnimation("IDLE", false);

			// Reset the timer and swap the identifier
			npc->status_assign("Wander_ActionTime", 0.0f);
			npc->status_assign("Wander_ActionIsIdle", 1.0f);
		}
	}
	else {
		// Catch if the wandering behaviour should swap
		if (npc->status_get("Wander_ActionTime") > npc->status_get("Wander_IdleTimeMax")) {
			// Change the NPC's animation to walking
			npc->animator_changeAnimation("WALK", false);

			// Reset the timer and swap the identifier
			npc->status_assign("Wander_ActionTime", 0.0f);
			npc->status_assign("Wander_ActionIsIdle", 0.0f);
		}
	}
}

void State_Wander::end(std::shared_ptr<GameObj_Base> context [[maybe_unused]]) {
	// No behaviour
}

void State_Wander::read(std::shared_ptr<GameObj_Base> context [[maybe_unused]], BlueEngine::ID msg_sender [[maybe_unused]], Message_Type msg_type [[maybe_unused]], float msg_attachment [[maybe_unused]]) {
	// No behaviour
}
