	/// Definition Include
#include "../Static.hpp"

	/// External Dependencies
#include <glm/gtc/matrix_transform.hpp>

	/// Internal Dependencies
#include "../GameObject.hpp"

	/// Debugging Dependencies
#include <assert.h>

GameObj_Static::GameObj_Static()
	: GameObj_Base() {
	// Configure the Shader
	gameObj_shader = std::make_shared<Shader>(Shader("res/shader/vertshader.vs", "res/shader/fragshader.fs"));
}

GameObj_Static::GameObj_Static(std::string path, unsigned long int physBody, glm::vec3 position, float rotateHori, float rotateVert, float rotateTilt)
	: GameObj_Base(path, physBody, position, rotateHori, rotateVert, rotateTilt) {
	// Configure the Shader
	gameObj_shader = std::make_shared<Shader>(Shader("res/shader/vertshader.vs", "res/shader/fragshader.fs"));
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

void GameObj_Static::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
	// Temporarily removed for the moment, make sure to re-implement this!
	assert(false);
}
