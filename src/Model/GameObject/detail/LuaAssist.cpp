	/// Declaration Include
#include "LuaAssist.hpp"

GameObj_Type GameObj_LuaHelper::Invalid()
{ return GameObj_Type::Invalid; }

GameObj_Type GameObj_LuaHelper::Static()
{ return GameObj_Type::Static; }

GameObj_Type GameObj_LuaHelper::Item()
{ return GameObj_Type::Item; };

GameObj_Type GameObj_LuaHelper::Player()
{ return GameObj_Type::Player; };

GameObj_Type GameObj_LuaHelper::NPC()
{ return GameObj_Type::NPC; };

GameObj_LuaHelper::CharacterWrapper::CharacterWrapper(std::shared_ptr<GameObj_Character> target) {
	// Just store the pointer
	gameObj = target;
}

GameObj_Type GameObj_LuaHelper::CharacterWrapper::type() {
	// Perform the operation on the wrapped GameObject
	return gameObj->type();
}

void GameObj_LuaHelper::CharacterWrapper::status_assign(std::string key, float value) {
	// Perform the operation on the wrapped GameObject
	gameObj->status_assign(key, value);
}

unsigned long long GameObj_LuaHelper::CharacterWrapper::status_count() {
	// Perform the operation on the wrapped GameObject
	return gameObj->status_count();
}

bool GameObj_LuaHelper::CharacterWrapper::status_has(std::string key) {
	// Perform the operation on the wrapped GameObject
	return gameObj->status_has(key);
}

std::vector<std::string> GameObj_LuaHelper::CharacterWrapper::status_list() {
	// Perform the operation on the wrapped GameObject
	return gameObj->status_list();
}

float GameObj_LuaHelper::CharacterWrapper::status_get(std::string key) {
	// Perform the operation on the wrapped GameObject
	return gameObj->status_get(key);
}

void GameObj_LuaHelper::CharacterWrapper::status_delete(std::string key) {
	// Perform the operation on the wrapped GameObject
	gameObj->status_delete(key);
}

void GameObj_LuaHelper::CharacterWrapper::status_clear() {
	// Perform the operation on the wrapped GameObject
	gameObj->status_clear();
}

BlueEngine::ID GameObj_LuaHelper::CharacterWrapper::npc_context() {
	// Catch a VALID type
	if (gameObj->type() == GameObj_Type::NPC)
	{
		// Perform the operation on the wrapped GameObject
		return dynamic_cast<GameObj_NPC*>(gameObj.get())->context();
	}

	// Return default if not the proper type
	return 0u;
}

bool GameObj_LuaHelper::CharacterWrapper::is_valid() {
	// Check for nullptr being wrapped
	if (gameObj == nullptr)
	{
		// Catch and return indicator of invalid wrapper state
		return false;
	}

	// Return the type check comparison
	return ((gameObj->type() == GameObj_Type::Player) || (gameObj->type() == GameObj_Type::NPC));
}