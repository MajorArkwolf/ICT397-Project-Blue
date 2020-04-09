#pragma once

/*!
 * @file GameObject_Management.hpp
 * @brief The main header to include for the centralisation of all GameObject management.
 * @note This file contains information about the GameObject type declarations.
 */

	/// System Dependencies
#include <memory>

	/// Internal Dependencies
// The 'base' GameObject
#include "GameObject.hpp"

	/*!
	 * @author William Vlahos
	 * @brief Stores additional information for GameObjects for modular storage of management information.
	 * @note None of this data should be stored by a GameObject to limit clutter, however access is fine.
	 */
struct GameObject_MiscProperties {
	public:
			/*!
			 * @brief The default constructor.
			 * @note Only initialises the contents of this structure, does not perform memory management.
			 */
		GameObject_MiscProperties() : data(nullptr), path("") {}

			/*!
			 * @brief A unique and managed reference to a GameObject.
			 * @note Either stores a pointer to the GameObject's position on the stack, or nullptr.
			 */
		std::shared_ptr<GameObject> data;

			/*!
			 * @brief The target external file path to use when managing the GameObject.
			 * @warning Paths must conform to the Unix format standard to be valid!
			 */
		std::string path;
};

	/*!
	 * @brief A set of misc. GameObject management tools.
	 * @note This name-space exists to remove clutter from other engine subsystems.
	 */
namespace GameObject_Detail {
		/*!
		 * @brief An enumeration for the many types of GameObjects.
		 * @warning! Failure to register 'child' GameObjects here may lead to unexpected behaviour!
		 */
	enum class GameObject_Types {
		//! Used to indicate an error regarding the GameObject types.
		invalid
	};

		/*!
		 * @brief Generic check for the GameObject type.
		 * @tparam T The C++ type to check.
		 * @return A value from the enumeration class GameObject_Types
		 * @note Always returns GameObject_Types::invalid, unless overloaded by a template specialisation.
		 * @see GameObject_Types
		 */
	template <class T>
	GameObject_Types type_GameObject() {
		// Default to indicating the GameObject type provided is invalid
		return GameObject_Types::invalid;
	}

		/*!
		 * @brief A GameObject type specialisation for the base GameObject.
		 * @return A value from the enumeration class GameObject_Types
		 * @note Always returns GameObject_Types::invalid.
		 * @see GameObject_Types
		 * @see GameObject
		 */
	template <>
	GameObject_Types type_GameObject<GameObject>() {
		// Indicate that raw use of the base GameObject type is invalid.
		return GameObject_Types::invalid;
	}
}
