#pragma once

	/// System Dependencies
#include <map>
#include <memory>

	/// Internal Dependencies
#include "Base.hpp"

	//! A manager class for GameObject's creation and storage.
class GameObj_Manager {
public:
		//! Default constructor, initialises manager.
	GameObj_Manager();

		/*!
		 * @brief Default destructor, calls for GameObjects to be removed from manager.
		 * @see GameObj_Manager::clear()
		 */
	~GameObj_Manager();

		/*!
		 * @brief Adds a new GameObject to be managed.
		 * @param [in] object A smart pointer to the target GameObject.
		 * @warning Assigning a new GameObject with an existing identifier will overwrite the old GameObject!
		 */
	void insert(std::shared_ptr<GameObj_Base> object);

		/*!
		 * @brief Gather a reference to a managed GameObject.
		 * @param [in] identifier A GameObject identifier.
		 * @return A pointer to the specified GameObject, or nullptr on error.
		 * @note Can be used to check if a GameObject is being managed.
		 */
	std::shared_ptr<GameObj_Base> get(BlueEngine::ID identifier);

		/*!
		 * @brief Calls for a specific GameObject to be removed from the manager.
		 * @param [in] identifier A GameObject identifier.
		 * @note No effect will occur if the requested GameObject is not managed.
		 * @warning The requested GameObject may remain in memory after this call due to smart pointers!
		 */
	void remove(BlueEngine::ID identifier);

		/*!
		 * @brief Calls for all GameObjects to be removed from the manager.
		 * @see GameObj_Manager::remove()
		 */
	void clear();

private:
		//! Stores a collection of unique GameObjects, mapped to their identifier.
	std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>> managedGameObjects;
};
