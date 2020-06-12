	/// Declaration Include
#include "Controller/AI/States/Custom.hpp"

	/// System Dependencies
#include <iostream>

State_Custom::State_Custom(std::shared_ptr<luabridge::LuaRef> start_func, std::shared_ptr<luabridge::LuaRef> run_func, std::shared_ptr<luabridge::LuaRef> end_func, std::shared_ptr<luabridge::LuaRef> read_func) {
	// Store the provided functions into the State's internals
	custom_behaviours[0] = start_func;
	custom_behaviours[1] = run_func;
	custom_behaviours[2] = end_func;
	custom_behaviours[3] = read_func;
}

void State_Custom::start(std::shared_ptr<GameObj_Base> context) {
	// Catch any errors thrown by the Lua function
	try {
		// Call the function and pass the parameter(s) into Lua
		(*custom_behaviours[0].get())(context.get());
	} catch (luabridge::LuaException const& err) {
		// Report the error, and stop the function
		std::cerr << "State_Custom::start() Lua Error! - \"" << err.what() << "\"\n";
	}
}

void State_Custom::run(std::shared_ptr<GameObj_Base> context, double t, double dt) {
	// Catch any errors thrown by the Lua function
	try {
		// Call the function and pass the parameter(s) into Lua
		(*custom_behaviours[1].get())(context.get(), t,  dt);
	}
	catch (luabridge::LuaException const& err) {
		// Report the error, and stop the function
		std::cerr << "State_Custom::run() Lua Error! - \"" << err.what() << "\"\n";
	}
}

void State_Custom::end(std::shared_ptr<GameObj_Base> context) {
	// Catch any errors thrown by the Lua function
	try {
		// Call the function and pass the parameter(s) into Lua
		(*custom_behaviours[2].get())(context.get());
	}
	catch (luabridge::LuaException const& err) {
		// Report the error, and stop the function
		std::cerr << "State_Custom::end() Lua Error! - \"" << err.what() << "\"\n";
	}
}

void State_Custom::read(std::shared_ptr<GameObj_Base> context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) {
	// Catch any errors thrown by the Lua function
	try {
		// Call the function and pass the parameter(s) into Lua
		(*custom_behaviours[3].get())(context.get(), msg_sender, msg_type, msg_attachment);
	}
	catch (luabridge::LuaException const& err) {
		// Report the error, and stop the function
		std::cerr << "State_Custom::read() Lua Error! - \"" << err.what() << "\"\n";
	}
}
