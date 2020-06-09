	/// Declaration Include
#include <Controller/ResourceManager.hpp>
#include "../Character.hpp"

	/// Internal Dependencies
#include "Model/GameObject/Types.hpp"
#include "LuaAssist.hpp"

GameObj_Type GameObj_Character::type() const {
	// The Character GameObject will always return an indicator that its type is not valid.
	return GameObj_Type::Invalid;
}

void GameObj_Character::status_assign(const std::string& key, float value) {
	// Perform the operation on the map
	statuses[key] = value;
}

unsigned long long GameObj_Character::status_count() {
	// Return the amount of unique elements in the map
	return statuses.size();
}

bool GameObj_Character::status_has(const std::string& key) {
	// Perform the operation on the map
	return (statuses.find(key) != statuses.end());
}

std::vector<std::string> GameObj_Character::status_list() {
	// Keep track of the map keys
	std::vector<std::string> keys;

	// Iterate through the entire map
	for (auto & statuse : statuses)
	{
		// Append the currently processed status' key
		keys.push_back(statuse.first);
	}

	// Return the gathered keys
	return keys;
}

float GameObj_Character::status_get(const std::string& key) {
	// Catch an invalid key
	if (!status_has(key))
		return 0.0f;

	// Perform the operation on the map
	return statuses.at(key);
}

void GameObj_Character::status_delete(const std::string& key) {
	// Perform the operation on the map
	statuses.erase(key);
}

void GameObj_Character::status_clear() {
	// Perform the operation on the map
	statuses.clear();
}

void GameObj_Character::lua_init_register() {
	// Prevent this being called more than once
	static bool isRegistered = false;
	if (isRegistered)
		return;

	// Register the Character GameObject class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.deriveClass<GameObj_Character, GameObj_Base>("GameObject_Character")
			.addFunction("status_assign", &GameObj_Character::status_assign)
			.addFunction("status_count", &GameObj_Character::status_count)
			.addFunction("status_has", &GameObj_Character::status_has)
			.addFunction("status_list", &GameObj_Character::status_list)
			.addFunction("status_get", &GameObj_Character::status_get)
			.addFunction("status_delete", &GameObj_Character::status_delete)
			.addFunction("status_clear", &GameObj_Character::status_clear)
		.endClass();

	// Prevent re-registration
	isRegistered = true;
}
