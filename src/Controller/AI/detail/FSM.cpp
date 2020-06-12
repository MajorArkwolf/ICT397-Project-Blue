	/// Declaration Include
#include "Controller/AI/FSM.hpp"

	/// Internal Dependencies
#include "Controller/AI/Manager.hpp"

FSM::FSM(std::shared_ptr<GameObj_Base> object) {
	// Cache the provided reference
	attached_object = object;

	// Assign the FSM's unique identifier
	unique_id = BlueEngine::IDTracker::getInstance().getID();

	// Initialise the States
	local_current = nullptr;
	local_prior = nullptr;
	global_current = nullptr;
	global_prior = nullptr;
}

FSM::~FSM() {
	// Only free memory on the custom States.
	if (local_current != nullptr) {
		if (local_current->isCustom()) {
			// Free the dynamically assigned State.
			delete local_current;
		}
	}
	if (local_prior != nullptr) {
		if (local_prior->isCustom()) {
			// Free the dynamically assigned State.
			delete local_prior;
		}
	}
	if (global_current != nullptr) {
		if (global_current->isCustom()) {
			// Free the dynamically assigned State.
			delete global_current;
		}
	}
	if (global_prior != nullptr) {
		if (global_prior->isCustom()) {
			// Free the dynamically assigned State.
			delete global_prior;
		}
	}
}

void FSM::local_set(State_Base* target) {
	// Call the status's end behaviour
	if (local_current)
		local_current->end(attached_object);

	// Update the internally stored states
	if (local_prior != nullptr) {
		if (local_prior->isCustom()) {
			// Free the dynamically assigned State.
			delete local_prior;
		}
	}
	local_prior = local_current;
	local_current = target;

	// Call the status's start behaviour
	if (local_current)
		local_current->start(attached_object);
}

void FSM::local_revert() {
	// Call the status's end behaviour
	if (local_current)
		local_current->end(attached_object);

	// Update the internally stored states
	auto local_temp = local_prior;
	local_prior = local_current;
	local_current = local_temp;

	// Call the status's start behaviour
	if (local_current)
		local_current->start(attached_object);
}

void FSM::global_set(State_Base* target) {
	// Call the status's end behaviour
	if (global_current)
		global_current->end(attached_object);

	// Update the internally stored states
	if (global_prior != nullptr) {
		if (global_prior->isCustom()) {
			// Free the dynamically assigned State.
			delete global_prior;
		}
	}
	global_prior = global_current;
	global_current = target;

	// Call the status's start behaviour
	if (global_current)
		global_current->start(attached_object);
}

void FSM::global_revert() {
	// Call the status's end behaviour
	if (global_current)
		global_current->end(attached_object);

	// Update the internally stored states
	auto global_temp = global_prior;
	global_prior = global_current;
	global_current = global_temp;

	// Call the status's start behaviour
	if (global_current)
		global_current->start(attached_object);
}

void FSM::run(double t, double dt) {
	// Call the local status's run behaviour
	if (local_current)
		local_current->run(attached_object, t, dt);

	// Call the global status's run behaviour
	if (global_current)
		global_current->run(attached_object, t, dt);
}

void FSM::read(BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) {
	// Call the local status's read behaviour
	if (local_current)
		local_current->read(attached_object, msg_sender, msg_type, msg_attachment);

	// Call the global status's read behaviour
	if (global_current)
		global_current->read(attached_object, msg_sender, msg_type, msg_attachment);
}

BlueEngine::ID FSM::id_this() {
	// Return a copy of the stored identifier
	return unique_id;
}

std::shared_ptr<GameObj_Base> FSM::attached() {
	// Return a copy of the attached GameObject's identifier
	return attached_object;
}

void FSM::lua_init() {
	// Prevent this being run more than once
	static bool isRegistered = false;
	if (isRegistered)
		return;

	// Register the Message Class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginClass<Message>("FSM_Message")
			.addConstructor<void (*) (void)>()
			.addProperty("sender", &Message::sender)
			.addProperty("type", &Message::type)
			.addProperty("attachment", &Message::attachment)
			.addProperty("delay", &Message::delay)
			.addFunction("recipient_add", &Message::recipient_add)
			.addFunction("recipient_list", &Message::recipient_list)
		.endClass();

	// Register the FSM Class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginClass<FSM>("FSM_Class")
			.addFunction("stateLocal_setRegular", &FSM::lua_local_set_regular)
			.addFunction("stateLocal_setCustom", &FSM::lua_local_set_custom_could_lua_bind_stop_breaking_this_please)
			.addFunction("stateGlobal_setRegular", &FSM::lua_global_set_regular)
			.addFunction("stateGlobal_setCustom", &FSM::lua_global_set_custom_could_lua_bind_stop_breaking_this_please)
			.addFunction("id", &FSM::id_this)
			.addFunction("attached", &FSM::lua_attached)
		.endClass();

	// Prevent re-registration
	isRegistered = true;
}

void FSM::lua_local_set_regular(State_Type type) {
	// Call the local set function and gather the regular state
	auto temp = FSM_Manager::regular_state(type);
	local_set(temp);
}

void FSM::lua_local_set_custom_could_lua_bind_stop_breaking_this_please(std::string start_func, std::string run_func, std::string end_func, std::string read_func) {
	// Attempt to generate the local state
	State_Base* custom_temp = FSM_Manager::custom_state(start_func, run_func, end_func, read_func);

	// Catch failure to generate the custom state
	if (custom_temp == nullptr) {
		// Report has already been made to the console, just indicate failure
		return;
	}

	// Call the local set function
	this->local_set(custom_temp);
}

void FSM::lua_global_set_regular(State_Type type) {
	// Call the local set function and gather the regular state
	global_set(FSM_Manager::regular_state(type));
}

void FSM::lua_global_set_custom_could_lua_bind_stop_breaking_this_please(std::string start_func, std::string run_func, std::string end_func, std::string read_func) {
	// Attempt to generate the local state
	State_Base* custom_temp = FSM_Manager::custom_state(start_func, run_func, end_func, read_func);

	// Catch failure to generate the custom state
	if (custom_temp == nullptr) {
		// Report has already been made to the console, just indicate failure
		return;
	}

	// Call the local set function
	this->global_set(custom_temp);
}

GameObj_Base* FSM::lua_attached() {
	// Call the function and encapsulate it's return value from Lua
	return attached().get();
}
