	/// Definition Include
#include "../GameObj_Static.hpp"

GameObj_Static::GameObj_Static() {
	// GameObj_Static has no unique attributes to initialise yet
}

GameObj_Static::GameObj_Static(std::string path, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up) {
	// GameObj_Static has no unique attributes to initialise yet
}

GameObj_Static::~GameObj_Static() {
	// GameObj_Static has no unique destruction procedure yet.
}

GameObjectType GameObj_Static::gameObj_getType() const {
	// Keep track of this class's identifier for its type
	static const GameObjectType classID = gameObj_getType();

	// Return a copy of the tracked id
	return classID;
}
