#pragma once

	/// Internal Dependencies
#include "Character.hpp"

	/*!
	 * @brief A non-moving Gameobject.
	 * @note Used for populating a scene with furnishings.
	 */
class GameObj_NPC : virtual public GameObj_Character {
public:
		/*!
		 * @brief Sets initial class contents and calls the inherited class constructor.
		 * @param [in] model_in The identifier for a model loaded into the engine.
		 * @param [in] physBody_in The identifier for a physics body loaded into the engine.
		 * @param [in] context_in The identifier for a finite state machine loaded into the engine.
		 */
	GameObj_NPC(size_t model_in, BlueEngine::ID physBody_in, BlueEngine::ID context_in);

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return Always returns GameObj_Type::NPC for GameObj_NPC.
		 */
	GameObj_Type type() const;

		//! Adds the GameObject to the draw queue.
	void addToDraw();

		/*!
		 * @brief The draw call for a GameObj_Player.
		 * @param [in] projection The rendering projection for rendering.
		 * @param [in] view The rendering view for rendering.
		 * @param [in] cameraPos The position of the camera for rendering.
		 */
	void draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos);

		/*!
		 * @brief Returns a read-only copy of the NPC's AI context.
		 * @return The identifier for the NPC's FSM.
		 */
	BlueEngine::ID context();

		/*!
		 * @brief Registers this GameObject class to the Lua subscripting system.
		 * @note Called in the constructor, constructor is responsible for only calling once.
		 */
	static void lua_init_register();

private:
		/*!
		 * @brief Stores the NPC's finite state machine identifier.
		 * @note Value assigned at NPC construction.
		 */
	BlueEngine::ID contextID;
};
