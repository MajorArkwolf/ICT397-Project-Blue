	/// Definition Include
#include "../GameObj_Player.hpp"

GameObj_Player::GameObj_Player() {
	// GameObj_Player has no unique attributes to initialise yet
}

GameObj_Player::GameObj_Player(std::string path, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up) {
	// GameObj_Player has no unique attributes to initialise yet
}

GameObjectType GameObj_Player::gameObj_getType() const {
	// Keep track of this class's identifier for its type
	static const GameObjectType classID = gameObj_getType();

	// Return a copy of the tracked id
	return classID;
}

GameObj_Player::status_assign(std::string key, float value) {
	// Perform the operation on the map
	player_statuses[key] = value;
}

GameObj_Player::status_has(std::string key) {
	// Perform the operation on the map
	return (player_statuses.has() != player_statuses.end());
}

GameObj_Player::status_get(std::string key) {
	// Catch an invalid key
	if (!status_has(key))
		return 0.0f;
	
	// Perform the operation on the map
	return player_statuses.at(key);
}

GameObj_Player::status_delete(std::string key) {
	// Perform the operation on the map
	player_statuses.erase(key);
}

GameObj_Player::status_deleteAll() {
	// Perform the operation on the map
	player_statuses.clear();
}
