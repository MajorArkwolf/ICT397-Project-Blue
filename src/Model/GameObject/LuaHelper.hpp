#pragma once

	/// System Dependencies
#include <memory>

	/// Internal Dependencies
#include "GameObject.hpp"

class GameObj_LuaHelper {
public:
		/*!
		 * @brief Lua GameObject Helper class constructor.
		 * @note Used for Lua to interact directly with the GameObjects stored within C++.
		 */
	GameObj_LuaHelper(std::shared_ptr<GameObj_Base> target);

		/*!
		 * @brief Checks if the managed GameObject is valid state for use.
		 * @return True if the gameObj is safefor use, false otherwise.
		 */
	bool gameObj_isValid();

		/*!
		 * @brief Returns a copy of this GameObject's unique identifier.
		 * @return An identifier value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	BlueEngine::ID gameObj_getUniqueID();

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return The GameObject's type identifier value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	GameObjType gameObj_getTypeID();

		/*!
		 * @brief Tracks and calls for the loading of an external model file.
		 * @param [in] path The path to a target external model file for this GameObject.
		 * @warning Will silently fail if the LuaHelper is in an invalid state!
		 */
	void gameObj_setModel(std::string path);

		/*!
		 * @brief Returns the model for this GameObject.
		 * @return The ID of the GameObject's tracked model.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	std::size_t gameObj_getModelID();

		/*!
		 * @brief Returns the model for this GameObject.
		 * @return The ID of the tracked model.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	std::string gameObj_getModelPath();

		/*!
		 * @brief Gathers a copy of the x-coordinate for the GameObject's position in 3D space.
		 * @return A copy of the GameObject's gameObj_pos x-coordinate.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getPos_X();

		/*!
		 * @brief Sets the value of the x-coordinate for the GameObject's position in 3D space.
		 * @param [in] posX The GameObject's new position x-coordinate value.
		 * @warning Will silently fail if the LuaHelper is in an invalid state!
		 */
	void gameObj_setPos_X(float posX);

		/*!
		 * @brief Gathers a copy of the y-coordinate for the GameObject's position in 3D space.
		 * @return A copy of the GameObject's gameObj_pos y-coordinate.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getPos_Y();

		/*!
		 * @brief Sets the value of the y-coordinate for the GameObject's position in 3D space.
		 * @param [in] posY The GameObject's new position y-coordinate value.
		 * @warning Will silently fail if the LuaHelper is in an invalid state!
		 */
	void gameObj_setPos_Y(float posY);

		/*!
		 * @brief Gathers a copy of the z-coordinate for the GameObject's position in 3D space.
		 * @return A copy of the GameObject's gameObj_pos z-coordinate.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getPos_Z();

		/*!
		 * @brief Sets the value of the z-coordinate for the GameObject's position in 3D space.
		 * @param [in] posZ The GameObject's new position z-coordinate value.
		 * @warning Will silently fail if the LuaHelper is in an invalid state!
		 */
	void gameObj_setPos_Z(float posZ);

		/*!
		 * @brief Gathers a copy of the yaw radians for the GameObject's rotation.
		 * @return A copy of the GameObject's gameObj_yaw value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getYaw();

		/*!
		 * @brief Sets the value of the yaw radians for the GameObject's rotation.
		 * @param [in] yaw The GameObject's new position gameObj_yaw value.
		 * @warning Will silently fail if the LuaHelper is in an invalid state!
		 */
	void gameObj_setYaw(float yaw);

		/*!
		 * @brief Gathers a copy of the pitch radians for the GameObject's rotation.
		 * @return A copy of the GameObject's gameObj_pitch value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getPitch();

		/*!
		 * @brief Sets the value of the pitch radians for the GameObject's rotation.
		 * @param [in] pitch The GameObject's new position gameObj_pitch value.
		 * @warning Will silently fail if the LuaHelper is in an invalid state!
		 */
	void gameObj_setPitch(float pitch);

		/*!
		 * @brief Gathers a copy of the roll radians for the GameObject's rotation.
		 * @return A copy of the GameObject's gameObj_roll value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getRoll();

		/*!
		 * @brief Sets the value of the roll radians for the GameObject's rotation.
		 * @param [in] roll The GameObject's new position gameObj_roll value.
		 * @warning Will silently fail if the LuaHelper is in an invalid state!
		 */
	void gameObj_setRoll(float roll);

		/*!
		 * @brief Gathers a copy of the GameObject's physics body identifier.
		 * @return A copy of the GameObject's gameObj_physBody value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	long unsigned int gameObj_getPhysBody();

		/*!
		 * @brief Sets the value of the GameObject's physics body identifier.
		 * @param [in] physBody The GameObject's new position gameObj_physBody value.
		 * @warning Will silently fail if the LuaHelper is in an invalid state!
		 */
	void gameObj_setPhysBody(long unsigned int physBody);

private:
		//! Stores a smart pointer reference to the GameObject encapsulated.
	std::shared_ptr<GameObj_Base> gameObj_pointer;
};
