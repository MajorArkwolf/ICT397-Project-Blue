#pragma once

	/// System Dependencies
#include <map>

	/// Internal Dependencies
#include "GameObject_Base.hpp"

	/*!
	 * @brief A GameObject containing player-specific features.
	 * @note Used for extendible and efficient characters that the players can control.
	 */
class GameObj_Player : public GameObject_Base {
public:
		/*!
		 * @brief Initialses class contents and calls the inherited class constructor.
		 * @see GameObject_Base
		 */
	GameObj_Player();

		/*!
		 * @brief Sets initial class contents and calls the inherited class constructor.
		 * @param [in] path The path to a target external model file for this GameObject.
		 * @param [in] physBody The identifier for the physical body for this GameObject.
		 * @param [in] position The position of the GameObject in the 3D environment.
		 * @param [in] look_at The point the GameObject is looking at, relative to its position.
		 * @param [in] look_up The point where GameObject is looking up, relative to its position.
		 * @see GameObject_Base
		 */
	GameObj_Player(std::string path, unsigned long int physBody, glm::vec3 position, glm::vec3 look_at, glm::vec3 look_up);

		//! GameObj_Player destructor
	~GameObj_Player();

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return A unique identifying value for the GameObj_Player class.
		 * @warning May return 0 if an error occured with registering the ID!
		 */
	GameObjectType gameObj_getTypeID() const;

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return A unique identifying value for the GameObj_Player class.
		 * @warning May return 0 if an error occured with registering the ID!
		 */
	static GameObjectType _gameObj_getTypeID();

		//! Adds the GameObject to the draw queue.
	void gameObj_addToDraw();

		/*!
		 * @brief Assigns a status (with a value) to the player.
		 * @param [in] key The string to identify the status by.
		 * @param [in] value The value to assign to the status.
		 * @note If the status key does not exist, it will be created.
		 * @note If the status key does exist, its assigned value will be overwritten.
		 */
	void status_assign(std::string key, float value);

		/*!
		 * @brief Checks if the player has a specific status.
		 * @param [in] key The string to identify the status by.
		 * @return True if the player has the specified status, False otherwise.
		 */
	bool status_has(std::string key);

		/*!
		 * @brief Returns a copy of the value assigned to the player's status.
		 * @param [in] key The string to identify the status by.
		 * @return A copy of the status' value, or 0.0f if the status was not found.
		 * @note Function status_has() should be called prior to confirm the status exists.
		 * @warning The return value alone cannot be used to determine if an error had occured!
		 * @see GameObj_Player::status_has()
		 */
	float status_get(std::string key);

		/*!
		 * @brief Deletes a specific status (and it's assigned value) for the player.
		 * @param [in] key The string to identify the status by.
		 * @note If the targeted status does not exist, no changes will occur.
		 */
	void status_delete(std::string key);

		//! Deletes all of the player's statuses.
	void status_deleteAll();

protected:
		/*!
		 * @brief Stores player status values to unique string keys.
		 * @note All player status values are stored as floats.
		 */
	std::map<std::string, float> player_statuses;
};
