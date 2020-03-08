#include "SceneManager.hpp"

BlueEngine::SceneManager::SceneManager() {
    L = luaL_newstate();
}