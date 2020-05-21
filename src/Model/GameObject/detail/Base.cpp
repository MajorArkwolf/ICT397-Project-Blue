	/// Definition Include
#include "../Base.hpp"

	/// Internal Dependencies
#include "../Types.hpp"

GameObj_Base::GameObj_Base(BlueEngine::ID model_in, BlueEngine::ID physBody_in) {
	// Store the external asset identifiers
	model = model_in;
	physBody = physBody_in;

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
	// The base GameObject will always return an indicator that its type is not valid.
	return BlueEngine::ID(GameObj_Type::Invalid);
}
