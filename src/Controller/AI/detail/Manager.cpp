	/// Declaration Include
#include "Controller/AI/Manager.hpp"

	/// System Dependencies
#include <set>
#include <stdexcept>

	/// Internal Dependencies
#include "Controller/Engine/LuaManager.hpp"
#include "Controller/AI/States/Custom.hpp"
#include "Controller/AI/States/Chase.hpp"
#include "Controller/AI/States/Flee.hpp"
#include "Controller/AI/States/Wander.hpp"
#include "Controller/AI/States/Attack.hpp"
#include "Controller/AI/States/Die.hpp"
#include "Controller/AI/States/Revive.hpp"

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

State_Base* FSM_Manager::regular_state(State_Type type) {
	// Spit out the requested type
	switch (type) {
	case (State_Type::Wander):
		static State_Wander staticState_Wander;
		return &staticState_Wander;

	case (State_Type::Chase):
		static State_Chase staticState_Chase;
		return &staticState_Chase;

	case (State_Type::Attack):
		static State_Attack staticState_Attack;
		return &staticState_Attack;

	case (State_Type::Flee):
		static State_Flee staticState_Flee;
		return &staticState_Flee;

	case (State_Type::Die):
		static State_Die staticState_Die;
		return &staticState_Die;

	case (State_Type::Revive):
		static State_Revive staticState_Revive;
		return &staticState_Revive;

	default:
		return nullptr;
	}
}

State_Base* FSM_Manager::custom_state(std::string start_func, std::string run_func, std::string end_func, std::string read_func) {
	// Attempt to gather the start function
	luabridge::LuaRef start_temp = luabridge::getGlobal(LuaManager::getInstance().getLuaState(), start_func.c_str());
	if (start_temp == luabridge::Nil()) {
		// Report the error and return nullptr
		std::cout << "Failed to generate a custom state: Lua global \"" << start_func << "\" could not be gathered for the start behaviour!\n";
		return nullptr;
	}

	// Attempt to gather the run function
	luabridge::LuaRef run_temp = luabridge::getGlobal(LuaManager::getInstance().getLuaState(), run_func.c_str());
	if (run_temp == luabridge::Nil()) {
		// Report the error and return nullptr
		std::cout << "Failed to generate a custom state: Lua global \"" << run_func << "\" could not be gathered for the run behaviour!\n";
		return nullptr;
	}

	// Attempt to gather the end function
	luabridge::LuaRef end_temp = luabridge::getGlobal(LuaManager::getInstance().getLuaState(), end_func.c_str());
	if (end_temp == luabridge::Nil()) {
		// Report the error and return nullptr
		std::cout << "Failed to generate a custom state: Lua global \"" << end_func << "\" could not be gathered for the end behaviour!\n";
		return nullptr;
	}

	// Attempt to gather the read function
	luabridge::LuaRef read_temp = luabridge::getGlobal(LuaManager::getInstance().getLuaState(), read_func.c_str());
	if (read_temp == luabridge::Nil()) {
		// Report the error and return nullptr
		std::cout << "Failed to generate a custom state: Lua global \"" << read_func << "\" could not be gathered for the read behaviour!\n";
		return nullptr;
	}

	// Generate and return the custom state
	return new State_Custom(start_temp, run_temp, end_temp, read_temp);
}

void FSM_Manager::lua_init() {
	// Prevent this being run more than once
	static bool isRegistered = false;
	if (isRegistered)
		return;

	// Call the FSM Class's Lua registration function
	FSM::lua_init();

	// Register the FSM Manager Class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("FSM")
			.addFunction("create", &FSM_Manager::lua_create)
			.addFunction("get", &FSM_Manager::lua_get)
			.addFunction("erase", &FSM_Manager::erase)
			.addFunction("clear", &FSM_Manager::clear)
			.addFunction("send", &FSM_Manager::send)
		.endNamespace();

	// Register the FSM State Type Enum access functions
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("FSM")
			.beginNamespace("State")
				.addFunction("Invalid", &FSM_Manager::lua_enum_state_invalid)
				.addFunction("Wander", &FSM_Manager::lua_enum_state_wander)
				.addFunction("Chase", &FSM_Manager::lua_enum_state_chase)
				.addFunction("Attack", &FSM_Manager::lua_enum_state_attack)
				.addFunction("Flee", &FSM_Manager::lua_enum_state_flee)
				.addFunction("Die", &FSM_Manager::lua_enum_state_die)
				.addFunction("Revive", &FSM_Manager::lua_enum_state_revive)
			.endNamespace()
		.endNamespace();

	// Register the FSM Message Type Enum access functions
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("FSM")
			.beginNamespace("Message")
				.addFunction("Invalid", &FSM_Manager::lua_enum_msg_invalid)
				.addFunction("PosX", &FSM_Manager::lua_enum_msg_posX)
				.addFunction("PosY", &FSM_Manager::lua_enum_msg_posY)
				.addFunction("PosZ", &FSM_Manager::lua_enum_msg_posZ)
				.addFunction("TargetFound", &FSM_Manager::lua_enum_msg_targetfound)
				.addFunction("IAmHurt", &FSM_Manager::lua_enum_msg_iamhurt)
				.addFunction("IAmHelping", &FSM_Manager::lua_enum_msg_iamhelping)
			.endNamespace()
		.endNamespace();

	// Prevent re-registration
	isRegistered = true;
}

BlueEngine::ID FSM_Manager::lua_create(GameObj_Base* object) {
	// Encapsulate the smart pointers from the C++ interface
	return create(std::shared_ptr<GameObj_Base>(object));
}

FSM* FSM_Manager::lua_get(BlueEngine::ID identifier) {
	// Encapsulate the smart pointers from the C++ interface
	return get(identifier).get();
}

State_Type FSM_Manager::lua_enum_state_invalid() {
	// Return a copy of that enum value
	return State_Type::Invalid;
}

State_Type FSM_Manager::lua_enum_state_wander() {
    // Return a copy of that enum value
    return State_Type::Wander;
}

State_Type FSM_Manager::lua_enum_state_chase() {
    // Return a copy of that enum value
    return State_Type::Chase;
}

State_Type FSM_Manager::lua_enum_state_attack() {
    // Return a copy of that enum value
    return State_Type::Attack;
}

State_Type FSM_Manager::lua_enum_state_flee() {
    // Return a copy of that enum value
    return State_Type::Flee;
}

State_Type FSM_Manager::lua_enum_state_die() {
    // Return a copy of that enum value
    return State_Type::Die;
}

State_Type FSM_Manager::lua_enum_state_revive() {
    // Return a copy of that enum value
    return State_Type::Revive;
}

Message_Type FSM_Manager::lua_enum_msg_invalid() {
	// Return a copy of that enum value
	return Message_Type::Invalid;
}

Message_Type FSM_Manager::lua_enum_msg_posX() {
    // Return a copy of that enum value
    return Message_Type::PositionX;
}

Message_Type FSM_Manager::lua_enum_msg_posY() {
    // Return a copy of that enum value
    return Message_Type::PositionY;
}

Message_Type FSM_Manager::lua_enum_msg_posZ() {
    // Return a copy of that enum value
    return Message_Type::PositionZ;
}

Message_Type FSM_Manager::lua_enum_msg_targetfound() {
    // Return a copy of that enum value
    return Message_Type::TargetFound;
}

Message_Type FSM_Manager::lua_enum_msg_iamhurt() {
    // Return a copy of that enum value
    return Message_Type::IAmHurt;
}

Message_Type FSM_Manager::lua_enum_msg_iamhelping() {
    // Return a copy of that enum value
    return Message_Type::IAmHelping;
}

std::map<BlueEngine::ID, std::shared_ptr<FSM>> FSM_Manager::actors = std::map<BlueEngine::ID, std::shared_ptr<FSM>>();

std::forward_list<Message> FSM_Manager::pending_messages = std::forward_list<Message>();
