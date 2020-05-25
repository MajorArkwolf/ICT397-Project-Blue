#pragma once

	/// Internal Dependencies
#include "../FSM.hpp"

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
		 * @warning Fully virtual, must be implemented by inheritors!
		 */
	virtual void run(FSM* context) = 0;

		/*!
		 * @brief The behaviour to perform when this State is made no longer active/current.
		 * @param [in] context The contextual information to apply to the State's behaviour.
		 * @warning Fully virtual, must be implemented by inheritors!
		 */
	virtual void end(FSM* context) = 0;

		/*!
		 * @brief The behaviour to perform when recieving a message.
		 * @param [in] context The contextual information to apply to the State's behaviour.
		 * @warning Fully virtual, must be implemented by inheritors!
		 */
	virtual void read(FSM* context) = 0;
};
