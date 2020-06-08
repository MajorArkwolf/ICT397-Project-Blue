#pragma once

	/// System Dependencies
#include <memory>

	/// External Dependencies
#include "glm/glm.hpp"

	/// Internal Dependencies
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
		 * @note A value of 0 indicates the GameObject has no model.
		 */
	size_t model;

    virtual void update(double t, double dt);

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

private:
		/*!
		 * @brief Stores the GameObject's unique identifier.
		 * @note Defaults to BlueEngine::IDTracker.getID().
		 */
	BlueEngine::ID uniqueID;
};
