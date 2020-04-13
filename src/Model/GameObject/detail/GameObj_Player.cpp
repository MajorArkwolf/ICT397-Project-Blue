	/// Definition Include
#include "../GameObj_Player.hpp"

GameObj_Player::GameObj_Player()
	: GameObject_Base() {
	// GameObj_Player has no unique attributes to initialise yet
}

GameObj_Player::GameObj_Player(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up)
	: GameObject_Base(path, physBody, position, look_at, look_up) {
	// GameObj_Player has no unique attributes to initialise yet
}

GameObj_Player::~GameObj_Player() {
	// GameObj_Player has no unique destruction procedure yet.
}

GameObjectType GameObj_Player::gameObj_getTypeID() const {
	// Return a copy of the class's unique type identifier
	return _gameObj_getTypeID();
}

GameObjectType GameObj_Player::_gameObj_getTypeID() {
	// Always return error indicator GAMEOBJ_PLAYER, never return anything else.
	return GAMEOBJ_PLAYER;
}

void GameObj_Player::gameObj_addToDraw() {
	//TODO: Implement this stubbed out function
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
