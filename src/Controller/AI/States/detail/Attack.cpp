    /// Declaration Include
#include "Controller/AI/States/Attack.hpp"

	/// Internal Dependencies
#include "Controller/PhysicsManager.hpp"
#include "Controller/Factory/GameAssetFactory.hpp"
#include "Controller/AI/Manager.hpp"

void State_Attack::start(std::shared_ptr<GameObj_Base> context) {
	// Set the GameObject's animation
	if (context->animator_has())
		context->animator_changeAnimation("PUNCH", true);

	// Register the GameObject's statuses for this state
	std::shared_ptr<GameObj_NPC> npc = std::dynamic_pointer_cast<GameObj_NPC>(context);
	if (!npc->status_has("Attack_Damage")) {
		// Assign the critical status
		npc->status_assign("Attack_Damage", 10.0f);
	}
	if (!npc->status_has("NPC_RangeScale")) {
		// Assign the critical status
		npc->status_assign("NPC_RangeScale", 1.0f);
	}

	// Configure the runtime status for the NPC
	npc->status_assign("Attack_Time", 0.0f);
	npc->status_assign("Attack_Performed", 0.0f);
}

void State_Attack::run(std::shared_ptr<GameObj_Base> context, double t [[maybe_unused]], double dt) {
	// Get the raw player information
	std::shared_ptr<GameObj_Character> player_raw = std::dynamic_pointer_cast<GameObj_Character>(Controller::Factory::get().GameObject(GameObj_Type::Player));

	// Get the raw physics data from the player
	auto player_phys = Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(player_raw->physBody);

	// Make sure the NPC's physical body is at a stand-still
	auto npc_phys = Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(context->physBody);
	npc_phys->SetSleeping(true);

	// Make sure the NPC is oriented towards the player
	glm::vec3 npc_pos = glm::vec3(npc_phys->GetPosition().x, 0.0f, npc_phys->GetPosition().z);
	glm::vec3 player_pos = glm::vec3(player_phys->GetPosition().x, 0.0f, player_phys->GetPosition().z);
	glm::quat rotationToPlayer = glm::quatLookAt(glm::normalize(npc_pos - player_pos), glm::vec3(0.0f, 1.0f, 0.0f));
	npc_phys->SetOrientation(rotationToPlayer);

	// Make sure the NPC is not falling through the ground
	glm::vec3 positionFix = npc_phys->GetPosition();
	positionFix.y = Controller::TerrainFactory::LuaBLHeight(positionFix.x, positionFix.z);
	npc_phys->SetPosition(positionFix);

	// Increment the timer for the NPC's attacking action
	std::shared_ptr<GameObj_NPC> npc = std::dynamic_pointer_cast<GameObj_NPC>(context);
	npc->status_assign("Attack_Time", npc->status_get("Attack_Time") + float(dt));

	// Catch if damage should be applied to the player
	if ((npc->status_get("Attack_Time") > 0.7f) && (npc->status_get("Attack_Performed") < 0.5f)) {
		// Catch if the NPC is within a close enough range to damage the player
		if (glm::length(npc_pos - player_pos) < 3.0f * npc->status_get("NPC_RangeScale")) {
			// Do damage to the player
			player_raw->status_assign("Health", player_raw->status_get("Health") - npc->status_get("Attack_Damage"));
		}

		// Ensure that damage is only done to the player once
		npc->status_assign("Attack_Performed", 1.0f);
	}

	// Catch if the GameObject's animation has ended
	if (context->animator_animationHasEnded()) {
		// Switch this NPC's state to chase the player
		FSM_Manager::get(npc->contextID)->local_set(FSM_Manager::regular_state(State_Type::Chase));
	}
}

void State_Attack::end(std::shared_ptr<GameObj_Base> context [[maybe_unused]] ) {
	// No behaviour
}

void State_Attack::read(std::shared_ptr<GameObj_Base> context [[maybe_unused]], BlueEngine::ID msg_sender [[maybe_unused]], Message_Type msg_type [[maybe_unused]], float msg_attachment [[maybe_unused]]) {
	// No behaviour
}
