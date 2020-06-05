	/// Declaration Include
#include "Controller/AI/FSM.hpp"

FSM::FSM(std::shared_ptr<GameObj_Base> object) {
	// Just cache the provided reference
	attached_object = object;
}

void FSM::local_set(std::shared_ptr<State_Base> target) {
	// Call the status's end behaviour
	if (local_current)
		local_current->end(this);

	// Update the internally stored states
	local_prior = local_current;
	local_current = target;

	// Call the status's start behaviour
	if (local_current)
		local_current->start(this);
}

void FSM::local_revert() {
	// Call the status's end behaviour
	if (local_current)
		local_current->end(this);

	// Update the internally stored states
	auto local_temp = local_prior;
	local_prior = local_current;
	local_current = local_temp;

	// Call the status's start behaviour
	if (local_current)
		local_current->start(this);
}

void FSM::global_set(std::shared_ptr<State_Base> target) {
	// Call the status's end behaviour
	if (global_current)
		global_current->end(this);

	// Update the internally stored states
	global_prior = global_current;
	global_current = target;

	// Call the status's start behaviour
	if (global_current)
		global_current->start(this);
}

void FSM::global_revert() {
	// Call the status's end behaviour
	if (global_current)
		global_current->end(this);

	// Update the internally stored states
	auto global_temp = global_prior;
	global_prior = global_current;
	global_current = global_temp;

	// Call the status's start behaviour
	if (global_current)
		global_current->start(this);
}

void FSM::run(double t, double dt) {
	// Call the local status's run behaviour
	if (local_current)
		local_current->run(this, t, dt);

	// Call the global status's run behaviour
	if (global_current)
		global_current->run(this, t, dt);
}

void FSM::read(BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) {
	// Call the local status's read behaviour
	if (local_current)
		local_current->read(this, msg_sender, msg_type, msg_attachment);

	// Call the global status's read behaviour
	if (global_current)
		global_current->read(this, msg_sender, msg_type, msg_attachment);
}

BlueEngine::ID FSM::id_this() {
	// Return a copy of the stored identifier
	return unique_id;
}

std::shared_ptr<GameObj_Base> FSM::attached() {
	// Return a copy of the attached GameObject's identifier
	return attached_object.lock();
}
