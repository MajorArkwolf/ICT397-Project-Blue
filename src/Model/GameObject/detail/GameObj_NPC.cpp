	/// Definition Include
#include "../GameObj_NPC.hpp"

GameObj_NPC::GameObj_NPC()
	: GameObj_Base() {
	// GameObj_NPC has no unique attributes to initialise yet
}

GameObj_NPC::GameObj_NPC(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up)
	: GameObj_Base(path, physBody, position, look_at, look_up) {
	// GameObj_NPC has no unique attributes to initialise yet
}

GameObj_NPC::~GameObj_NPC() {
	// GameObj_NPC has no unique destruction procedure yet.
}

GameObjType GameObj_NPC::gameObj_getTypeID() const {
	// Return a copy of the class's unique type identifier
	return _gameObj_getTypeID();
}

GameObjType GameObj_NPC::_gameObj_getTypeID() {
	// Always return error indicator GAMEOBJ_NPC, never return anything else.
	return GAMEOBJ_NPC;
}

void GameObj_NPC::gameObj_addToDraw() {
	//TODO: Implement this stubbed out function
}

