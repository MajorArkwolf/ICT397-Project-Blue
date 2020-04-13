#pragma once

	/// System Dependencies
#include <memory>

	/// Internal Dependencies
#include "GameObj_Base.hpp"

	//! A small library for GameObject construction through Factory Methods.
namespace GameAssetFactory {
		/*!
		 * @brief Parameterised GameObject Factory.
		 * @param [in] type A GameObject type identifier for the target factory output.
		 * @return A pointer to a newly assigned GameObject, or nullptr on error.
		 */
	std::shared_ptr<GameObj_Base> GameObject(GameObjType type);
};
