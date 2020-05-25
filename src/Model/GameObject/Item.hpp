#include <memory>

/// Internal Dependencies
#include "Base.hpp"

	/*!
	 * @brief A non-static and non-playable GameObject.
	 * @note Used for interactable objects within scenes.
	 */
class GameObj_Item : public GameObj_Base {
public:
		/*!
		 * @brief Sets initial class contents and calls the inherited class constructor.
		 * @param [in] model_in The identifier for a model loaded into the engine.
		 * @param [in] physbody_in The identifier for a physics body loaded into the engine.
		 */
	GameObj_Item(BlueEngine::ID model_in, BlueEngine::ID physBody_in);

		/*!
		* @brief GameObj_Static destructor.
		* @note Currently stubbed out, does not extend destructor behaviour for this GameObject.
		*/
	~GameObj_Item();

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return Always returns GameObj_Type::Item for GameObj_Item.
		 */
	BlueEngine::ID type() const;

		/*!
		 * @brief The draw call for a GameObj_Item.
		 * @param [in] projection The rendering projection for rendering.
		 * @param [in] view The rendering view for rendering.
		 * @param [in] cameraPos The position of the camera for rendering.
		 */
	void draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos);
};
