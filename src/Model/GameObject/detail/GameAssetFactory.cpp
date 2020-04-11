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
	case (GameObj_Static::gameObj_getType()):
		return new GameObj_Static();

	case (GameObj_Player::gameObj_getType()):
		return new GameObj_Player();

	case (GameObj_NPC::gameObj_getType()):
		return new GameObj_NPC();

	default:
		// Catch an invalid type
		return nullptr;
	};
}
