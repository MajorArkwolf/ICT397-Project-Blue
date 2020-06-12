	/// Declaration Include
#include "LuaAssist.hpp"

GameObj_Type GameObj_LuaHelper::Invalid()
{ return GameObj_Type::Invalid; }

GameObj_Type GameObj_LuaHelper::Static()
{ return GameObj_Type::Static; }

GameObj_Type GameObj_LuaHelper::Item()
{ return GameObj_Type::Item; };

GameObj_Type GameObj_LuaHelper::Player()
{ return GameObj_Type::Player; };

GameObj_Type GameObj_LuaHelper::NPC()
{ return GameObj_Type::NPC; };
