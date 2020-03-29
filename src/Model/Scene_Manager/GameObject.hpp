#pragma once

	/// System Dependencies
#include <string>

	/*!
	 * @author William Vlahos
	 * @brief A virtual base GameObject class, used to define a polymorphic base structure.
	 * @note Used as parent for all data structures that directly encapsulate game-data.
	 */
class GameObject {
	public:
			/*!
			 * @brief The default GameObject constructor.
			 * @note Does nothing on its own.
			 * @warning Must be extended by inheritors!
			 */
		GameObject() {};

			/*!
			 * @brief The virtual GameObject destructor.
			 * @warning Must be implemented by inheritors!
			 */
		virtual ~GameObject() = 0;

			/*!
			 * @brief A call to display the GameObject to the user.
			 * @warning Must be implemented by inheritors!
			 */
		virtual void display() = 0;

			/*!
			 * @brief Updates the contents of the GameObject relative to the time passed.
			 * @param t The time elapsed since the engine started.
			 * @param delta_t The time elapsed since the prior update (i.e. the delta time).
			 * @note Provide an empty implementation to disable updating.
			 * @warning Must be implemented by inheritors!
			 */
		virtual void update(double t, double delta_t) = 0;

			/*!
			 * @brief Stores the current contents of the GameObject into an external file.
			 * @param [in] file_path The target external file path to access for this operation.
			 * @note Provide an empty implementation to disable exporting.
			 * @warning Must be implemented by inheritors!
			 */
		virtual bool data_export(std::string file_path) = 0;

			/*!
			 * @brief Gathers the current contents of an external file into the GameObject.
			 * @param [in] file_path The target external file path to access for this operation.
			 * @note Provide an empty implementation to disable importing.
			 * @warning Must be implemented by inheritors!
			 */
		virtual bool data_import(std::string file_path) = 0;
};
