	/// Definition Include
#include "../Static.hpp"

	/// External Dependencies
#include <glm/gtc/matrix_transform.hpp>

	/// Internal Dependencies
#include "View/Renderer/Renderer.hpp"
#include "../GameObject.hpp"

	/// Debugging Dependencies
#include <assert.h>

GameObj_Static::GameObj_Static()
	: GameObj_Base() {
	// GameObj_Static has no unique attributes to initialise yet
}

GameObj_Static::GameObj_Static(std::string path, unsigned long int physBody, glm::vec3 position, float rotateHori, float rotateVert, float rotateTilt)
	: GameObj_Base(path, physBody, position, rotateHori, rotateVert, rotateTilt) {
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
	// Temporarily removed for the moment, make sure to re-implement this!
	assert(false);
}
