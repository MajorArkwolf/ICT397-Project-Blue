	/// Declaration Include
#include "Controller/AI/States/Custom.hpp"

State_Custom::State_Custom(std::shared_ptr<luabridge::LuaRef> start_func, std::shared_ptr<luabridge::LuaRef> run_func, std::shared_ptr<luabridge::LuaRef> end_func, std::shared_ptr<luabridge::LuaRef> read_func) {

}

void State_Custom::start(std::shared_ptr<GameObj_Base> context) {

}

void State_Custom::run(std::shared_ptr<GameObj_Base> context, double t, double dt) {

}

void State_Custom::end(std::shared_ptr<GameObj_Base> context) {

}

void State_Custom::read(std::shared_ptr<GameObj_Base> context, BlueEngine::ID msg_sender, Message_Type msg_type, float msg_attachment) {

}
