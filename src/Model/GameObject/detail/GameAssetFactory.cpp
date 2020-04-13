	/// Declaration Include
#include "../GameAssetFactory.hpp"

	/// Internal Dependencies
#include "../GameObj_Static.hpp"
#include "../GameObj_Player.hpp"
#include "../GameObj_NPC.hpp"

GameAssetFactory::GameObject(GameObjectType type) {
	// Process the provided type key
	switch (type)
	{
	case (GameObj_Static::gameObj_getType()):
		return std::shared_ptr<GameObject_Base>(new GameObj_Static());

	case (GameObj_Player::gameObj_getType()):
		return std::shared_ptr<GameObject_Base>(new GameObj_Player());

	case (GameObj_NPC::gameObj_getType()):
		return std::shared_ptr<GameObject_Base>(new GameObj_NPC());

	default:
		// Catch an invalid type
		return nullptr;
	};
}
