#pragma once

	/*!
	 * @brief Stores the identifiers for each GameObject type.
	 * @warning The GameObject type identifiers should not be confused with the unique GameObject identifiers!
	 */
enum class GameObj_Type
{
	Invalid = 0u,
	Static = 1u,
	Item = 2u,
	Player = 3u,
	NPC = 4u
};
