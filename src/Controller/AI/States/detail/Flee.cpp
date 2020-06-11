	/// Declaration Include
#include "Controller/AI/States/Flee.hpp"

	/// Internal Dependencies
#include "Controller/PhysicsManager.hpp"

void State_Flee::start(std::shared_ptr<GameObj_Base> context [[maybe_unused]]) {
	// No behaviour
}

void State_Flee::run(std::shared_ptr<GameObj_Base> context [[maybe_unused]], double t [[maybe_unused]], double dt [[maybe_unused]]) {
	// No behaviour
}

void State_Flee::end(std::shared_ptr<GameObj_Base> context [[maybe_unused]]) {
	// No behaviour
}

void State_Flee::read(std::shared_ptr<GameObj_Base> context [[maybe_unused]], BlueEngine::ID msg_sender [[maybe_unused]], Message_Type msg_type [[maybe_unused]], float msg_attachmen [[maybe_unused]]) {
	// No behaviour
}
