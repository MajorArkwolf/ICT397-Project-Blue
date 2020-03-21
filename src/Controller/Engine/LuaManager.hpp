#pragma once

extern "C" {
	#include "lauxlib.h"
	#include "lua.h"
	#include "lualib.h"
}
#include "LuaBridge/LuaBridge.h"

class LuaManager {
  public:
    static LuaManager &getInstance() {
        static LuaManager instance;
        return instance;
    }
    lua_State *getLuaState();

  private:
    lua_State *luaState = nullptr;
    LuaManager();
    ~LuaManager();
    LuaManager(const LuaManager &other) = delete;
    LuaManager operator=(LuaManager &rhs) = delete;
};