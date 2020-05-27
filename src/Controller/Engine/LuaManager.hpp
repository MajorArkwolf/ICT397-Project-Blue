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

    /*!
     * @brief Provides a templated method to register C++ enums to Lua.
     * @note Expects the use of the LuaBridge stack struct system in addition to this.
     */
template <typename T>
struct EnumWrapper
{
    static typename std::enable_if<std::is_enum<T>::value, void>::type push(lua_State* L, T value)
    {
        lua_pushnumber(L, static_cast<std::size_t> (value));
    }

    static typename std::enable_if<std::is_enum<T>::value, T>::type get(lua_State* L, int index)
    {
        return static_cast <T> (lua_tointeger(L, index));
    }
};
