	/// Definition Include
#include "../GameObj_Static.hpp"

GameObj_Static::GameObj_Static()
	: GameObj_Base() {
	// GameObj_Static has no unique attributes to initialise yet
}

GameObj_Static::GameObj_Static(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up)
	: GameObj_Base(path, physBody, position, look_at, look_up) {
	// GameObj_Static has no unique attributes to initialise yet
}

GameObj_Static::~GameObj_Static() {
	// GameObj_Static has no unique destruction procedure yet.
}

GameObjType GameObj_Static::gameObj_getTypeID() const {
	// Return a copy of the class's unique type identifier
	return _gameObj_getTypeID();
}

GameObjType GameObj_Static::_gameObj_getTypeID() {
	// Always return error indicator GAMEOBJ_STATIC, never return anything else.
	return GAMEOBJ_STATIC;
}

void GameObj_Static::gameObj_addToDraw() {
	//TODO: Implement this stubbed out function
}