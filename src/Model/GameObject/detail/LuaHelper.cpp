	/// Declaration Include
#include "../LuaHelper.hpp"

GameObj_LuaHelper::GameObj_LuaHelper() {
	// Set an invalid target GameObject
	gameObj_pointer = nullptr;
}

GameObj_LuaHelper::GameObj_LuaHelper(std::shared_ptr<GameObj_Base> target) {
	// Store the target GameObject
	gameObj_pointer = target;
}

BlueEngine::ID GameObj_LuaHelper::gameObj_getUniqueID() {
	return gameObj_pointer.get()->gameObj_getUniqueID();
}

GameObjType GameObj_LuaHelper::gameObj_getTypeID() {
	return gameObj_pointer.get()->gameObj_getTypeID();
}

void GameObj_LuaHelper::gameObj_setModel(std::string path) {
	gameObj_pointer.get()->gameObj_setModel(path);
}

std::size_t GameObj_LuaHelper::gameObj_getModelID() {
	return gameObj_pointer.get()->gameObj_getModelID();
}

std::string GameObj_LuaHelper::gameObj_getModelPath() {
	return gameObj_pointer.get()->gameObj_getModelPath();
}

float GameObj_LuaHelper::gameObj_getPos_X() {
	return gameObj_pointer.get()->gameObj_pos[0];
}

void GameObj_LuaHelper::gameObj_setPos_X(float posX) {
	gameObj_pointer.get()->gameObj_pos[0] = posX;
}

float GameObj_LuaHelper::gameObj_getPos_Y() {
	return gameObj_pointer.get()->gameObj_pos[1];
}

void GameObj_LuaHelper::gameObj_setPos_Y(float posY) {
	gameObj_pointer.get()->gameObj_pos[1] = posY;
}

float GameObj_LuaHelper::gameObj_getPos_Z() {
	return gameObj_pointer.get()->gameObj_pos[2];
}

void GameObj_LuaHelper::gameObj_setPos_Z(float posZ) {
	gameObj_pointer.get()->gameObj_pos[2] = posZ;
}

float GameObj_LuaHelper::gameObj_getYaw() {
	return gameObj_pointer.get()->gameObj_yaw;
}

void GameObj_LuaHelper::gameObj_setYaw(float yaw) {
	gameObj_pointer.get()->gameObj_yaw = yaw;
}

float GameObj_LuaHelper::gameObj_getPitch() {
	return gameObj_pointer.get()->gameObj_pitch;
}

void GameObj_LuaHelper::gameObj_setPitch(float pitch) {
	gameObj_pointer.get()->gameObj_pitch = pitch;
}

float GameObj_LuaHelper::gameObj_getRoll() {
	return gameObj_pointer.get()->gameObj_roll;
}

void GameObj_LuaHelper::gameObj_setRoll(float roll) {
	gameObj_pointer.get()->gameObj_roll = roll;
}

long unsigned int GameObj_LuaHelper::gameObj_getPhysBody() {
	return gameObj_pointer.get()->gameObj_physBody;
}

void GameObj_LuaHelper::gameObj_setPhysBody(long unsigned int physBody) {
	gameObj_pointer.get()->gameObj_physBody = physBody;
}

bool GameObj_LuaHelper::gameObj_isValid() {
	// The GameObject should be considered valid when the managed pointer is not nullptr
	return (gameObj_pointer.get() != nullptr);
}
