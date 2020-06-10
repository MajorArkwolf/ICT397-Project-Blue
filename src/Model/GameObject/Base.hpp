#pragma once

	/// System Dependencies
#include <memory>

	/// System Dependencies
#include "glm/glm.hpp"

	/// Internal Dependencies
#include "Controller/Animator.hpp"
#include "Controller/Engine/IDTracker.hpp"
#include "View/Renderer/Shader.hpp"
#include "Types.hpp"

	/*!
	 * @brief The parent class for all child GameObjects.
	 * @note Acts as the base polymorphic structure for use with all derived GameObjects.
	 */
class GameObj_Base {
public:
		/*!
		 * @brief Initialises class attributes to custom values.
		 * @param [in] model_in The identifier for a model loaded into the engine.
		 * @param [in] physBody_in The identifier for a physics body loaded into the engine.
		 */
	GameObj_Base(size_t model_in, BlueEngine::ID physBody_in);

		//! Virtual destructor
	virtual ~GameObj_Base() {}

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
	virtual GameObj_Type type() const = 0;

		/*!
		 * @brief Adds the GameObject to the draw queue.
		 * @warning Behaviour must be implemented by inheritors!
		 */
	virtual void addToDraw() = 0;

		/*!
		 * @brief Stores the identifier for the GameObject's physics body.
		 * @note A value of 0 indicates the GameObject has no physics body.
		 */
	BlueEngine::ID physBody;

		/*!
		 * @brief Stores the identifier for the GameObject's model.
		 */
	size_t model;

		/*!
		 * @brief Performs animation preperation pertaining to the GameObject's model.
		 * @return True if the GameObject's model had animation initialised and loaded, False otherwise.
		 * @note If the model has no animations, no change to the GameObject's animator will be made.
		 */
	bool animator_add();

		/*!
		 * @brief Updates the GameObject's current animation, relative to the delta time passed.
		 * @param [in] t The amount of time that the engine has been running.
		 * @param [in] dt The delta amount of time since the engine loop called the subsystems' update functions.
		 */
	void animator_update(double t, double dt);

		/*!
		 * @brief Changes the current animation of the GameObject.
		 * @param [in] animToLoad The name of the animation to load and apply to the GameObject.
		 * @param [in] stopOnEnd True to stop animation after it ends, False to loop the animation.
		 * @note Has no effect if the GameObject has not had its animation initialised.
		 */
	void animator_changeAnimation(const std::string& animToLoad, bool stopOnEnd);

		/*!
		 * @brief Checks if the GameObject has an initialised and configured animation.
		 * @return True if it does, False otherwise.
		 */
	bool animator_has();

		/*!
		 * @brief The GameObject's scale along all 3D axises.
		 * @note Defaults to { 0.0f, 0.0f, 0.0f }.
		 */
	glm::vec3 scale;

		/*!
		 * @brief Registers this GameObject class to the Lua subscripting system.
		 * @note Called in the constructor, constructor is responsible for only calling once.
		 */
	static void lua_init_register();

protected:
		/*!
		 * @brief Manages the shader program to be used for all GameObject rendering.
		 * @note Shared across all types and instances of Game Objects.
		 */
	std::shared_ptr<Shader> program;

		/*!
		 * @brief Stores the GameObject's individual animation properties.
		 * @note Internal to the GameObject itself, and must be updated relative to delta time passed.
		 */
	std::shared_ptr<Controller::Animator> animator;

private:
		/*!
		 * @brief Stores the GameObject's unique identifier.
		 * @note Defaults to BlueEngine::IDTracker.getID().
		 */
	BlueEngine::ID uniqueID;
};
