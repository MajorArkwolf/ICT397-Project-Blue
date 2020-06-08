	/// Declaration Include
#include "Controller/AI/Manager.hpp"

	/// System Dependencies
#include <set>
#include <stdexcept>

	/// Internal Dependencies
#include "Controller/Engine/LuaManager.hpp"

BlueEngine::ID FSM_Manager::create(std::shared_ptr<GameObj_Base> object) {
	// Catch an invalid GameObject being attached
	if (!object)
		return 0u;
	if (object->type() != GameObj_Type::NPC)
		return 0u;
	
	// Create a new FSM, 'attaching' it to the specified GameObject.
	std::shared_ptr<FSM> new_fsm = std::make_shared<FSM>(object);

	// Catch failing to create the FSM
	if (!new_fsm)
		return 0u;

	// Store the new FSM into the manager's internal storage, and return its identifier
	actors[new_fsm->id_this()] = new_fsm;
	return new_fsm->id_this();
}

std::shared_ptr<FSM> FSM_Manager::get(BlueEngine::ID identifier) {
	// Catch any errors thrown
	try {
		// Attempt to find and return a copy of the requested FSM actor
		return actors.at(identifier);
	}
	catch (...) {
		// Indicate no FSM actor with the specified identifier was found
		return nullptr;
	}
}

void FSM_Manager::erase(BlueEngine::ID identifier) {
	// Just remove the specified FSM actor from the manager's map
	actors.erase(identifier);
}

void FSM_Manager::clear() {
	// Just remove all of the FSM actors from the manager's map
	actors.clear();
}

void FSM_Manager::update(double t, double dt) {
	// Process through the currently pending messages
	std::forward_list<Message>::iterator msg = pending_messages.begin();
	while (msg != pending_messages.end()) {
		// Check if the message can be sent
		if (msg->delay == 0u) {
			// Process through the entire set of recipients
			for (auto recipient = msg->recipients.begin(); recipient != msg->recipients.end(); ++recipient) {
				// Catch messages being sent to invalid recipients
				try {
					// Attempt to send the message to the current recipient
					actors.at(*recipient)->read(msg->sender, msg->type, msg->attachment);
				}
				catch (const std::out_of_range& error[[maybe_unused]]) {
					// Do nothing, as you cannot send messages to recipients that do not exist
				}
			}

			// Remove the message from the pending list and move onto the next
			msg = pending_messages.erase_after(msg);
		}
		else {
			// Decrement the current message and move onto the next
			msg->delay -= 1u;
			++msg;
		}
	}

	// Process through the stored FSM actors
	for (auto actor = actors.begin(); actor != actors.end(); ++actor) {
		// Call their run behaviour
		actor->second->run(t, dt);
	}
}

void FSM_Manager::send(Message message) {
	// Catch the message having no recipients
	if (message.recipients.size() == 0u) {
		// Don't store it for performance reasons
		return;
	}
	
	// Add the message to the list, only process and send them when the manager's run operation is called.
	pending_messages.insert_after(pending_messages.before_begin(), message);
}

std::shared_ptr<State_Base> FSM_Manager::regular_state(State_Type type) {

}

std::shared_ptr<State_Base> FSM_Manager::custom_state(std::string start_func, std::string run_func, std::string end_func, std::string read_func) {

}

void FSM_Manager::lua_init() {

}

BlueEngine::ID FSM_Manager::lua_create(GameObj_Base* object) {

}

FSM* FSM_Manager::lua_get(BlueEngine::ID identifier) {

}

State_Type FSM_Manager::lua_enum_chase() {
	// Return a copy of that enum value
	return State_Type::Chase;
}

State_Type FSM_Manager::lua_enum_evade() {
	// Return a copy of that enum value
	return State_Type::Evade;
}

State_Type FSM_Manager::lua_enum_flee() {
	// Return a copy of that enum value
	return State_Type::Flee;
}

State_Type FSM_Manager::lua_enum_patrol() {
	// Return a copy of that enum value
	return State_Type::Patrol;
}

State_Type FSM_Manager::lua_enum_pursuit() {
	// Return a copy of that enum value
	return State_Type::Pursuit;
}

State_Type FSM_Manager::lua_enum_wander() {
	// Return a copy of that enum value
	return State_Type::Wander;
}
