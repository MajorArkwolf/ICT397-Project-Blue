#pragma once

	/// Internal Dependencies
#include "GameObj_Base.hpp"

	//! The constant static definition for the identifier of GameObject type GameObj_Static.
constexpr GameObjType GAMEOBJ_STATIC = 1u;

	/*!
	 * @brief A non-moving Gameobject.
	 * @note Used for populating a scene with furnishings.
	 */
class GameObj_Static : public GameObj_Base {
public:
		/*!
		 * @brief Initialses class contents and calls the inherited class constructor.
		 * @see GameObj_Base
		 */
	GameObj_Static();

		/*!
		 * @brief Sets initial class contents and calls the inherited class constructor.
		 * @param [in] path The path to a target external model file for this GameObject.
		 * @param [in] physBody The identifier for the physical body for this GameObject.
		 * @param [in] position The position of the GameObject in the 3D environment.
		 * @param [in] look_at The point the GameObject is looking at, relative to its position.
		 * @param [in] look_up The point where GameObject is looking up, relative to its position.
		 * @see GameObj_Base
		 */
	GameObj_Static(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up);

		//! GameObj_Static destructor
	~GameObj_Static();

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return GAMEOBJ_STATIC, always.
		 */
	GameObjType gameObj_getTypeID() const;

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return GAMEOBJ_STATIC, always.
		 */
	static GameObjType _gameObj_getTypeID();

		//! Adds the GameObject to the draw queue.
	void gameObj_addToDraw();
};
