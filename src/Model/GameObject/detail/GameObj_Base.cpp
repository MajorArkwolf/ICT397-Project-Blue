	/// Definition Include
#include "../GameObj_Base.hpp"

	/// External Dependencies
#include <limits>

	/// Internal Dependencies
#include "../../../Controller/ResourceManager.hpp"

GameObj_Base::GameObj_Base() {
	// Set the initial values of the GameObject's 3D position attributes
	gameObj_pos  = {0.0f, 0.0f, 0.0f};
	gameObj_lookAt = {0.0f, 0.0f, 1.0f};
	gameObj_lookUp = {0.0f, 1.0f, 0.0f};

	// Set the initial stored identifiers
	gameObj_modelId = std::numeric_limits<std::size_t>::min();
	gameObj_modelPath = "";
	gameObj_physBody = 0ul;
}

GameObj_Base::GameObj_Base(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 look_at,
 glm::vec3 look_up) {
	// Set the initial values of the GameObject's 3D position attributes
	gameObj_pos  = position;
	gameObj_lookAt = look_at;
	gameObj_lookUp = look_up;

	// Set the initial stored identifiers
	gameObj_setModel(path);
	gameObj_physBody = physBody;
}

GameObj_Base::~GameObj_Base() {
	// GameObj_Base has no unique destruction procedure yet.
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