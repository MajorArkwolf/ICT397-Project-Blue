	/// Declaration Include
#include "Controller/AI/States/Wander.hpp"

void State_Wander::start(std::shared_ptr<GameObj_Base> context) {
	// Set the GameObject's animation
	if (context->animator_has())
		context->animator_changeAnimation("IDLE", false);

	// Register the GameObject's statuses for this state
	std::shared_ptr<GameObj_NPC> npc = std::dynamic_pointer_cast<GameObj_NPC>(context);
	if (!npc->status_has("Wander_IdleTimeMin")) {
		// Assign the critical status
		npc->status_assign("Wander_IdleTimeMin", 2.0f);
	}
	if (!npc->status_has("Wander_IdleTimeMax")) {
		// Assign the critical status
		npc->status_assign("Wander_IdleTimeMax", 5.0f);
	}
	if (!npc->status_has("Wander_WalkTimeMin")) {
		// Assign the critical status
		npc->status_assign("Wander_WalkTimeMin", 4.0f);
	}
	if (!npc->status_has("Wander_WalkTimeMax")) {
		// Assign the critical status
		npc->status_assign("Wander_WalkTimeMax", 6.0f);
	}

	// Configure the runtime status for the NPC
	npc->status_assign("Wander_ActionTime", 1.0f);
	npc->status_assign("Wander_ActionIsIdle", 1.0f);
}

void State_Wander::run(std::shared_ptr<GameObj_Base> context, double t, double dt) {

}

void State_Wander::end(std::shared_ptr<GameObj_Base> context) {

}

void State_Wander::read(std::shared_ptr<GameObj_Base> context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) {

}
