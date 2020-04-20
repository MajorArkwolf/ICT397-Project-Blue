	/// Definition Include
#include "../Base.hpp"

	/// External Dependencies
#include <limits>

	/// Internal Dependencies
#include "Controller/ResourceManager.hpp"
#include "../GameObject.hpp"

GameObj_Base::GameObj_Base() {
	// Set the initial values of the GameObject's 3D position attributes
	gameObj_pos  = { 0.0f, 0.0f, 0.0f };
	gameObj_rotation = { 0.0f, 0.0f, 0.0f };
	gameObj_scale = { 1.0f, 1.0f, 1.0f };

	// Set the initial stored identifiers
	gameObj_modelId = std::numeric_limits<std::size_t>::min();
	gameObj_modelPath = "";
	gameObj_physBody = 0ul;
	gameObj_uniqueId = BlueEngine::IDTracker::getInstance().getID();
}

GameObj_Base::GameObj_Base(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
	// Set the initial values of the GameObject's 3D position attributes
	gameObj_pos  = position;
	gameObj_rotation = rotation;
	gameObj_scale = scale;

	// Set the initial stored identifiers
	gameObj_setModel(path);
	gameObj_modelPath = path;
	gameObj_physBody = physBody;
	gameObj_uniqueId = BlueEngine::IDTracker::getInstance().getID();
}

GameObj_Base::~GameObj_Base() {
	// GameObj_Base has no unique destruction procedure yet.
}

BlueEngine::ID GameObj_Base::gameObj_getUniqueID()
{
	// Return a copy of the GameObject's unique identifier
	return gameObj_uniqueId;
}

GameObjType GameObj_Base::gameObj_getTypeID() const {
	// Always return error indicator GAMEOBJ_INVALID, never return anything else.
	return GAMEOBJ_INVALID;
}

void GameObj_Base::gameObj_setModel(std::string path) {
	// Store the path
	gameObj_modelPath = path;
	
	// Call the Model Loader and keep track of what it spits out
	auto resmanager = ResourceManager::getInstance();
	gameObj_modelId = resmanager.getModelID(gameObj_modelPath);
}

std::size_t GameObj_Base::gameObj_getModelID() {
	// Return a copy of the stored model identifier
	return gameObj_modelId;
}

std::string GameObj_Base::gameObj_getModelPath() {
	// return a copy of the stored model path
	return gameObj_modelPath;
}
