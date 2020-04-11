#pragma once

	/// Internal Dependencies
#include "GameObject_Base.hpp"

	//! A small library for GameObject construction through Factory Methods.
namespace GameAssetFactory {
		/*!
		 * @brief Parameterised GameObject Factory.
		 * @param [in] type A string containing the target type of GameObject to generate.
		 * @return A pointer to a newly assigned GameObject, or nullptr on error.
		 * @see GameObject_Base
		 * @see FactoryKey_Type
		 */
	GameObject_Base* GameObject(std::string type);
};
