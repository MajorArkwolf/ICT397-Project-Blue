#pragma once

	/// Internal Dependencies
#include "Entity.hpp"
#include "../../Controller/Engine/BaseState.hpp"

	/*!
	 * @author William Vlahos
	 * @brief An Entity manager.
	 * @see Entity
	 */
class Scene : virtual public BaseState {
	public:
			/*!
			 * @brief Stores all Scene (and its contained Entities') data to an external file.
			 * @param [in] file_path The path to a target external file to store the Scene's data into.
			 * @note No GameObject data will be directly stored at the provided path for this function.
			 * @note GameObject data saving will be managed by the Scene calling data_export() on all stored Entities.
			 */
		bool save(std::string file_path);

			/*!
			 * @brief Gathers all Scene (and its contained Entities') data from an external file.
			 * @param [in] file_path The path to a target external file to gather the Scene's data from.
			 * @note No GameObject data will be directly loaded at the provided path for this function.
			 * @note GameObject data loading will be managed by the Scene calling data_import() on all stored Entities.
			 */
		bool load(std::string file_path);

			/*!
			 * @brief Counts the amount of Entities currently stored in the Scene.
			 * @return An integer value counting the amount of elements in entity_storage.
			 * @see Scene::entity_storage
			 */
		unsigned int count();

			/*!
			 * @brief Calls the display() function for each Entity stored in the Scene.
			 * @note Any stored Entity 'attachments' with an empty display() implementation will not be displayed.
			 * @see Entity::display()
			 */
		void display();

			/*!
			 * @brief Calls the update() function for each Entity stored in the Scene.
			 * @param t The time elapsed since the engine started.
			 * @param delta_t The time elapsed since the prior update (i.e. the delta time).
			 * @note Any stored Entity 'attachments' with an empty update() implementation will not be displayed.
			 * @see Entity::update()
			 */
		void update(double t, double delta_t);

			/*!
			 * @brief Checks a specific Entity is stored in the Scene.
			 * @param [in] name The 'key' Entity identifier to search by.
			 * @return True if the target Entity was found, False otherwise.
			 */
		bool has(std::string name);

			/*!
			 * @brief Gather a specific Entity stored in the Scene.
			 * @param [in] name The 'key' Entity identifier to search by.
			 * @return A reference to the target Entity if found, nullptr otherwise.
			 * @warning Do not perform any memory management on the provided reference, or issues will occur!
			 * @warning The reference provided will only be reliably valid at this function call!
			 * @see Entity
			 */
		Entity &get(std::string name);

			/*!
			 * @brief Creates a new Entity to be stored in the Scene.
			 * @param [in] name The 'key' identifier to assign to the new Entity.
			 * @return True if the 'key' was unique to the Scene and the Entity was created, False otherwise.
			 * @note This will fail if an existing Entity stored in the Scene has already been allocated the provided name.
			 */
		bool add(std::string name);

			/*!
			 * @brief Removes a specific Entity stored in the Scene.
			 * @param [in] name The 'key' Entity identifier to identify the target for deletion.
			 * @return True if the Entity was found and deleted from the Scene, False otherwise.
			 * @note This will return False if the Entity with the specified name was not stored in the Scene.
			 * @warning Prior pointers provided for the Scene's Entities will no longer be valid!
			 * @warning This will delete all GameObjects attached to the Entity!
			 */
		bool remove(std::string name);

			/*!
			 * @brief Deletes all of the Entities stored in the Scene.
			 * @warning This will delete all GameObjects attached to the Entities!
			 * @see Scene::remove()
			 */
		void clear();

			/*!
			 * @brief The Scene initialiser, used to replace the object constructor due to inheritance issues.
			 * @see BaseState::Init()
			 */
		void Init();

			/*!
			 * @brief The Scene 'uninitializer', used to replace the object destructor due to the inheritance issues.
			 * @see BaseState::unInit()
			 */
		void unInit();

			/*!
			 * @brief The Scene handler for input data.
			 * @note Currently stubbed out with this implementation, does nothing.
			 * @see BaseState::handleInputData
			 */
		void handleInputData(Controller::Input::InputData inputData);

	protected:
			/*!
			 * @brief Stores the Entities.
			 * @note Maps a unique name string key to each Entity.
			 * @warning The Entities have no understanding of their name, only Scene contains this information!
			 * @see Entity
			 */
		std::map<std::string, Entity> entity_storage;
};
