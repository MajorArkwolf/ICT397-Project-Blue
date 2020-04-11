#pragma once

	/// Internal Dependencies
#include "GameObject_Base.hpp"

	//! A small library for GameObject construction through Factory Methods.
namespace GameAssetFactory {
		//! Encapsulates constants to reduce clutter for GameAssetfactory.
	namespace Constants {
		using FactoryKey_Type = extern const unsigned int;

			//! A key to identify GameObj_Static.
		FactoryKey_Type GAMEOBJ_STATIC = 0;

			//! A key to identify GameObj_Player.
		FactoryKey_Type GAMEOBJ_PLAYER = 0;

			//! A key to identify GameObj_NPC.
		FactoryKey_Type GAMEOBJ_NPC = 0;
	}

		/*!
		 * @brief Parameterised GameObject Factory.
		 * @param [in] type A string containing the target type of GameObject to generate.
		 * @return A pointer to a newly assigned GameObject, or nullptr on error.
		 * @see GameObject_Base
		 * @see FactoryKey_Type
		 */
	GameObject_Base* GameObject(std::string type);
};
