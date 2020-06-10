	/// Declaration Include
#include "Controller/AI/States/Revive.hpp"

void State_Revive::start(std::shared_ptr<GameObj_Base> context) {
	// Set the GameObject's animation
	if (context->animator_has())
		context->animator_changeAnimation("WORKING", true);
}

void State_Revive::run(std::shared_ptr<GameObj_Base> context, double t, double dt) {

}

void State_Revive::end(std::shared_ptr<GameObj_Base> context) {

}

void State_Revive::read(std::shared_ptr<GameObj_Base> context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) {

}
