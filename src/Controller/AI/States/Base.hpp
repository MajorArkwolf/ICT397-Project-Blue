#pragma once

	/// Internal Dependencies
#include "Controller/Engine/IDTracker.hpp"
#include "Controller/AI/Message.hpp"
#include "Controller/AI/FSM.hpp"

	/// Forward Declaration
class FSM {};

	/*!
	 * @brief A virtual polymorphic interface class to be used by all FSM State systems.
	 * @warning This is fully virtual, and thus all specified operations must be implemented by child classes.
	 */
class State_Base {
public:
		/*!
		 * @brief The behaviour to perform when this State is made active/current.
		 * @param [in] context The contextual information to apply to the State's behaviour.
		 * @warning Fully virtual, must be implemented by inheritors!
		 */
	virtual void start(FSM* context) = 0;

		/*!
		 * @brief The behaviour to perform while the State is active/current.
		 * @param [in] context The contextual information to apply to the State's behaviour.
		 * @param [in] t The amount of time from the engine program starting.
		 * @param [in] dt The amount of delta time from the prior operation of this behaviour.
		 * @warning Fully virtual, must be implemented by inheritors!
		 */
	virtual void run(FSM* context, double t, double dt) = 0;

		/*!
		 * @brief The behaviour to perform when this State is made no longer active/current.
		 * @param [in] context The contextual information to apply to the State's behaviour.
		 * @warning Fully virtual, must be implemented by inheritors!
		 */
	virtual void end(FSM* context) = 0;

		/*!
		 * @brief The behaviour to perform when recieving a message.
		 * @param [in] context The contextual information to apply to the State's behaviour.
		 * @param [in] msg_sender The identifier of the FSM that generated this message.
		 * @param [in] msg_type The type identifier of this message.
		 * @param [in] msg_attachment The secondary message data, used to suppliment the message type.
		 * @warning Fully virtual, must be implemented by inheritors!
		 */
	virtual void read(FSM* context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) = 0;
};
