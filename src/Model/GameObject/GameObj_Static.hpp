#pragma once

	/// Internal Dependencies
#include "GameObject_Base.hpp"

	/*!
	 * @brief A non-moving Gameobject.
	 * @note Used for populating a scene with furnishings.
	 */
class GameObj_Static : virtual public GameObject_Base {
	public:
			/*!
			 * @brief Initialses class contents and calls the inherited class constructor.
			 * @see GameObject_Base
			 */
		GameObj_Static();

			/*!
			 * @brief Sets initial class contents and calls the inherited class constructor.
			 * @param [in] path The path to a target external model file for this GameObject.
			 * @param [in] position The position of the GameObject in the 3D environment.
			 * @param [in] look_at The point the GameObject is looking at, relative to its position.
			 * @param [in] look_up The point where GameObject is looking up, relative to its position.
			 * @see GameObject_Base
			 */
		GameObj_Static(std::string path, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up)
			: GameObject_Base(path, position, look_at, look_up);

			//! GameObj_Static destructor
		~GameObj_Static();

			/*!
			 * @brief Identifies the GameObject's type.
			 * @return A unique identifying value for the GameObj_Static class.
			 */
		static GameObjectType gameObj_getType() const;
};
