	/// Declaration Include
#include "LuaAssist.hpp"

namespace GameObj_Type_LuaHelper {
	GameObj_Type Invalid()
	{ return GameObj_Type::Invalid; }

	GameObj_Type Static()
	{ return GameObj_Type::Static; }

	GameObj_Type Item()
	{ return GameObj_Type::Item; };

	GameObj_Type Player()
	{ return GameObj_Type::Player; };

	GameObj_Type NPC()
	{ return GameObj_Type::NPC; };
};
