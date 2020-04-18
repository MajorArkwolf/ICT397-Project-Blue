#pragma once

	/// System Dependencies
#include <string>

	/// External Dependencies
#include <glm/glm.hpp>

	/// Internal Dependencies
#include "Controller/Engine/IDTracker.hpp"

	/*!
	 * @brief Declaration of the type for identifying different GameObject classes.
	 * @warning 0 is reserved for invalid identifiers and error reporting.
	 */
using GameObjType = unsigned int;

	//! The parent class for all child GameObjects.
class GameObj_Base
{
public:
		//! Initialises class attributes to their defaults.
	GameObj_Base();

		/*!
		 * @brief Initialises class attributes to custom values.
		 * @param [in] path The path to a target external model file for this GameObject.
		 * @param [in] physBody The identifier for the physical body for this GameObject.
		 * @param [in] position The position of the GameObject in the 3D environment.
		 * @param [in] yaw The GameObject's rotation, in degrees, along the Y axis.
		 * @param [in] pitch The GameObject's rotation, in degrees, along the X axis.
		 * @param [in] roll The GameObject's rotation, in degrees, along the Z axis.
		 */
	GameObj_Base(std::string path, unsigned long int physBody, glm::vec3 position, float yaw, float pitch, float roll);

		//! Virtual destructor.
	virtual ~GameObj_Base() = 0;

		/*!
		 * @brief Returns a copy of this GameObject's unique identifier.
		 * @return An identifier value.
		 */
	BlueEngine::ID gameObj_getUniqueID();

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return Always returns GAMEOBJ_INVALID for GameObj_Base.
		 * @warning Must be implemented by inheritors!
		 */
	virtual GameObjType gameObj_getTypeID() const = 0;

		/*!
		 * @brief Adds the GameObject to the draw queue.
		 * @warning Behaviour must be implemented by inheritors!
		 */
	virtual void gameObj_addToDraw() = 0;

		/*!
		 * @brief Tracks and calls for the loading of an external model file.
		 * @param [in] path The path to a target external model file for this GameObject.
		 * @see gameObj_modelId
		 * @see gameObj_modelPath
		 */
	void gameObj_setModel(std::string path);

		/*!
		 * @brief Returns the model for this GameObject.
		 * @return The ID of the tracked model.
		 * @see gameObj_modelId
		 */
	std::size_t gameObj_getModelID();

		/*!
		 * @brief Returns the model for this GameObject.
		 * @return The ID of the tracked model.
		 * @see gameObj_modelPath
		 */
	std::string gameObj_getModelPath();

		/*!
		 * @brief Stores the current position of the GameObject in a 3D space.
		 * @note Default value of { 0.0f, 0.0f, 0.0f }.
		 */
	glm::vec3 gameObj_pos;

		/*!
		 * @brief The GameObject's rotation, in degrees, along the Y axis.
		 * @note Default 0.0f.
		 */
	float gameObj_yaw;

		/*!
		 * @brief The GameObject's rotation, in degrees, along the X axis.
		 * @note Default 0.0f.
		 */
	float gameObj_pitch;

		/*!
		 * @brief The GameObject's rotation, in degrees, along the Z axis.
		 * @note Default 0.0f.
		 */
	float gameObj_roll;

		/*!
		 * @brief Stores the identifier for the GameObject's physics body.
		 * @note Default value of 0ul.
		 */
	long unsigned int gameObj_physBody;

private:
		/*!
		 * @brief Stores the identifier of the model for the GameObject.
		 * @note Defaults to the lowest possible value for the ID type.
		 */
	std::size_t gameObj_modelId;

		/*!
		 * @brief Stores the external path to the model on the disk for the GameObject.
		 * @note Defaults to "".
		 */
	std::string gameObj_modelPath;

		/*!
		 * @brief Stores the unique Identifier for the GameObject.
		 * @note Defaults to BlueEngine::IDTracker.getID().
		 */
	BlueEngine::ID gameObj_uniqueId;
};
