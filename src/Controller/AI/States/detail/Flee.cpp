	/// Declaration Include
#include "Controller/AI/States/Flee.hpp"

void State_Flee::start(std::shared_ptr<GameObj_Base> context) {
	// Set the GameObject's animation
	if (context->animator_has())
		context->animator_changeAnimation("RUN", false);
}

void State_Flee::run(std::shared_ptr<GameObj_Base> context, double t, double dt) {

}

void State_Flee::end(std::shared_ptr<GameObj_Base> context) {

}

void State_Flee::read(std::shared_ptr<GameObj_Base> context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) {

}
