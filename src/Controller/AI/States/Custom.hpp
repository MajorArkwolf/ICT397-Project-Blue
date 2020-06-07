#pragma once

	/// System Dependencies
#include <string>
#include <memory>

	/// Internal Dependencies
#include "Controller/Engine/LuaManager.hpp"
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
		 * @param [in] start_func A Lua function, called with identical parameters as the C++ start().
		 * @param [in] run_func A Lua function, called with identical parameters as the C++ run().
		 * @param [in] end_func A Lua function, called with identical parameters as the C++ end().
		 * @param [in] read_func A Lua function, called with identical parameters as the C++ read().
		 */
	State_Custom(std::shared_ptr<luabridge::LuaRef> start_func, std::shared_ptr<luabridge::LuaRef> run_func, std::shared_ptr<luabridge::LuaRef> end_func, std::shared_ptr<luabridge::LuaRef> read_func);

		/*!
		 * @brief Invokes the Lua function for the State's starting behaviour.
		 * @param [in] context The contextual GameObject reference to pass to the Lua function.
		 * @note This will catch (and print to cerr) any LuaException errors thrown.
		 */
	void start(std::shared_ptr<GameObj_Base> context);

		/*!
		 * @brief Invokes the Lua function for the State's starting behaviour.
		 * @param [in] context The contextual GameObject reference to pass to the Lua function.
		 * @param [in] t The amount of time from the engine program starting.
		 * @param [in] dt The amount of delta time from the prior operation of this behaviour.
		 * @note This will catch (and print to cerr) any LuaException errors thrown.
		 */
	void run(std::shared_ptr<GameObj_Base> context, double t, double dt);

		/*!
		 * @brief Invokes the Lua function for the State's starting behaviour.
		 * @param [in] context The contextual GameObject reference to pass to the Lua function.
		 * @note This will catch (and print to cerr) any LuaException errors thrown.
		 */
	void end(std::shared_ptr<GameObj_Base> context);

		/*!
		 * @brief Invokes the Lua function for the State's starting behaviour.
		 * @param [in] context The contextual GameObject reference to pass to the Lua function.
		 * @param [in] msg_sender The identifier of the FSM that generated this message.
		 * @param [in] msg_type The type identifier of this message.
		 * @param [in] msg_attachment The secondary message data, used to suppliment the message type.
		 * @note This will catch (and print to cerr) any LuaException errors thrown.
		 */
	void read(std::shared_ptr<GameObj_Base> context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment);

private:
		/*!
		 * @brief Stored managed references to the invokable Lua functions.
		 * @note Ascending indexing order is start, run, end, read.
		 */
	std::shared_ptr<luabridge::LuaRef> custom_behaviours[4];
};
