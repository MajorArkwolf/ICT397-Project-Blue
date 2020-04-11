#pragma once

	/// Internal Dependencies
#include "GameObject_Base.hpp"

	/*!
	 * @brief A non-moving Gameobject.
	 * @note Used for populating a scene with furnishings.
	 */
class GameObj_NPC : virtual public GameObject_Base {
	public:
			/*!
			 * @brief Initialses class contents and calls the inherited class constructor.
			 * @see GameObject_Base
			 */
		GameObj_NPC();

			/*!
			 * @brief Sets initial class contents and calls the inherited class constructor.
			 * @param [in] path The path to a target external model file for this GameObject.
			 * @param [in] position The position of the GameObject in the 3D environment.
			 * @param [in] look_at The point the GameObject is looking at, relative to its position.
			 * @param [in] look_up The point where GameObject is looking up, relative to its position.
			 * @see GameObject_Base
			 */
		GameObj_NPC(std::string path, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up) : GameObject_Base(path);
};
