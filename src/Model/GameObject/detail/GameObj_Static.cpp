	/// Definition Include
#include "../GameObj_Static.hpp"

	/// External Dependencies
#include <glm/gtc/matrix_transform.hpp>

	/// Internal Dependencies
#include "View/Renderer/Renderer.hpp"

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
	// Prepare for model position configuration
	glm::mat4 translation = glm::mat4(1.0f);

	// Configure the model position
	translation = glm::translate(translation, gameObj_pos);

	// Configure the model orientation
	translation = glm::rotate(translation, glm::radians(gameObj_rotateHori), glm::vec3(0.0f, 1.0f, 0.0f));
	translation = glm::rotate(translation, glm::radians(gameObj_rotateVert), glm::vec3(1.0f, 0.0f, 0.0f));
	translation = glm::rotate(translation, glm::radians(gameObj_rotateTilt), glm::vec3(0.0f, 0.0f, 1.0f));

	// Add the GameObject's model to the renderer's draw call
	Renderer::addToDraw(translation, gameObj_getModelID());
}
