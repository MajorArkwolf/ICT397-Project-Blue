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

void GameObj_LuaHelper::gameObj_setPos_X(float posX) {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		return;

	// Perform the operation
	gameObj_pointer.get()->gameObj_pos[0] = posX;
}

float GameObj_LuaHelper::gameObj_getPos_Y() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_pos[1];
}

void GameObj_LuaHelper::gameObj_setPos_Y(float posY) {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		return;

	// Perform the operation
	gameObj_pointer.get()->gameObj_pos[1] = posY;
}

float GameObj_LuaHelper::gameObj_getPos_Z() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_pos[2];
}

void GameObj_LuaHelper::gameObj_setPos_Z(float posZ) {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		return;

	// Perform the operation
	gameObj_pointer.get()->gameObj_pos[2] = posZ;
}

float GameObj_LuaHelper::gameObj_getYaw() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_yaw;
}

void GameObj_LuaHelper::gameObj_setYaw(float yaw) {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		return;

	// Perform the operation
	gameObj_pointer.get()->gameObj_yaw = yaw;
}

float GameObj_LuaHelper::gameObj_getPitch() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_pitch;
}

void GameObj_LuaHelper::gameObj_setPitch(float pitch) {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		return;

	// Perform the operation
	gameObj_pointer.get()->gameObj_pitch = pitch;
}

float GameObj_LuaHelper::gameObj_getRoll() {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		throw std::string("Cannot provide return as GameObj_LuaHelper is in an invalid state!");

	// Perform the operation
	return gameObj_pointer.get()->gameObj_roll;
}

void GameObj_LuaHelper::gameObj_setRoll(float roll) {
	// Catch invalid state of the LuaHelper
	if (!gameObj_isValid())
		return;

	// Perform the operation
	gameObj_pointer.get()->gameObj_roll = roll;
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
