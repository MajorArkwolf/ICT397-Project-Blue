#include "Controller/Engine/BaseState.hpp"
#include <iostream>
extern "C" {
	#include "lauxlib.h"
	#include "lua.h"
	#include "lualib.h"
}
#include "LuaBridge/LuaBridge.h"

namespace BlueEngine {
    class SceneManager : public BaseState {
      public:
        SceneManager();
        ~SceneManager() = default;

      private:
        lua_State *L;
    };
};