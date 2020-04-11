	/// Definition Include
#include "../GameObject_Base.hpp"

	/// External Dependencies
#include <limits>

	/// Internal Dependencies
#include "../../Models/ModelManager.hpp"

GameObject_Base::GameObject_Base() {
	// Set the initial values of the GameObject's 3D position attributes
    gameObj_pos  = {0.0f, 0.0f, 0.0f};
    gameObj_lookAt = {0.0f, 0.0f, 1.0f};
    gameObj_lookUp = {0.0f, 1.0f, 0.0f};

	// Set the initial stored ID
    gameObj_modelId = std::numeric_limits<std::size_t>::min();
}

GameObject_Base::GameObject_Base(std::string path, glm::vec3 position, glm::vec3 look_at,
 glm::vec3 look_up) {
	// Set the initial values of the GameObject's 3D position attributes
    gameObj_pos  = position;
    gameObj_lookAt = look_at;
    gameObj_lookUp = look_up;

	// Set the initial stored ID
	gameObj_setModel(path);
}

void GameObject_Base::gameObj_setModel(std::string path) {
	// Call the Model Loader and keep track of what it spits out
    gameObj_modelId = ModelManager::GetModelID();
}

std::size_t GameObject_Base::gameObj_getModel() {
	// Return a copy of the stored path
	return model_path;
}
