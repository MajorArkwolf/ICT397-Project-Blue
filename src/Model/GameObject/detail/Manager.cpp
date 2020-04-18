	/// Declaration Include
#include "../Manager.hpp"

GameObj_Manager::GameObj_Manager() {
	// Nothing to happen in here, all attributes automatically initialise themselves.
}

GameObj_Manager::~GameObj_Manager() {
	// Remove all GameObjects from the manager, probably excessive due to attribute behaviour.
	clear();
}

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

void GameObj_Manager::remove(BlueEngine::ID identifier) {
	// Just remove the specified GameObject from the manager, don't directly call for it to be removed from memory
	managedGameObjects.erase(identifier);
}

void GameObj_Manager::clear() {
	// Just remove the GameObjects from the manager, don't directly call for it to be removed from memory
	managedGameObjects.clear();
}
