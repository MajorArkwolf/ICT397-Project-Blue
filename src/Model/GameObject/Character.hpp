#pragma once

	/// System Dependencies
#include <string>
#include <vector>
#include <map>

	/// Internal Dependencies
#include "Base.hpp"

#include "Controller/Animator.hpp"

	/*!
	 * @brief A sub-parent class for inteligent and controlled actor GameObjects.
	 * @note This is only a polymorphic base, and can not be instantiated on its own.
	 */
class GameObj_Character : virtual public GameObj_Base {
public:

		/*!
		 * @brief Default constructor, does nothing.
		 * @note This only exists due to a bug with MSVC failing to either generate or prevent calling this from a derived class's constructor.
		 */
	GameObj_Character() {}

		/*!
		 * @brief Identifies the GameObject's type.
		 * @return Always returns GameObj_Type::Invalid for GameObj_Character.
		 * @warning Must be implemented by inheritors!
		 */
	GameObj_Type type() const = 0;

		/*!
		 * @brief Assigns a status (with a value) to the character.
		 * @param [in] key The string to identify the status by.
		 * @param [in] value The value to assign to the status.
		 * @note If the status key does not exist, it will be created.
		 * @note If the status key does exist, its assigned value will be overwritten.
		 */
	void status_assign(const std::string& key, float value);

		/*!
		 * @brief Counts the amount of unique statuses are assigned to the GameObject.
		 * @return The amount of unique status keys stored in this GameObject.
		 */
	unsigned long long status_count();

		/*!
		 * @brief Checks if the character has a specific status.
		 * @param [in] key The string to identify the status by.
		 * @return True if the character has the specified status key, False otherwise.
		 */
	bool status_has(const std::string& key);

		/*!
		 * @brief Generates a list of unique status keys stored in this GameObject.
		 * @return A vector of the GameObject's status key strings.
		 * @note Any modifications to the returned list will not affect the stored statuses.
		 */
	std::vector<std::string> status_list();

		/*!
		 * @brief Returns a copy of the value assigned to the character's status.
		 * @param [in] key The string to identify the status by.
		 * @return A copy of the status' value, or 0.0f if the status was not found.
		 * @note Function status_has() should be called prior to confirm the status exists.
		 * @warning The return value alone cannot be used to determine if an error had occured!
		 */
	float status_get(const std::string& key);

		/*!
		 * @brief Deletes a specific status (and it's assigned value) from the character.
		 * @param [in] key The string to identify the status by.
		 * @note If the targeted status does not exist, no changes will occur.
		 */
	void status_delete(const std::string& key);

		/*!
		 * @brief Removes all statuses (and their values) from the character.
		 * @note If the character has no statuses, no changes will occur.
		 */
	void status_clear();

		/*!
		 * @brief Registers this GameObject class to the Lua subscripting system.
		 * @note Called in the constructor, constructor is responsible for only calling once.
		 */
	static void lua_init_register();

    void update(double t, double dt) override;

    void add_animator();

    void change_animation(const std::string& animToLoad, bool stopOnEnd = false);

private:
		/*!
		 * @brief Stores a dynamic amount of configurable character statuses.
		 * @note All status values are mapped to a unique name.
		 */
	std::map<std::string, float> statuses;

  protected:
    std::unique_ptr<Controller::Animator> animator = nullptr;


};
