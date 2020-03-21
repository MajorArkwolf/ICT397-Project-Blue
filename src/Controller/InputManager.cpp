#include "Controller/InputManager.hpp"

namespace Controller::Input {

    void InputManager::ProcessInput(SDL_Event &event) {
        // Handle input data from event
        InputData inputEvent;

        switch (event.type) {
            case SDL_KEYDOWN: {
                inputEvent.inputType = BLUE_InputType::KEY_PRESS;
            }; break;
            case SDL_KEYUP: {
                inputEvent.inputType = BLUE_InputType::KEY_RELEASE;
            }; break;
            case SDL_MOUSEMOTION: {
                inputEvent.inputType             = BLUE_InputType::MOUSE_MOTION;
                inputEvent.mouseMotionRelative.x = event.motion.xrel;
                inputEvent.mouseMotionRelative.y = event.motion.yrel;
                inputEvent.mouseMotionAbsolute.x = event.motion.x;
                inputEvent.mouseMotionAbsolute.y = event.motion.y;
            }; break;
            case SDL_MOUSEBUTTONDOWN: {
                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONDOWN;
            }; break;
            case SDL_MOUSEBUTTONUP: {
                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONUP;
            }; break;
            case SDL_MOUSEWHEEL: {
                inputEvent.inputType        = BLUE_InputType::MOUSE_WHEEL;
                inputEvent.mouseWheelMotion = event.wheel.y;
            }; break;
        }

        // for (auto pair : InputMap) {
        //    // Looks through input map for action match with pressed key
        //    if (pair.second == event.key.keysym.scancode) {
        //        inputEvent.inputAction = pair.first;
        //        break;
        //    }
        //}

        // Send inputEvent to top of game stack or whatever
    }

    void InputManager::ReadBindings() {
        auto &engine    = BlueEngine::Engine::get();
        auto baseBath   = engine.getBasePath();
        auto luaState   = engine.getLuaState();
        auto scriptPath = baseBath + "scripts/InputBindings.lua";
        if (luaL_dofile(luaState, scriptPath.c_str()) ||
            lua_pcall(luaState, 0, 0, 0)) {
            std::cout << "No script file found at '" << scriptPath
                      << "', aborting binding." << std::endl;
        }

        luaL_openlibs(luaState);
        luabridge::LuaRef table =
            luabridge::getGlobal(luaState, "InputBindings");
        if (!table.isNil()) {
            readLuaInputTable(table);
        }
    }

    BLUE_InputDevice InputManager::hashInputValue(const std::string &value) {
        if (value == "LSHIFT") {
            return BLUE_InputDevice::KEY_LSHIFT;
        }
        return BLUE_InputDevice::UNKNOWN;
    }

    void InputManager::bindKey(BLUE_InputAction action, luabridge::LuaRef &inputTable, std::string value) {

        luabridge::LuaRef inputRef = inputTable[value];

        if (inputRef.isString()) {

            std::string input = inputRef.cast<std::string>();
            InputMap.at(action) = hashInputValue(input);
            
        }
    }

    void InputManager::readLuaInputTable(luabridge::LuaRef inputTable) {

        bindKey(BLUE_InputAction::INPUT_JUMP, inputTable, "JUMP");
    }

    void InputManager::DefaultInputMap() {
        InputMap.at(BLUE_InputAction::INPUT_JUMP) = BLUE_InputDevice::KEY_SPACE;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_FORWARD) = BLUE_InputDevice::KEY_W;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_BACKWARD) = BLUE_InputDevice::KEY_S;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_LEFT) = BLUE_InputDevice::KEY_A;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_RIGHT) = BLUE_InputDevice::KEY_D;
        InputMap.at(BLUE_InputAction::INPUT_ACTION_1) = BLUE_InputDevice::MOUSE_LEFT;
        InputMap.at(BLUE_InputAction::INPUT_ACTION_2) =
            BLUE_InputDevice::MOUSE_RIGHT;
        InputMap.at(BLUE_InputAction::INPUT_SPRINT) = BLUE_InputDevice::KEY_LSHIFT;
        InputMap.at(BLUE_InputAction::INPUT_CROUCH) = BLUE_InputDevice::KEY_LCTRL;
    }

    InputManager::~InputManager() {}
}
