#pragma once

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}
#include "LuaBridge/LuaBridge.h"

/**
 * @class LuaManager
 * @brief A class used to give out Lua instances
 */
class LuaManager {
  public:
    /**
     * @brief Returns a static instance of the LuaManager
     * @return Returns a static instance of the LuaManager
     */
    static LuaManager &getInstance() {
        static LuaManager instance;
        return instance;
    }

    /**
     * @brief Returns the lua state
     * @return The Lua state
     */
    lua_State *getLuaState();

  private:
    /// The lua state
    lua_State *luaState = nullptr;
    LuaManager();
    ~LuaManager();
    LuaManager(const LuaManager &other) = delete;
    LuaManager operator=(LuaManager &rhs) = delete;
};
