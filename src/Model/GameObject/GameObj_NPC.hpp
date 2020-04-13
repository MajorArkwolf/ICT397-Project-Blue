#pragma once

	/// Internal Dependencies
#include "GameObject_Base.hpp"

	/*!
	 * @brief A non-moving Gameobject.
	 * @note Used for populating a scene with furnishings.
	 */
class GameObj_NPC : public GameObject_Base {
public:
		/*!
		 * @brief Initialses class contents and calls the inherited class constructor.
		 * @see GameObject_Base
		 */
	GameObj_NPC();

		/*!
		 * @brief Sets initial class contents and calls the inherited class constructor.
		 * @param [in] path The path to a target external model file for this GameObject.
		 * @param [in] physBody The identifier for the physical body for this GameObject.
		 * @param [in] position The position of the GameObject in the 3D environment.
		 * @param [in] look_at The point the GameObject is looking at, relative to its position.
		 * @param [in] look_up The point where GameObject is looking up, relative to its position.
		 * @see GameObject_Base
		 */
	GameObj_NPC(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up);

		//! GameObj_NPC destructor
	~GameObj_NPC();

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return A unique identifying value for the GameObj_NPC class.
		 * @warning May return 0 if an error occured with registering the ID!
		 */
	GameObjectType gameObj_getType() const;

		//! Adds the GameObject to the draw queue.
	void gameObj_addToDraw();

private:
		/*!
		 * @brief Identifies the GameObject's type.
		 * @return A unique identifying value for the GameObj_NPC class.
		 * @warning May return 0 if an error occured with registering the ID!
		 */
	static GameObjectType gameObj_getTypeID();
};
