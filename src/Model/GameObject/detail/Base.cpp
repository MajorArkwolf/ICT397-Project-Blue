	/// Definition Include
#include "../Base.hpp"

	/// System Dependencies
#include <functional>

	/// Internal Dependencies
#include "Controller/Engine/Engine.hpp"
#include "Controller/PhysicsManager.hpp"
#include "View/Renderer/Renderer.hpp"
#include "../Types.hpp"

GameObj_Base::GameObj_Base(BlueEngine::ID model_in, BlueEngine::ID physBody_in) {
	// Store the external asset identifiers
	model = model_in;
	physBody = physBody_in;
	program = std::make_shared<Shader>(Shader("res/shader/vertshader.vs", "res/shader/fragshader.fs"));

	// Generate the GameObject's unique identifier.
	uniqueID = BlueEngine::IDTracker::getInstance().getID();
}

GameObj_Base::~GameObj_Base() {
	// GameObj_Base has no unique destruction procedure yet.
}

BlueEngine::ID GameObj_Base::id()
{
	// Return a copy of the GameObject's unique identifier.
	return uniqueID;
}

BlueEngine::ID GameObj_Base::type() const {
	// The Base GameObject will always return an indicator that its type is not valid.
	return BlueEngine::ID(GameObj_Type::Invalid);
}
