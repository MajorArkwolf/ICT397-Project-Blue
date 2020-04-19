#pragma once

	/// System Dependencies
#include <memory>

	/// Internal Dependencies
#include "GameObject.hpp"
#include "Static.hpp"
#include "Player.hpp"
#include "NPC.hpp"

class GameObj_LuaHelper {
public:
		//! Default constructor, sets the target to nullptr
	GameObj_LuaHelper();

		/*!
		 * @brief Lua GameObject Helper class constructor.
		 * @note Used for Lua to interact directly with the GameObjects stored within C++.
		 */
	GameObj_LuaHelper(std::shared_ptr<GameObj_Base> target);

		//! Checks if the managed GameObject is valid for use by Lua
	bool gameObj_isValid();

	BlueEngine::ID gameObj_getUniqueID();

	GameObjType gameObj_getTypeID();

	void gameObj_setModel(std::string path);

	std::size_t gameObj_getModelID();

	std::string gameObj_getModelPath();

	float gameObj_getPos_X();

	void gameObj_setPos_X(float posX);

	float gameObj_getPos_Y();

	void gameObj_setPos_Y(float posY);

	float gameObj_getPos_Z();

	void gameObj_setPos_Z(float posZ);

	float gameObj_getYaw();

	void gameObj_setYaw(float yaw);

	float gameObj_getPitch();

	void gameObj_setPitch(float pitch);

	float gameObj_getRoll();

	void gameObj_setRoll(float roll);

	long unsigned int gameObj_getPhysBody();

	void gameObj_setPhysBody(long unsigned int physBody);

private:
	std::shared_ptr<GameObj_Base> gameObj_pointer;
};
