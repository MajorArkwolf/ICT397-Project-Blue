#pragma once

	/// System Dependencies
#include <map>
#include <memory>

	/// System Dependencies
#include <functional>

	/// Internal Dependencies
#include "detail/LuaAssist.hpp"

	/*!
	 * @brief Type declaration for a function pointer used by the GameObj_Manager.
	 * @param [in] GameObj_In A smart pointer to a GameObject.
	 * @return Never returns anything.
	 */
using GameObj_ProcessFunc = std::function<void(std::shared_ptr<GameObj_Base> GameObj_In)> ;

	//! A manager class for GameObject's creation and storage.
class GameObj_Manager {
public:
		//! The GameObj_Manager class constructor use is not allowed.
	GameObj_Manager() = delete;

		/*!
		 * @brief Registers the GameObject system with the engine's scripting system.
		 * @note Only performs the initialisation once, even if called multiple times.
		 */
	static void init();

		/*!
		 * @brief Adds a new GameObject to be managed.
		 * @param [in] object A smart pointer to the target GameObject.
		 * @warning Assigning a new GameObject with an existing identifier will overwrite the old GameObject!
		 */
	static void insert(std::shared_ptr<GameObj_Base> object);

		/*!
		 * @brief Gathers a reference to a managed GameObject.
		 * @param [in] identifier A GameObject identifier.
		 * @return A pointer to the specified GameObject, or nullptr on error.
		 * @note Can be used to check if a GameObject is being managed.
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
		 */
	static void syncPhys();

		/*!
		 * @brief Updates the current animation of the managed GameObjects, relative to the delta time passed.
		 * @param [in] t The amount of time that the engine has been running.
		 * @param [in] dt The delta amount of time since the engine loop called the subsystems' update functions.
		 */
	static void animation_update(double t, double dt);

protected:
		/*!
		 * @brief Invokes the use of the GameObject Factory and automates the process of storing its output.
		 * @param [in] type The Type of GameObject to create and store.
		 * @return The identifier of the newly created GameObject.
		 */
	static BlueEngine::ID lua_create(GameObj_Type type);

		/*!
		 * @brief Gathers a reference to a managed GameObject, in a format compatible with Lua.
		 * @param [in] identifier A GameObject identifier.
		 * @return A pointer to the specified GameObject, or nullptr on error.
		 * @note Can gather ANY type of managed GameObject.
		 * @warning The pointer provided is not managed, and the data may go out of scope!
		 */
	static GameObj_Base* lua_get(BlueEngine::ID identifier);
	
		/*!
		 * @brief Gathers a reference to a managed Player GameObject.
		 * @return A pointer to the specified GameObject, or nullptr on error.
		 * @note Will automatically store the Player GameObject into the manager if not used.
		 */
	static GameObj_Base* lua_getPlayer();

		/*!
		 * @brief Downcasts a GameObj_Base reference to a GameObj_Character reference.
		 * @param [in] raw_in A base pointer to a polymorphic GameObject.
		 * @return The reference typecasted, or nullptr if the cast could not be safely performed.
		 * @note To be used in Lua to access character specific operations.
		 */
	static GameObj_Character* lua_to_character(GameObj_Base* raw_in);

		/*!
		 * @brief Downcasts a GameObj_Character reference to a GameObj_NPC reference.
		 * @param [in] raw_in A base pointer to a polymorphic GameObject.
		 * @return The reference typecasted, or nullptr if the cast could not be safely performed.
		 * @note To be used in Lua to access npc specific operations.
		 */
	static GameObj_NPC* lua_to_npc(GameObj_Character* raw_in);

private:
		//! Stores a collection of unique GameObjects, mapped to their identifier.
	static std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>> managed_objs;
};
