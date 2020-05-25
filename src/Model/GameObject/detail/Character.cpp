	/// Declaration Include
#include "../Character.hpp"

void GameObj_Character::status_assign(std::string key, float value) {
	// Perform the operation on the map
	statuses[key] = value;
}

bool GameObj_Character::status_has(std::string key) {
	// Perform the operation on the map
	return (statuses.find(key) != statuses.end());
}

float GameObj_Character::status_get(std::string key) {
	// Catch an invalid key
	if (!status_has(key))
		return 0.0f;

	// Perform the operation on the map
	return statuses.at(key);
}

void GameObj_Character::status_delete(std::string key) {
	// Perform the operation on the map
	statuses.erase(key);
}

void GameObj_Character::status_clear() {
	// Perform the operation on the map
	statuses.clear();
}
