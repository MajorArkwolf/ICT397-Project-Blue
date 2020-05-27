#pragma once

	/// System Dependencies
#include <map>
#include <memory>

	/// Internal Dependencies
#include "Base.hpp"
#include <functional>

	/*!
	 * @brief Type declaration for a function pointer used by the GameObj_Manager.
	 * @param [in] GameObj_In A smart pointer to a GameObject.
	 * @return Never returns anything.
	 */
using GameObj_ProcessFunc = std::function<void(std::shared_ptr<GameObj_Base> GameObj_In)> ;

	//! A manager class for GameObject's creation and storage.
class GameObj_Manager {
public:
		/*!
		 * @brief Registers the GameObject Manager and LuaHelper classes into the engine's Lua VM.
		 * @note Only performs the initialisation once, even if called multiple times.
		 */
	//static void init();

		/*!
		 * @brief Adds a new GameObject to be managed.
		 * @param [in] object A smart pointer to the target GameObject.
		 * @note This is not registered with Lua.
		 * @warning Assigning a new GameObject with an existing identifier will overwrite the old GameObject!
		 */
	static void insert(std::shared_ptr<GameObj_Base> object);

		/*!
		 * @brief Gather a reference to a managed GameObject.
		 * @param [in] identifier A GameObject identifier.
		 * @return A pointer to the specified GameObject, or nullptr on error.
		 * @note Can be used to check if a GameObject is being managed.
		 * @note This is not registered with Lua.
		 */
	static std::shared_ptr<GameObj_Base> get(BlueEngine::ID identifier);

		/*!
		 * @brief Calls for a specific GameObject to be removed from the manager.
		 * @param [in] identifier A GameObject identifier.
		 * @note No effect will occur if the requested GameObject is not managed.
		 * @warning The requested GameObject may remain in memory after this call due to smart pointers!
		 */
	static void remove(BlueEngine::ID identifier);

		/*!
		 * @brief Calls for all GameObjects to be removed from the manager.
		 * @see GameObj_Manager::remove()
		 */
	static void clear();

		/*!
		 * @brief Passes a smart pointer to a provided function for each managed GameObject.
		 * @param [in] function A function to process all of the stored GameObjects in the Manager.
		 * @see GameObj_ProcessFunc
		 */
	static void process_all(GameObj_ProcessFunc function);

		/*!
		 * @brief Calls the addToDraw function on all managed GameObjects.
		 * @note No calls will occur if the Manager isn't managing any GameObjects.
		 */
	static void addAllToDraw();

		/*!
		 * @brief Updates the managed GameObjects' collisions bodies to match their rigid bidies.
		 * @warning Must be called after the physics system delta-updates its rigid bodies!
		 * @note Should be replaced by the physics system, this is a hacky solution.
		 */
	static void updatePhys();

private:
		//! Stores a collection of unique generic GameObjects, mapped to their identifier.
	static std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>> generic_objs;

		//! Stores a collection of unique character GameObjects, mapped to their identifier.
	static std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>> character_objs;
};
