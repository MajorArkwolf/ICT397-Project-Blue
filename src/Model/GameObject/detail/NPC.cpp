	/// Definition Include
#include "../NPC.hpp"

	/// External Dependencies
#include <glm/gtc/matrix_transform.hpp>

	/// Internal Dependencies
#include "View/Renderer/Renderer.hpp"
#include "../GameObject.hpp"

	/// Debugging Dependencies
#include <assert.h>

GameObj_NPC::GameObj_NPC()
	: GameObj_Base() {
	// GameObj_NPC has no unique attributes to initialise yet
}

GameObj_NPC::GameObj_NPC(std::string path, unsigned long int physBody, glm::vec3 position, float rotateHori, float rotateVert, float rotateTilt)
	: GameObj_Base(path, physBody, position, rotateHori, rotateVert, rotateTilt) {
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
	// Temporarily removed for the moment, make sure to re-implement this!
	assert(false);
}

