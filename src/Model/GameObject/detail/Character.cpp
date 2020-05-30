	/// Declaration Include
#include "../Character.hpp"

	/// Internal Dependencies
#include "../Types.hpp"

GameObj_Type GameObj_Character::type() const {
	// The Character GameObject will always return an indicator that its type is not valid.
	return GameObj_Type::Invalid;
}

void GameObj_Character::status_assign(std::string key, float value) {
	// Perform the operation on the map
	statuses[key] = value;
}

unsigned long long GameObj_Character::status_count() {
	// Return the amount of unique elements in the map
	return statuses.size();
}

bool GameObj_Character::status_has(std::string key) {
	// Perform the operation on the map
	return (statuses.find(key) != statuses.end());
}

std::vector<std::string> GameObj_Character::status_list() {
	// Keep track of the map keys
	std::vector<std::string> keys;

	// Iterate through the entire map
	for (auto i = statuses.begin(); i != statuses.end(); ++i)
	{
		// Append the currently processed status' key
		keys.push_back(i->first);
	}

	// Return the gathered keys
	return keys;
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
