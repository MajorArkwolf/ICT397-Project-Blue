#pragma once

	/// System Dependencies
#include <memory>

	/// Internal Dependencies
#include "Base.hpp"

	/*!
	 * @brief A non-moving Gameobject.
	 * @note Used for populating a scene with non-interactive furnishings.
	 */
class GameObj_Static : public GameObj_Base {
public:
		/*!
		 * @brief Sets initial class contents and calls the inherited class constructor.
		 * @param [in] model_in The identifier for a model loaded into the engine.
		 * @param [in] physbody_in The identifier for a physics body loaded into the engine.
		 */
	GameObj_Static(BlueEngine::ID model_in, BlueEngine::ID physBody_in);

		/*!
		 * @brief GameObj_Static destructor.
		 * @note Currently stubbed out, does not extend destructor behaviour for this GameObject.
		 */
	~GameObj_Static();

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return Always returns GameObj_Type::Static for GameObj_Static.
		 */
	GameObj_Type type() const;

		//! Adds the GameObject to the draw queue.
	void addToDraw();

		/*!
		 * @brief The draw call for a GameObj_Static.
		 * @param [in] projection The rendering projection for rendering.
		 * @param [in] view The rendering view for rendering.
		 * @param [in] cameraPos The position of the camera for rendering.
		 */
	void draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos);
};
