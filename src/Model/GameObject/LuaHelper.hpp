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
		 * @brief Gathers a copy of the y-coordinate for the GameObject's position in 3D space.
		 * @return A copy of the GameObject's gameObj_pos y-coordinate.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getPos_Y();

		/*!
		 * @brief Gathers a copy of the z-coordinate for the GameObject's position in 3D space.
		 * @return A copy of the GameObject's gameObj_pos z-coordinate.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getPos_Z();

		/*!
		 * @brief Sets the GameObject's position in 3D space.
		 * @param [in] posX The GameObject's new position along the x-coordinate.
		 * @param [in] posY The GameObject's new position along the y-coordinate.
		 * @param [in] posZ The GameObject's new position along the z-coordinate.
		 * @warning Will silently fail if the LuaHelper is in an invalid state!
		 */
	void gameObj_setPos(float posX, float posY, float posZ);

		/*!
		 * @brief Gathers a copy of the yaw (in degrees) for the GameObject's rotation.
		 * @return A copy of the GameObject's gameObj_rotation[0] value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getRotation_yaw();

		/*!
		 * @brief Gathers a copy of the pitch (in degrees) for the GameObject's rotation.
		 * @return A copy of the GameObject's gameObj_rotation[1] value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getRotation_pitch();

		/*!
		 * @brief Gathers a copy of the roll (in degrees) for the GameObject's rotation.
		 * @return A copy of the GameObject's gameObj_rotation[2] value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getRotation_roll();

		/*!
		 * @brief Sets the GameObject's rotation properties.
		 * @param [in] yaw The new yaw rotation value (in degrees).
		 * @param [in] pitch The new pitch rotation value (in degrees).
		 * @param [in] roll The new roll rotation value (in degrees).
		 * @warning Will silently fail if the LuaHelper is in an invalid state!
		 */
	void gameObj_setRotation(float yaw, float pitch, float roll);

		/*!
		 * @brief Gathers a copy of the GameObject's scale along the x axis.
		 * @return A copy of the GameObject's gameObj_scale[0] value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getScale_X();

		/*!
		 * @brief Gathers a copy of the GameObject's scale along the y axis.
		 * @return A copy of the GameObject's gameObj_scale[1] value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getScale_Y();

		/*!
		 * @brief Gathers a copy of the GameObject's scale along the z axis.
		 * @return A copy of the GameObject's gameObj_scale[2] value.
		 * @exception std::string Cannot provide return as GameObj_LuaHelper is in an invalid state!
		 */
	float gameObj_getScale_Z();

		/*!
		 * @brief Sets the GameObject's scale across its 3 dimensions.
		 * @param [in] scaleX The GameObject's new scale along the x-coordinate.
		 * @param [in] scaleY The GameObject's new scale along the y-coordinate.
		 * @param [in] scaleZ The GameObject's new scale along the z-coordinate.
		 * @warning Will silently fail if the LuaHelper is in an invalid state!
		 */
	void gameObj_setScale(float scaleX, float scaleY, float scaleZ);

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
