#pragma once

/// Internal Dependencies
#include "Base.hpp"

	//! A state where the FSM actor will assist other NPCs that have collapsed from taking too much damage.
class State_Revive : virtual public State_Base {
public:
	/*!
	 * @brief The behaviour to perform when this State is made active/current.
	 * @param [in] context The contextual GameObject reference to pass to the State's behaviour.
	 */
	void start(std::shared_ptr<GameObj_Base> context);

	/*!
	 * @brief The behaviour to perform while the State is active/current.
	 * @param [in] context The contextual GameObject reference to pass to the State's behaviour.
	 * @param [in] t The amount of time from the engine program starting.
	 * @param [in] dt The amount of delta time from the prior operation of this behaviour.
	 */
	void run(std::shared_ptr<GameObj_Base> context, double t, double dt);

	/*!
	 * @brief The behaviour to perform when this State is made no longer active/current.
	 * @param [in] context The contextual GameObject reference to pass to the State's behaviour.
	 * @warning Fully virtual, must be implemented by inheritors!
	 */
	void end(std::shared_ptr<GameObj_Base> context);

	/*!
	 * @brief The behaviour to perform when recieving a message.
	 * @param [in] context The contextual GameObject reference to pass to the State's behaviour.
	 * @param [in] msg_sender The identifier of the FSM that generated this message.
	 * @param [in] msg_type The type identifier of this message.
	 * @param [in] msg_attachment The secondary message data, used to suppliment the message type.
	 */
	void read(std::shared_ptr<GameObj_Base> context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment);
};
