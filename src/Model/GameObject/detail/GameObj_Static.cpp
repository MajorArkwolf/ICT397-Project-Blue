	/// Definition Include
#include "../GameObj_Static.hpp"

GameObj_Static::GameObj_Static()
	: GameObject_Base() {
	// GameObj_Static has no unique attributes to initialise yet
}

GameObj_Static::GameObj_Static(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up)
	: GameObject_Base(path, physBody, position, look_at, look_up) {
	// GameObj_Static has no unique attributes to initialise yet
}

GameObj_Static::~GameObj_Static() {
	// GameObj_Static has no unique destruction procedure yet.
}

GameObjectType GameObj_Static::gameObj_getTypeID() const {
	// Return a copy of the class's unique type identifier
	return _gameObj_getTypeID();
}

GameObjectType GameObj_Static::_gameObj_getTypeID() {
	// Keep track of this class's identifier for its type
	static const GameObjectType classID = gameObj_registerTypeID();

	// Return a copy of the tracked id
	return classID;
}

void GameObj_Static::gameObj_addToDraw() {
	//TODO: Implement this stubbed out function
}
