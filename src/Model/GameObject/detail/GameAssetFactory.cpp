	/// Declaration Include
#include "../GameAssetFactory.hpp"

	/// Internal Dependencies
#include "../GameObj_Static.hpp"
#include "../GameObj_Player.hpp"
#include "../GameObj_NPC.hpp"

std::shared_ptr<GameObj_Base> GameAssetFactory::GameObject(GameObjType type) {
	// Process the provided type key
	switch (type)
	{
	case (GAMEOBJ_STATIC):
		return std::shared_ptr<GameObj_Base>(new GameObj_Static());

	case (GAMEOBJ_PLAYER):
		return std::shared_ptr<GameObj_Base>(new GameObj_Player());

	case (GAMEOBJ_NPC):
		return std::shared_ptr<GameObj_Base>(new GameObj_NPC());

	default:
		// Catch an invalid type
		return nullptr;
	}
}
