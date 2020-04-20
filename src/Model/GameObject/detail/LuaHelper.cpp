	/// Declaration Include
#include "../LuaHelper.hpp"

GameObj_LuaHelper::GameObj_LuaHelper(std::shared_ptr<GameObj_Base> target) {
	// Store the target GameObject
	gameObj_pointer = target;
}

BlueEngine::ID GameObj_LuaHelper::gameObj_getUniqueID() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_getUniqueID();
}

GameObjType GameObj_LuaHelper::gameObj_getTypeID() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_getTypeID();
}

void GameObj_LuaHelper::gameObj_setModel(std::string path) {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		return;

	// Perform the operation
	gameObj_pointer.get()->gameObj_setModel(path);
}

std::size_t GameObj_LuaHelper::gameObj_getModelID() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_getModelID();
}

std::string GameObj_LuaHelper::gameObj_getModelPath() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_getModelPath();
}

float GameObj_LuaHelper::gameObj_getPos_X() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_pos[0];
}

float GameObj_LuaHelper::gameObj_getPos_Y() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_pos[1];
}

float GameObj_LuaHelper::gameObj_getPos_Z() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_pos[2];
}

void GameObj_LuaHelper::gameObj_setPos(float posX, float posY, float posZ) {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		return;

	// Perform the operation
	gameObj_pointer.get()->gameObj_pos[0] = posX;
	gameObj_pointer.get()->gameObj_pos[1] = posY;
	gameObj_pointer.get()->gameObj_pos[2] = posZ;
}

float GameObj_LuaHelper::gameObj_getRotation_yaw() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_rotation[0];
}

float GameObj_LuaHelper::gameObj_getRotation_pitch() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_rotation[1];
}

float GameObj_LuaHelper::gameObj_getRotation_roll() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_rotation[2];
}

void GameObj_LuaHelper::gameObj_setRotation(float yaw, float pitch, float roll) {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		return;

	// Perform the operation
	gameObj_pointer.get()->gameObj_rotation[0] = yaw;
	gameObj_pointer.get()->gameObj_rotation[1] = pitch;
	gameObj_pointer.get()->gameObj_rotation[2] = roll;
}

float GameObj_LuaHelper::gameObj_getScale_X() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_scale[0];
}

float GameObj_LuaHelper::gameObj_getScale_Y() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_scale[1];
}

float GameObj_LuaHelper::gameObj_getScale_Z() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_scale[2];
}

void GameObj_LuaHelper::gameObj_setScale(float scaleX, float scaleY, float scaleZ) {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		return;

	// Perform the operation
	gameObj_pointer.get()->gameObj_scale[0] = scaleX;
	gameObj_pointer.get()->gameObj_scale[1] = scaleY;
	gameObj_pointer.get()->gameObj_scale[2] = scaleZ;
}

long unsigned int GameObj_LuaHelper::gameObj_getPhysBody() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_physBody;
}

void GameObj_LuaHelper::gameObj_setPhysBody(long unsigned int physBody) {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		return;

	// Perform the operation
	gameObj_pointer.get()->gameObj_physBody = physBody;
}

bool GameObj_LuaHelper::gameObj_isValid() {
	// The GameObject should be considered valid when the managed pointer is not nullptr
	return (gameObj_pointer.get() != nullptr);
}
