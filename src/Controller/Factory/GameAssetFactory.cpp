#include "GameAssetFactory.hpp"

Controller::Factory::Factory() {
    terrain.Init();
    //terrain.LoadLua();
}

auto Controller::Factory::get() -> Factory & {
    static auto instance = Factory{};
    return instance;
}
