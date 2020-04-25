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
