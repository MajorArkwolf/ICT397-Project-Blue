	/// Definition Include
#include "../Player.hpp"

	/// External Dependencies
#include <glm/gtc/matrix_transform.hpp>

	/// Internal Dependencies
#include "View/Renderer/Renderer.hpp"
#include "../GameObject.hpp"

	/// Debugging Dependencies
#include <assert.h>

GameObj_Player::GameObj_Player()
	: GameObj_Base() {
	// Configure the Shader
	gameObj_shader = std::make_shared<Shader>(Shader("res/shader/vertshader.vs", "res/shader/fragshader.fs"));
}

GameObj_Player::GameObj_Player(std::string path, unsigned long int physBody, glm::vec3 position, float rotateHori, float rotateVert, float rotateTilt)
	: GameObj_Base(path, physBody, position, rotateHori, rotateVert, rotateTilt) {
	// Configure the Shader
	gameObj_shader = std::make_shared<Shader>(Shader("res/shader/vertshader.vs", "res/shader/fragshader.fs"));
}

GameObj_Player::~GameObj_Player() {
	// GameObj_Player has no unique destruction procedure yet.
}

GameObjType GameObj_Player::gameObj_getTypeID() const {
	// Return a copy of the class's unique type identifier
	return _gameObj_getTypeID();
}

GameObjType GameObj_Player::_gameObj_getTypeID() {
	// Always return error indicator GAMEOBJ_PLAYER, never return anything else.
	return GAMEOBJ_PLAYER;
}

void GameObj_Player::gameObj_addToDraw() {
	// Temporarily removed for the moment, make sure to re-implement this!
	assert(false);
}

void GameObj_Player::status_assign(std::string key, float value) {
	// Perform the operation on the map
	player_statuses[key] = value;
}

bool GameObj_Player::status_has(std::string key) {
	// Perform the operation on the map
	return (player_statuses.find(key) != player_statuses.end());
}

float GameObj_Player::status_get(std::string key) {
	// Catch an invalid key
	if (!status_has(key))
		return 0.0f;
	
	// Perform the operation on the map
	return player_statuses.at(key);
}

void GameObj_Player::status_delete(std::string key) {
	// Perform the operation on the map
	player_statuses.erase(key);
}

void GameObj_Player::status_deleteAll() {
	// Perform the operation on the map
	player_statuses.clear();
}

void GameObj_Player::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
	// Temporarily removed for the moment, make sure to re-implement this!
	assert(false);
}
