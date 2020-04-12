#include "Controller/Engine/LuaManager.hpp"

#include "LuaManager.hpp"

lua_State *LuaManager::getLuaState() {
    if (luaState == nullptr) {
        luaState = luaL_newstate();
    }
    return luaState;
}

LuaManager::~LuaManager() {}
LuaManager::LuaManager() {
    luaState = luaL_newstate();
    luaL_openlibs(luaState);
}
