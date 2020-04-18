#pragma once

	/// The base GameObject
#include "Base.hpp"

	/// Constant GameObject type identifying value definitions
constexpr GameObjType GAMEOBJ_INVALID = 0u;
constexpr GameObjType GAMEOBJ_STATIC = 1u;
constexpr GameObjType GAMEOBJ_PLAYER = 2u;
constexpr GameObjType GAMEOBJ_NPC = 3u;
