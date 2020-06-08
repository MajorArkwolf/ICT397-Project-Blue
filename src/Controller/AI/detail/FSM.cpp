	/// Declaration Include
#include "Controller/AI/FSM.hpp"

	/// Internal Dependencies
#include "Controller/Engine/LuaManager.hpp"
#include "Controller/AI/Manager.hpp"

// Registratiion of Enum State_Type
namespace luabridge {
	template <>
	struct luabridge::Stack <State_Type> : EnumWrapper <State_Type> {};
}

// Registratiion of Enum Message_Type
namespace luabridge {
	template <>
	struct luabridge::Stack <Message_Type> : EnumWrapper <Message_Type> {};
}

FSM::FSM(std::shared_ptr<GameObj_Base> object) {
	// Just cache the provided reference
	attached_object = object;
}

void FSM::local_set(std::shared_ptr<State_Base> target) {
	// Call the status's end behaviour
	if (local_current)
		local_current->end(attached_object.lock());

	// Update the internally stored states
	local_prior = local_current;
	local_current = target;

	// Call the status's start behaviour
	if (local_current)
		local_current->start(attached_object.lock());
}

void FSM::local_revert() {
	// Call the status's end behaviour
	if (local_current)
		local_current->end(attached_object.lock());

	// Update the internally stored states
	auto local_temp = local_prior;
	local_prior = local_current;
	local_current = local_temp;

	// Call the status's start behaviour
	if (local_current)
		local_current->start(attached_object.lock());
}

void FSM::global_set(std::shared_ptr<State_Base> target) {
	// Call the status's end behaviour
	if (global_current)
		global_current->end(attached_object.lock());

	// Update the internally stored states
	global_prior = global_current;
	global_current = target;

	// Call the status's start behaviour
	if (global_current)
		global_current->start(attached_object.lock());
}

void FSM::global_revert() {
	// Call the status's end behaviour
	if (global_current)
		global_current->end(attached_object.lock());

	// Update the internally stored states
	auto global_temp = global_prior;
	global_prior = global_current;
	global_current = global_temp;

	// Call the status's start behaviour
	if (global_current)
		global_current->start(attached_object.lock());
}

void FSM::run(double t, double dt) {
	// Call the local status's run behaviour
	if (local_current)
		local_current->run(attached_object.lock(), t, dt);

	// Call the global status's run behaviour
	if (global_current)
		global_current->run(attached_object.lock(), t, dt);
}

void FSM::read(BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) {
	// Call the local status's read behaviour
	if (local_current)
		local_current->read(attached_object.lock(), msg_sender, msg_type, msg_attachment);

	// Call the global status's read behaviour
	if (global_current)
		global_current->read(attached_object.lock(), msg_sender, msg_type, msg_attachment);
}

BlueEngine::ID FSM::id_this() {
	// Return a copy of the stored identifier
	return unique_id;
}

std::shared_ptr<GameObj_Base> FSM::attached() {
	// Return a copy of the attached GameObject's identifier
	return attached_object.lock();
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
			.addFunction("stateLocal_setCustom", &FSM::lua_local_set_custom)
			.addFunction("stateGlobal_setRegular", &FSM::lua_global_set_regular)
			.addFunction("stateGlobal_setCustom", &FSM::lua_global_set_custom)
			.addFunction("id", &FSM::id_this)
			.addFunction("attached", &FSM::lua_attached)
		.endClass();

	// Prevent re-registration
	isRegistered = true;
}

void FSM::lua_local_set_regular(State_Type type) {

}

bool FSM::lua_local_set_custom(std::string start_func, std::string run_func, std::string end_func, std::string read_func) {

}

void FSM::lua_global_set_regular(State_Type type) {

}

void FSM::lua_global_set_custom(std::string start_func, std::string run_func, std::string end_func, std::string read_func) {

}

GameObj_Base* FSM::lua_attached() {

}
