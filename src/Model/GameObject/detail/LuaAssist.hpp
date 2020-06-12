#pragma once

	/// Internal Dependencies
#include "Controller/Engine/LuaManager.hpp"
#include "../Types.hpp"
#include "../Base.hpp"
#include "../Static.hpp"
#include "../Item.hpp"
#include "../Character.hpp"
#include "../Player.hpp"
#include "../NPC.hpp"

	/*!
	 * @brief A simple set of functions that can be used to get the GameObject type identifiers.
	 * @note Exists to provide an easy way to get all values of the enum for scripting.
	 */
namespace GameObj_LuaHelper {
		//! Returns GameObj_Type::Invalid
	GameObj_Type Invalid();

		//! Returns GameObj_Type::Static
	GameObj_Type Static();

		//! Returns GameObj_Type::Item
	GameObj_Type Item();

		//! Returns GameObj_Type::Player
	GameObj_Type Player();

		//! Returns GameObj_Type::NPC
	GameObj_Type NPC();
};

// Registratiion of Enum GameObj_Type
namespace luabridge {
	template <>
	struct Stack <GameObj_Type> : EnumWrapper <GameObj_Type> {};
}
