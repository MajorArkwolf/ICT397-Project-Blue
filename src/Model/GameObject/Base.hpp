#pragma once

	/// External Dependencies
#include "glm/glm.hpp"

	/// Internal Dependencies
#include "Controller/Engine/IDTracker.hpp"
#include "View/Renderer/Shader.hpp"

	/*!
	 * @brief The parent class for all child GameObjects.
	 * @note Acts as the base polymorphic structure for use with all derived GameObjects.
	 */
class GameObj_Base {
public:
		/*!
		 * @brief Initialises class attributes to custom values.
		 * @param [in] model_in The identifier for a model loaded into the engine.
		 * @param [in] physbody_in The identifier for a physics body loaded into the engine.
		 */
	GameObj_Base(BlueEngine::ID model_in, BlueEngine::ID physBody_in);

		/*!
		 * @brief Virtual destructor.
		 * @warning Must be implemented by inheritors!
		 */
	virtual ~GameObj_Base() = 0;

		/*!
		 * @brief Returns a copy of this GameObject's unique identifier.
		 * @return A copy of GameObj_Base::uniqueID.
		 */
	BlueEngine::ID id();

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return Always returns GameObj_Type::Invalid for GameObj_Base.
		 * @warning Must be implemented by inheritors!
		 */
	virtual BlueEngine::ID type() const = 0;

		/*!
		 * @brief Renders the GameObject within the engine.
		 * @param [in] projection The rendering projection for rendering.
		 * @param [in] view The rendering view for rendering.
		 * @param [in] cameraPos The position of the camera for rendering.
		 * @warning Must be implemented by inheritors!
		 */
	virtual void draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) = 0;

		/*!
		 * @brief Stores the identifier for the GameObject's physics body.
		 * @note A value of 0 indicates the GameObject has no physics body.
		 */
	BlueEngine::ID physBody;

		/*!
		 * @brief Stores the identifier for the GameObject's model.
		 * @note A value of 0 indicates the GameObject has no model.
		 */
	BlueEngine::ID model;

protected:
		/*!
		 * @brief Manages the shader program to be used for all GameObject rendering.
		 * @note This is shared across all child GameObjects.
		 */
	static Shader program;

private:
		/*!
		 * @brief Stores the GameObject's unique identifier.
		 * @note Defaults to BlueEngine::IDTracker.getID().
		 */
	BlueEngine::ID uniqueID;
};
