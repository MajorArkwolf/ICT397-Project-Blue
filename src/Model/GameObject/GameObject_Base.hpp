#pragma once

	/// System Dependencies
#include <string>

	/// External Dependencies
#include <glm/glm.hpp>

	/*!
	 * @brief Declaration of the type for identifying different GameObject classes.
	 * @warning 0 is reserved for invalid identifiers and error reporting.
	 */
using GameObjectType = unsigned int;

	//! The parent class for all child GameObjects.
class GameObject_Base
{
public:
		//! Initialises class attributes to their defaults.
	GameObject_Base();

		/*!
		 * @brief Initialises class attributes to custom values.
		 * @param [in] path The path to a target external model file for this GameObject.
		 * @param [in] position The position of the GameObject in the 3D environment.
		 * @param [in] look_at The point the GameObject is looking at, relative to its position.
		 * @param [in] look_up The point where GameObject is looking up, relative to its position.
		 */
	GameObject_Base(std::string path, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up);

		//! Virtual destructor.
	virtual ~GameObject_Base() = 0;

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return Always returns 0 for GameObject_Base.
		 * @warning Must be implemented by inheritors!
		 */
	virtual GameObjectType gameObj_getType() const = 0;

		/*!
		 * @brief Tracks and calls for the loading of an external model file.
		 * @param [in] path The path to a target external model file for this GameObject.
		 * @see gameObj_modelId
		 */
	void gameObj_setModel(std::string path);

		/*!
		 * @brief Returns the model for this GameObject.
		 * @return The ID of the tracked model.
		 * @see gameObj_modelId
		 */
	std::size_t gameObj_getModel();

		/*!
		 * @brief Stores the current position of the GameObject in a 3D space.
		 * @note Default value of { 0.0f, 0.0f, 0.0f }.
		 */
	glm::vec3 gameObj_pos;

		/*!
		 * @brief The point the GameObject is currently looking at, relative to its position.
		 * @note Default value of { 0.0f, 0.0f, 1.0f }.
		 */
	glm::vec3 gameObj_lookAt;

		/*!
		 * @brief Stores the direction that points up relative from the GameObject in a 3D space.
		 * @note Default value of { 0.0f, 1.0f, 0.0f }.
		 */
	glm::vec3 gameObj_lookUp;

protected:
		/*!
		 * @brief Registers an identifying value for the GameObject's class.
		 * @return A unique value of GameObjectType, or the lowest possible value of GameObjectType on error.
		 * @warning Should only be called by an inheritor's gameObj_getType()!
		 */
	static GameObjectType gameObj_registerTypeID();

private:
		/*!
		 * @brief Stores the ID of the model for the GameObject.
		 * @note Defaults to the lowest possible value for the ID type.
		 */
	std::size_t gameObj_modelId;
};
