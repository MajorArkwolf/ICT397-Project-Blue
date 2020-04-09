#pragma once

	/// System Dependencies
#include <map>

	/// Internal Dependencies
#include "GameObject_Management.hpp"

	/*!
	 * @author William Vlahos
	 * @brief A game-specific data manager, used to 'attach' external resources to a single 'game-being'.
	 * @note Provides an API for easy management and control of the 'attached' external resources.
	 */
class Entity {
	public:
			/*!
			 * @brief The default Entity constructor.
			 * @note Does minimal work, as the Entity class attributes will automatically initialise themselves.
			 */
		Entity();

			/*!
			 * @brief The default Entity destructor.
			 * @note A call to export_data() must be made before Entity's destructor is invoked to externally retain its data.
			 * @note This will remove all 'attached' GameObjects on call.
			 * @warning Prior pointers provided for the Entity's GameObject 'attachments' will no longer be valid!
			 * @see Entity::clear()
			 */
		~Entity();

			/*!
			 * @brief Removes all 'attached' external resources from the Entity.
			 * @warning Prior pointers provided for the Entity's GameObject 'attachments' will no longer be valid!
			 */
		void clear();

			/*!
			 * @brief Counts the amount of GameObjects currently 'attached' to the Entity.
			 * @return An integer value counting the amount of elements in attachments.
			 * @see Entity::attachments
			 */
		unsigned int count();

			/*!
			 * @brief Calls the display() function for each external resource 'attached' to the Entity.
			 * @note Any 'attachment' with an empty display() implementation will not be displayed.
			 * @see GameObject::display()
			 */
		void display();

			/*!
			 * @brief Calls the update() function for each external resource 'attached' to the Entity.
			 * @param t The time elapsed since the engine started.
			 * @param delta_t The time elapsed since the prior update (i.e. the delta time).
			 * @note Any 'attachment' with an empty display() implementation will not be displayed.
			 * @see GameObject::update()
			 */
		void update(double, t, double delta_t);

			/*!
			 * @brief Calls the data_export() function for each external resource 'attached' to the Entity.
			 * @return True if all of the calls on all 'attachments' succeeded, False otherwise.
			 * @note Any 'attachment' with an empty data_export() implementation will not be exported.
			 * @see GameObject::data_export()
			 */
		bool data_export();

			/*!
			 * @brief Calls the data_import() function for each external resource 'attached' to the Entity.
			 * @return True if all of the calls on all 'attachments' succeeded, False otherwise.
			 * @note Any 'attachment' with an empty data_import() implementation will not be imported.
			 * @see GameObject::data_import()
			 */
		bool data_import();

			/*!
			 * @brief Checks if a specific GameObject 'attachment' is stored in the Entity.
			 * @tparam T The type of GameObject 'attachment' to search for.
			 * @return True if a T 'attachment' is found in data_storage, False otherwise.
			 * @see GameObject
			 */
		template<typename T>
		bool has();

			/*!
			 * @brief Return a reference to a specific GameObject 'attachment' stored in the Entity.
			 * @tparam T The type of GameObject 'attachment' to return a reference of.
			 * @return A GameObject reference to the T 'attachment', or nullptr.
			 * @warning Do not perform any memory management on the provided reference, or issues will occur!
			 * @warning The reference provided will only be reliably valid at this function call!
			 * @see GameObject
			 */
		template<typename T>
		GameObject& get();

			/*!
			 * @brief Creates and stores a specific GameObject 'attachment' into the Entity.
			 * @tparam T The type of GameObject 'attachment' to create and store.
			 * @param [in] path The target external file path to use when managing the GameObject.
			 * @return True if the T 'attachment' was successfully created and stored, False otherwise.
			 * @warning If an existing GameObject 'attachment' of type T is already stored, it will be deleted to make room!
			 * @see Entity::remove()
			 * @see GameObject::GameObject()
			 * @see GameObject
			 */
		template<typename T>
		bool create(std::string path);

			/*!
			 * @brief Deletes a specific GameObject 'attachment' from the Entity.
			 * @tparam T The type of GameObject 'attachment' to remove.
			 * @see GameObject::~GameObject()
			 * @see GameObject
			 */
		template<typename T>
		void remove();

	protected:
			/*!
			 * @brief Stores the data for the 'attached' GameObjects.
			 * @note Only a single attachment of each type will stored.
			 * @see GameObject_Detail::GameObject_Types
			 * @see GameObject_MiscProperties
			 */
		std::map<GameObject_Detail::GameObject_Types, GameObject_MiscProperties> attachments;
};
