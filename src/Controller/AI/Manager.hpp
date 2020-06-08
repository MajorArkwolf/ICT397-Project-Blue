#pragma once

	/// System Dependencies
#include <map>
#include <forward_list>
#include <memory>

	/// Internal Dependencies
#include "Controller/Engine/IDTracker.hpp"
#include "Model/GameObject/Base.hpp"
#include "FSM.hpp"
#include "Message.hpp"

	/*!
	 * @brief A centralised system for the use and management of Finite State Machines for AI Game Actors.
	 * @note To avoid performance costs, only have a single globally-accessible instance of this system!
	 */
class FSM_Manager {
public:
		/*!
		 * @brief Creates a new FSM to be managed, attached to a specified Game Object.
		 * @param [in] A managed reference to the target attachment Game Object.
		 * @return The newly created FSM's identifier, or 0u on error.
		 * @note This will intentionally not create an FSM if the attached GameObject is nullptr or not an NPC.
		 */
	static BlueEngine::ID create(std::shared_ptr<GameObj_Base> object);

		/*!
		 * @brief The getter function for accessing the managed FSMs.
		 * @param [in] identifier A FSM identifier.
		 * @return A managed reference to the requested FSM, or nullptr on error.
		 */
	static std::shared_ptr<FSM> get(BlueEngine::ID identifier);

		/*!
		 * @brief Removes a specified FSM from this Manager's internal storage.
		 * @param [in] identifier A FSM identifier.
		 * @note Due to the encapsulation in managed references, it may remain in memory after this call.
		 */
	static void erase(BlueEngine::ID identifier);

		/*!
		 * @brief Removes all managed FSMs from this Manager's internal storage.
		 * @note Due to the encapsulation in managed references, they may remain in memory after this call.
		 */
	static void clear();

		/*!
		 * @brief Processes all pending messages and THEN operates the managed FSMs' behaviours.
		 * @param [in] t The amount of time from the engine program starting.
		 * @param [in] dt The amount of delta time from the prior operation of this behaviour.
		 * @note All messages will have their delay property decreased by 1 unless delivered.
		 */
	static void update(double t, double dt);

		/*!
		 * @brief Adds a new Inter-FSM Message to a queue for processing.
		 * @param [in] message The data structure to be processed by a specific set of FSMs.
		 * @note Any invalid recipients assigned to a message will be skipped.
		 */
	static void send(Message message);

		/*!
		 * @brief Returns a reference to a static instance of a requested type of FSM State.
		 * @param [in] type The specification of the state type to gather.
		 * @return A reference to a static regular FSM State.
		 */
	static std::shared_ptr<State_Base> regular_state(State_Type type);

		/*!
		 * @brief Attempts to generate a new Lua scripted FSM State.
		 * @param [in] start_func The name of the Lua function to call for the starting behaviour.
		 * @param [in] run_func The name of the Lua function to call for the running behaviour.
		 * @param [in] end_func The name of the Lua function to call for the ending behaviour.
		 * @param [in] read_func The name of the Lua function to call for the reading behaviour.
		 * @return A managed reference to a newly created custom FSM State, or nullptr on error.
		 */
	static std::shared_ptr<State_Base> custom_state(std::string start_func, std::string run_func, std::string end_func, std::string read_func);

		/*!
		 * @brief Registers the FSM management systems and misc. properties to the Lua scripting system.
		 * @note Only operates on its first call, and should be called at engine startup.
		 */
	static void lua_init();

protected:
		/*!
		 * @brief Stores a collection of managed FSMs, mapped to their unique identifiers.
		 * @note The FSM is solely responsible for maintaining their ID, this mapping is for access performance.
		 */
	static std::map<BlueEngine::ID, std::shared_ptr<FSM>> actors;

private:
		/*!
		 * @brief Creates a new FSM to be managed, attached to a specified Game Object.
		 * @param [in] A managed reference to the target attachment Game Object.
		 * @return The newly created FSM's identifier, or 0u on error.
		 * @note This will intentionally not create an FSM if the attached GameObject is nullptr or not an NPC.
		 */
	static BlueEngine::ID lua_create(GameObj_Base* object);

		/*!
		 * @brief The getter function for accessing the managed FSMs.
		 * @param [in] identifier A FSM identifier.
		 * @return A managed reference to the requested FSM, or nullptr on error.
		 */
	static FSM* lua_get(BlueEngine::ID identifier);

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return State_Type::Chase
		 */
	static State_Type lua_enum_chase();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return State_Type::Evade
		 */
	static State_Type lua_enum_evade();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return State_Type::Flee
		 */
	static State_Type lua_enum_flee();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return State_Type::Patrol
		 */
	static State_Type lua_enum_patrol();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return State_Type::Pursuit
		 */
	static State_Type lua_enum_pursuit();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return State_Type::Wander
		 */
	static State_Type lua_enum_wander();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return Message_Type::Invalid
		 */
	static Message_Type lua_enum_msg_invalid();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return Message_Type::TargetSet
		 */
	static Message_Type lua_enum_msg_targetSet();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return Message_Type::TargetFound
		 */
	static Message_Type lua_enum_msg_targetFound();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return Message_Type::TargetLost
		 */
	static Message_Type lua_enum_msg_targetLost();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return Message_Type::TargetDanger
		 */
	static Message_Type lua_enum_msg_targetDanger();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return Message_Type::TargetVunerable
		 */
	static Message_Type lua_enum_msg_targetVunerable();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return Message_Type::PositionX
		 */
	static Message_Type lua_enum_msg_posX();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return Message_Type::PositionY
		 */
	static Message_Type lua_enum_msg_posY();

		/*!
		 * @brief Provides scripted access to enumerated values.
		 * @return Message_Type::PositionZ
		 */
	static Message_Type lua_enum_msg_posZ();

		/*!
		 * @brief Stores the currently pending messages to be delivered.
		 * @note Should not be pollable, only internally iterated through.
		 */
	static std::forward_list<Message> pending_messages;
};
