#include "Controller/Engine/LuaManager.hpp"

#include "LuaManager.hpp"

lua_State *LuaManager::getLuaState() {
    if (luaState == nullptr) {
        luaState = luaL_newstate();
    }
    return luaState;
}

void LuaManager::LuaRunScript(const std::string &path) {
    luaL_dofile(LuaManager::getInstance().getLuaState(), path.c_str());
}


LuaManager::LuaManager() {
    luaState = luaL_newstate();
    luaL_openlibs(luaState);

    luabridge::getGlobalNamespace(luaState).addFunction("runScript", &LuaManager::LuaRunScript);
}
