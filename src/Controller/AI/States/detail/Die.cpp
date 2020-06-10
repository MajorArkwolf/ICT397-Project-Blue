	/// Declaration Include
#include "Controller/AI/States/Die.hpp"

void State_Die::start(std::shared_ptr<GameObj_Base> context) {
	// Set the GameObject's animation
	if (context->animator_has())
		context->animator_changeAnimation("DEATH", true);
}

void State_Die::run(std::shared_ptr<GameObj_Base> context, double t, double dt) {

}

void State_Die::end(std::shared_ptr<GameObj_Base> context) {

}

void State_Die::read(std::shared_ptr<GameObj_Base> context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) {

}
