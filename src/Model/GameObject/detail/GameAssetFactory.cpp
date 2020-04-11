	/// Declaration Include
#include "../GameAssetFactory.hpp"

	/// Internal Dependencies
#include "../GameObj_Static.hpp"
#include "../GameObj_Player.hpp"
#include "../GameObj_NPC.hpp"

GameAssetFactory::GameObject(std::string type) {
	// Process the provided type key
	switch (type)
	{
	case (Constants::GAMEOBJ_STATIC):
		return new GameObj_Static();

	case (Constants::GAMEOBJ_PLAYER):
		return new GameObj_Static();

	case (Constants::GAMEOBJ_OBJ):
		return new GameObj_NPC();

	default:
		// Catch an invalid type
		return nullptr;
	};
}
