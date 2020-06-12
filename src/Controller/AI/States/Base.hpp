#pragma once

	// System Dependencies
#include <memory>

	/// Internal Dependencies
#include "Controller/Engine/IDTracker.hpp"
#include "Controller/AI/Message.hpp"
#include "Model/GameObject/Base.hpp"
#include "Model/GameObject/NPC.hpp"

	/*!
	 * @brief A virtual polymorphic interface class to be used by all FSM State systems.
	 * @warning This is fully virtual, and thus all specified operations must be implemented by child classes.
	 */
class State_Base {
public:
		//! Virtual destructor
	virtual ~State_Base() {};

		/*!
		 * @brief The behaviour to perform when this State is made active/current.
		 * @param [in] context The contextual GameObject reference to pass to the State's behaviour.
		 * @warning Fully virtual, must be implemented by inheritors!
		 */
	virtual void start(std::shared_ptr<GameObj_Base> context) = 0;

		/*!
		 * @brief The behaviour to perform while the State is active/current.
		 * @param [in] context The contextual GameObject reference to pass to the State's behaviour.
		 * @param [in] t The amount of time from the engine program starting.
		 * @param [in] dt The amount of delta time from the prior operation of this behaviour.
		 * @warning Fully virtual, must be implemented by inheritors!
		 */
	virtual void run(std::shared_ptr<GameObj_Base> context, double t, double dt) = 0;

		/*!
		 * @brief The behaviour to perform when this State is made no longer active/current.
		 * @param [in] context The contextual GameObject reference to pass to the State's behaviour.
		 * @warning Fully virtual, must be implemented by inheritors!
		 */
	virtual void end(std::shared_ptr<GameObj_Base> context) = 0;

		/*!
		 * @brief The behaviour to perform when recieving a message.
		 * @param [in] context The contextual GameObject reference to pass to the State's behaviour.
		 * @param [in] msg_sender The identifier of the FSM that generated this message.
		 * @param [in] msg_type The type identifier of this message.
		 * @param [in] msg_attachment The secondary message data, used to suppliment the message type.
		 * @warning Fully virtual, must be implemented by inheritors!
		 */
	virtual void read(std::shared_ptr<GameObj_Base> context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) = 0;

		/*!
		 * @brief For use with hacky memory manegement.
		 * @note Only exists to deal with the issues pertaining to memory management.
		 */
	virtual bool isCustom() { return false; }
};
