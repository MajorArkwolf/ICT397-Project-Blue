	/// Declaration Include
#include "Controller/AI/States/Revive.hpp"

	/// Internal Dependencies
#include "Controller/PhysicsManager.hpp"

void State_Revive::start(std::shared_ptr<GameObj_Base> context [[maybe_unused]]) {
	// No behaviour
}

void State_Revive::run(std::shared_ptr<GameObj_Base> context [[maybe_unused]], double t [[maybe_unused]], double dt [[maybe_unused]]) {
	// No behaviour
}

void State_Revive::end(std::shared_ptr<GameObj_Base> context [[maybe_unused]]) {
	// No behaviour
}

void State_Revive::read(std::shared_ptr<GameObj_Base> context [[maybe_unused]], BlueEngine::ID msg_sender [[maybe_unused]], Message_Type msg_type [[maybe_unused]], float msg_attachment [[maybe_unused]]) {
	// No behaviour
}
