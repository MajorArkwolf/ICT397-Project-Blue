	/// Declaration Include
#include "../Manager.hpp"

	/// Internal Dependencies
#include "Controller/Engine/LuaManager.hpp"
#include "Controller/Factory/GameAssetFactory.hpp"

void GameObj_Manager::insert(std::shared_ptr<GameObj_Base> object) {
	// Catch and stop processing nullptr
	if (!object)
		return;
	
	// Assign the new object for management into the map
	managedGameObjects[object.get()->gameObj_getUniqueID()] = object;
}

std::shared_ptr<GameObj_Base> GameObj_Manager::get(BlueEngine::ID identifier)
{
	// Catch any errors thrown
	try {
		// Attempt to find and return a copy of the requested GameObject
		return managedGameObjects.at(identifier);
	}
	catch (...) {
		// Indicate no element with specified found
		return nullptr;
	}
}

void GameObj_Manager::addAllToDraw() {
	// Process all of the stored GameObjects
	for (auto i = managedGameObjects.begin(); i != managedGameObjects.end(); ++i)
	{
		// Call the currently accessed GameObject's addToDraw function
		i->second.get()->gameObj_addToDraw();
	}
}

void GameObj_Manager::remove(BlueEngine::ID identifier) {
	// Just remove the specified GameObject from the manager, don't directly call for it to be removed from memory
	managedGameObjects.erase(identifier);
}

void GameObj_Manager::clear() {
	// Just remove the GameObjects from the manager, don't directly call for it to be removed from memory
	managedGameObjects.clear();
}

void GameObj_Manager::process_all(GameObj_ProcessFunc function) {
	// Catch invalid function pointer
	if (function == nullptr)
		return;

	// Loop through all of the stored GameObjects
	for (auto i = managedGameObjects.begin(); i != managedGameObjects.end(); ++i)
	{
		// Pass the currently processed GameObject to the provided function
		function(i->second);
	}
}

BlueEngine::ID GameObj_Manager::lua_add(GameObjType type) {
	// Call the Factory Constructor to generate and insert a new GameObject
	std::shared_ptr<GameObj_Base> temp = Controller::Factory::get().GameObject(type);
	// Catch any error from the Factory output
	if (temp == nullptr)
	{
		// Don't store anything, just return an indicator of failure
		return 0u;
	}

	// On success, store the factory output and return the GameObject's identifier
	insert(temp);
	return temp->gameObj_getUniqueID();
}

GameObj_LuaHelper GameObj_Manager::lua_get(BlueEngine::ID identifier) {
	//Return the outcome from get() encapsulated in a LuaHelper GameObject
	return GameObj_LuaHelper(get(identifier));
}

void GameObj_Manager::init() {
	// Prevent registering multiple times
	static bool is_registered = false;
	if (is_registered)
		return;

	// Register the LuaHelper class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginClass<GameObj_LuaHelper>("GameObject")
			.addFunction("isValid", &GameObj_LuaHelper::gameObj_isValid)
			.addFunction("getUniqueID", &GameObj_LuaHelper::gameObj_getUniqueID)
			.addFunction("getTypeID", &GameObj_LuaHelper::gameObj_getTypeID)
			.addFunction("setModel", &GameObj_LuaHelper::gameObj_setModel)
			.addFunction("getModelID", &GameObj_LuaHelper::gameObj_getModelID)
			.addFunction("getModelPath", &GameObj_LuaHelper::gameObj_getModelPath)
			.addFunction("getPos_X", &GameObj_LuaHelper::gameObj_getPos_X)
			.addFunction("getPos_Y", &GameObj_LuaHelper::gameObj_getPos_Y)
			.addFunction("getPos_Z", &GameObj_LuaHelper::gameObj_getPos_Z)
			.addFunction("setPos", &GameObj_LuaHelper::gameObj_setPos)
			.addFunction("getRotation_yaw", &GameObj_LuaHelper::gameObj_getRotation_yaw)
			.addFunction("getRotation_pitch", &GameObj_LuaHelper::gameObj_getRotation_pitch)
			.addFunction("getRotation_roll", &GameObj_LuaHelper::gameObj_getRotation_roll)
			.addFunction("getScale_X", &GameObj_LuaHelper::gameObj_getScale_X)
			.addFunction("getScale_Y", &GameObj_LuaHelper::gameObj_getScale_Y)
			.addFunction("getScale_Z", &GameObj_LuaHelper::gameObj_getScale_Z)
			.addFunction("setScale", &GameObj_LuaHelper::gameObj_setScale)
			.addFunction("setRotation", &GameObj_LuaHelper::gameObj_setRotation)
			.addFunction("getPhysBody", &GameObj_LuaHelper::gameObj_getPhysBody)
			.addFunction("setPhysBody", &GameObj_LuaHelper::gameObj_setPhysBody)
		.endClass();

	// Register the Manager class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("GameObject_Manager")
			.addFunction("add", &GameObj_Manager::lua_add)
			.addFunction("get", &GameObj_Manager::lua_get)
			.addFunction("remove", &GameObj_Manager::remove)
			.addFunction("clear", &GameObj_Manager::clear)
		.endNamespace();

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginNamespace("TerrainFactory")
            .addProperty ("chunkSize", &Controller::TerrainFactory::LuaMapSize)
            .addFunction("heightAt", &Controller::TerrainFactory::LuaBLHeight)
        .endNamespace();
	// Prevent the registration with lua occuring multiple times
	is_registered = true;
}

	/// Static Initialisation
std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>> GameObj_Manager::managedGameObjects = std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>>();
