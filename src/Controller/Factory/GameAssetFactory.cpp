#include "GameAssetFactory.hpp"

	/// Internal Dependencies
#include "Model/GameObject/Static.hpp"
#include "Model/GameObject/Player.hpp"
#include "Model/GameObject/NPC.hpp"

Controller::Factory::Factory() {
    terrain.Init();
    //terrain.LoadLua();
}

auto Controller::Factory::get() -> Factory & {
    static auto instance = Factory{};
    return instance;
}

std::shared_ptr<GameObj_Base> Controller::Factory::GameObject(GameObjType type) {
	// Process the provided type key
	std::shared_ptr<GameObj_Base> object = nullptr;
	switch (type)
	{
	case (GAMEOBJ_STATIC):
		object = std::make_shared<GameObj_Static>();
		break;
	case (GAMEOBJ_PLAYER):
		object = std::make_shared<GameObj_Player>();
		break;
	case (GAMEOBJ_NPC):
		object = std::make_shared<GameObj_NPC>();
		break;

	default:
		// Catch an invalid type
		object = nullptr;
		//return nullptr;
	}
	return object;
}
