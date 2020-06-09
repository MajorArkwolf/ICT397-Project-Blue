#pragma once

	/// Internal Dependencies
#include "Character.hpp"

	/*!
	 * @brief A GameObject containing player-specific features.
	 * @note Used for extendible and efficient characters that the players can control.
	 */
class GameObj_Player : virtual public GameObj_Character {
public:
		/*!
		 * @brief Sets initial class contents and calls the inherited class constructor.
		 * @param [in] model_in The identifier for a model loaded into the engine.
		 * @param [in] physBody_in The identifier for a physics body loaded into the engine.
		 */
	GameObj_Player(BlueEngine::ID model_in, BlueEngine::ID physBody_in);

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return Always returns GameObj_Type::Player for GameObj_Player.
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
};
