    /// Declaration Include
#include "Controller/AI/States/Attack.hpp"

void State_Attack::start(std::shared_ptr<GameObj_Base> context) {
	// Set the GameObject's animation
	if (context->animator_has())
		context->animator_changeAnimation("PUNCH", true);
}

void State_Attack::run(std::shared_ptr<GameObj_Base> context, double t, double dt) {

}

void State_Attack::end(std::shared_ptr<GameObj_Base> context) {

}

void State_Attack::read(std::shared_ptr<GameObj_Base> context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) {

}
