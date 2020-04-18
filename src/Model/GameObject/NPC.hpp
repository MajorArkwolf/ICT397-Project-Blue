#pragma once

	/// Internal Dependencies
#include "Base.hpp"

	/*!
	 * @brief A non-moving Gameobject.
	 * @note Used for populating a scene with furnishings.
	 */
class GameObj_NPC : public GameObj_Base {
public:
		/*!
		 * @brief Initialses class contents and calls the inherited class constructor.
		 * @see GameObj_Base
		 */
	GameObj_NPC();

		/*!
		 * @brief Sets initial class contents and calls the inherited class constructor.
		 * @param [in] path The path to a target external model file for this GameObject.
		 * @param [in] physBody The identifier for the physical body for this GameObject.
		 * @param [in] position The position of the GameObject in the 3D environment.
		 * @param [in] rotateHori The GameObject's rotation, in degrees, along the Y axis.
		 * @param [in] rotateVert The GameObject's rotation, in degrees, along the X axis.
		 * @param [in] rotateTilt The GameObject's rotation, in degrees, along the Z axis.
		 * @see GameObj_Base
		 */
	GameObj_NPC(std::string path, unsigned long int physBody, glm::vec3 position, float rotateHori, float rotateVert, float rotateTilt);

		//! GameObj_NPC destructor
	~GameObj_NPC();

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return GAMEOBJ_NPC, always.
		 */
	GameObjType gameObj_getTypeID() const;

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return GAMEOBJ_NPC, always.
		 */
	static GameObjType _gameObj_getTypeID();

		//! Adds the GameObject to the draw queue.
	void gameObj_addToDraw();
};
