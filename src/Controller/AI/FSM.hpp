#pragma once

	/// System Dependencies
#include <memory>

	/// Internal Dependencies
#include "Controller/Engine/IDTracker.hpp"
#include "Controller/AI/States/Base.hpp"
#include "Controller/AI/Message.hpp"

	/// Forward Declaration
class FSM {};

	/*!
	 * @brief A finite state machine.
	 * @note Manages the contextual data required for state behaviour.
	 */
class FSM {
public:
		/*!
		 * @brief Finite State Machine constructor, 'attaches' a Game Object for additional context.
		 * @param [in] object The identifier of the target Game Object to 'attach'.
		 */
	FSM(BlueEngine::ID object);

		/*!
		 * @brief Sets the current local State, calling the appropiate start and end behaviour.
		 * @param [in] target A managed reference to an existing State loaded into the engine.
		 * @note Sets the prior local State to the value of the current local State at call before operating.
		 * @warning Will throw an error if the attached Game Object is invalid!
		 */
	void local_set(std::shared_ptr<State_Base> target);

		/*!
		 * @brief Swaps the current local and prior State, calling the appropiate start and end behaviour.
		 * @warning Will throw an error if the attached Game Object is invalid!
		 */
	void local_revert();

		/*!
		 * @brief Sets the current global State, calling the appropiate start and end behaviour.
		 * @param [in] target A managed reference to an existing State loaded into the engine.
		 * @note Sets the prior global State to the value of the current global State at call before operating.
		 * @warning Will throw an error if the attached Game Object is invalid!
		 */
	void global_set(std::shared_ptr<State_Base> target);

		/*!
		 * @brief Swaps the current global and prior State, calling the appropiate start and end behaviour.
		 * @warning Will throw an error if the attached Game Object is invalid!
		 */
	void global_revert();

		/*!
		 * @brief Calls the run behaviour for the current States.
		 * @param [in] t The amount of time from the engine program starting.
		 * @param [in] dt The amount of delta time from the prior operation of this behaviour.
		 * @note Operation calls are done in the order of local, global.
		 * @warning Will throw an error if the attached Game Object is invalid!
		 */
	void run(double t, double dt);

		/*!
		 * @brief Calls the read behaviour for the current States.
		 * @param [in] msg_sender The identifier of the FSM that generated this message.
		 * @param [in] msg_type The type identifier of this message.
		 * @param [in] msg_attachment The secondary message data, used to suppliment the message type.
		 * @warning Will throw an error if the attached Game Object is invalid!
		 */
	void read(BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment);

		/*!
		 * @brief Provides read-only access to the FSM's unique identifier.
		 * @return A copy of the value stored in unique_id.
		 */
	BlueEngine::ID id_this();

		/*!
		 * @brief Provides read-only access to the identifier of the 'attached' Game Object.
		 * @warning Will throw an error if the attached Game Object is invalid!
		 */
	BlueEngine::ID id_attached();

protected:
		/*!
		 * @brief The FSM's local active/current State.
		 * @note Stores a managed reference to the State, not an instance of the State itself.
		 * @warning If nullptr, no calls to its behaviour will be made.
		 */
	std::shared_ptr<State_Base> local_current;

		/*!
		 * @brief The FSM's local prior (inactive) State.
		 * @note Stores a managed reference to the State, not an instance of the State itself.
		 * @warning If nullptr, no calls to its behaviour will be made.
		 */
	std::shared_ptr<State_Base> local_prior;

		/*!
		 * @brief The FSM's global active/current State.
		 * @note Stores a managed reference to the State, not an instance of the State itself.
		 * @warning If nullptr, no calls to its behaviour will be made.
		 */
	std::shared_ptr<State_Base> global_current;

		/*!
		 * @brief The FSM's global prior (inactive) State.
		 * @note Stores a managed reference to the State, not an instance of the State itself.
		 * @warning If nullptr, no calls to its behaviour will be made.
		 */
	std::shared_ptr<State_Base> global_prior;

private:
		/*!
		 * @brief Stores the FSM's unique identifier.
		 * @note Initialised by constructor, should be treated as read-only after.
		 */
	BlueEngine::ID unique_id;

		/*!
		 * @brief Stores the unique identifier of the 'attached' GameObject.
		 * @note Initialised by constructor, should be treated as read-only after.
		 */
	BlueEngine::ID attached_id;
};
