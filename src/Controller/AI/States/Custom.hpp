#pragma once

	/// System Dependencies
#include <string>

	/// Internal Dependencies
#include "Base.hpp"

	/*!
	 * @brief A customizable FSm state that has its behaviour defined in Lua scripting.
	 * @note Operates on the contextual GameObject's "_TargetGameObject" status.
	 */
class State_Custom : public State_Base {
public:
		//! Use of the default constructor is disallowed.
	State_Custom() = delete;

		/*!
		 * @brief Configuration constructor.
		 * @param [in] start_func
		 * @param [in] run_func
		 * @param [in] end_func
		 * @param [in] read_func
		 * @warning 
		 */
	State_Custom(TODO: USE LUABRIDGE TO CALL LUA FUNCTIONS IN THIS CLASS);

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
