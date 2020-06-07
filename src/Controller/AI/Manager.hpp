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
	BlueEngine::ID create(std::shared_ptr<GameObj_Base> object);

		/*!
		 * @brief The getter function for accessing the managed FSMs.
		 * @param [in] identifier A FSM identifier.
		 * @return A managed reference to the requested FSM, or nullptr on error.
		 */
	std::shared_ptr<FSM> get(BlueEngine::ID identifier);

		/*!
		 * @brief Removes a specified FSM from this Manager's internal storage.
		 * @param [in] identifier A FSM identifier.
		 * @note Due to the encapsulation in managed references, it may remain in memory after this call.
		 */
	void erase(BlueEngine::ID identifier);

		/*!
		 * @brief Removes all managed FSMs from this Manager's internal storage.
		 * @note Due to the encapsulation in managed references, they may remain in memory after this call.
		 */
	void clear();

		/*!
		 * @brief Processes all pending messages and THEN operates the managed FSMs' behaviours.
		 * @param [in] t The amount of time from the engine program starting.
		 * @param [in] dt The amount of delta time from the prior operation of this behaviour.
		 * @note All messages will have their delay property decreased by 1 unless delivered.
		 */
	void update(double t, double dt);

		/*!
		 * @brief Adds a new Inter-FSM Message to a queue for processing.
		 * @param [in] message The data structure to be processed by a specific set of FSMs.
		 * @note Any invalid recipients assigned to a message will be skipped.
		 */
	void send(Message message);

protected:
		/*!
		 * @brief Stores a collection of managed FSMs, mapped to their unique identifiers.
		 * @note The FSM is solely responsible for maintaining their ID, this mapping is for access performance.
		 */
	std::map<BlueEngine::ID, std::shared_ptr<FSM>> actors;

private:
		/*!
		 * @brief Stores the currently pending messages to be delivered.
		 * @note Should not be pollable, only internally iterated through.
		 */
	std::forward_list<Message> pending_messages;
};
