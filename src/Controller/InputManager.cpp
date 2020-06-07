#include "Controller/InputManager.hpp"

#include <iostream>
#include <utility>

#include "Controller/Engine/Engine.hpp"

namespace Controller::Input {

    InputManager::InputManager() {
        populateInputMap();
        DefaultInputMap();
        createEnumStringPairs();
        resetKeyStates();
        ReadBindings();

        luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
            .beginClass<glm::ivec2>("ivec2")
            .addConstructor<void (*)(int, int)>()
            .addProperty("x", &glm::ivec2::x)
            .addProperty("y", &glm::ivec2::y)
            .endClass();

        luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
            .beginClass<InputData>("InputData")
            .addProperty("relativeMouseMotion", &InputData::mouseMotionRelative)
            .addProperty("absoluteMouseMotion", &InputData::mouseMotionAbsolute)
            .addProperty("mouseWheelMotion", &InputData::mouseWheelMotion)
            .addProperty("action", &InputData::actionString)
            .addProperty("inputType", &InputData::typeString)
            .endClass();
    }

    InputManager &InputManager::getInstance() {
        static auto instance = InputManager{};

        return instance;
    }

    InputData InputManager::ProcessInput(GLEQevent &event) {
        auto &engine = BlueEngine::Engine::get();
        // Handle input data from event
        InputData inputEvent;
        int width, height;
        glfwGetWindowSize(engine.window, &width, &height);

        static glm::ivec2 currentMousePos{width / 2, height / 2};

        switch (event.type) {
            case GLEQ_KEY_PRESSED: {
                inputEvent.inputType = BLUE_InputType::KEY_PRESS;
            } break;
            case GLEQ_KEY_RELEASED: {
                inputEvent.inputType = BLUE_InputType::KEY_RELEASE;
            } break;
            case GLEQ_CURSOR_MOVED: {
                const auto prevMousePos{currentMousePos};

                currentMousePos.x = event.pos.x;
                currentMousePos.y = event.pos.y;

                inputEvent.inputType             = BLUE_InputType::MOUSE_MOTION;
                inputEvent.mouseMotionRelative.x = currentMousePos.x - prevMousePos.x;
                inputEvent.mouseMotionRelative.y = currentMousePos.y - prevMousePos.y;
                inputEvent.mouseMotionAbsolute.x = event.pos.x;
                inputEvent.mouseMotionAbsolute.y = event.pos.y;

                inputEvent.mouseMotionRelative.y *= -1;
            } break;
            case GLEQ_BUTTON_PRESSED: {
                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONDOWN;
            } break;
            case GLEQ_BUTTON_RELEASED: {
                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONUP;
            } break;
            case GLEQ_SCROLLED: {
                inputEvent.inputType        = BLUE_InputType::MOUSE_WHEEL;
                inputEvent.mouseWheelMotion = event.scroll.y;

            } break;
            case GLEQ_WINDOW_RESIZED: {
                inputEvent.inputType = BLUE_InputType::WINDOW_RESIZE;
            } break;
            default: break;
        }

        switch (inputEvent.inputType) {
            case BLUE_InputType::KEY_PRESS:
            case BLUE_InputType::KEY_RELEASE: {
                for (auto &itr : InputMap) {
                    if (itr.second == event.keyboard.key) {
                        inputEvent.inputAction = itr.first;
                    }
                }
            } break;

            case BLUE_InputType::MOUSE_BUTTONDOWN: {
                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONDOWN;
                if (event.mouse.button == GLFW_MOUSE_BUTTON_LEFT) {
                    inputEvent.inputAction = BLUE_InputAction::MOUSE_LEFT;
                } else if (event.mouse.button == GLFW_MOUSE_BUTTON_RIGHT) {
                    inputEvent.inputAction = BLUE_InputAction::MOUSE_RIGHT;
                } else if (event.mouse.button == GLFW_MOUSE_BUTTON_MIDDLE) {
                    inputEvent.inputAction = BLUE_InputAction::MOUSE_MIDDLE;
                }
            } break;
            case BLUE_InputType::MOUSE_BUTTONUP: {
                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONUP;
                if (event.mouse.button == GLFW_MOUSE_BUTTON_LEFT) {
                    inputEvent.inputAction = BLUE_InputAction::MOUSE_LEFT;
                } else if (event.mouse.button == GLFW_MOUSE_BUTTON_RIGHT) {
                    inputEvent.inputAction = BLUE_InputAction::MOUSE_RIGHT;
                } else if (event.mouse.button == GLFW_MOUSE_BUTTON_MIDDLE) {
                    inputEvent.inputAction = BLUE_InputAction::MOUSE_MIDDLE;
                }
            } break;
            default: {

            } break;
        }
        inputEvent.actionString = hashInputActionToString(inputEvent.inputAction);
        inputEvent.typeString   = hashInputTypeToString(inputEvent.inputType);
        return inputEvent;
    }

    void InputManager::ReadBindings() {
        auto useLuaInputs   = false;
        const auto basePath = BlueEngine::Engine::get().basepath;

        auto &LuaManager = LuaManager::getInstance();

        auto *const luaState         = LuaManager.getLuaState();
        const std::string scriptPath = basePath + "res/scripts/InputBindings.lua";
        if (luaL_dofile(luaState, scriptPath.c_str())) {
            std::cout << "No script file found at '" << scriptPath << "', aborting input binding."
                      << std::endl;
        }
        lua_pcall(luaState, 0, 0, 0);
        luaL_openlibs(luaState);
        const auto luaOverride = luabridge::getGlobal(luaState, "UseLuaInputs");
        if (luaOverride.isBool()) {
            useLuaInputs = luaOverride.cast<bool>();
        }
        if (useLuaInputs) {
            const auto table = luabridge::getGlobal(luaState, "InputBindings");
            if (!table.isNil()) {
                readLuaInputTable(table);
            }
        }
    }

    int InputManager::hashStringToGLFWKey(const std::string &value) const {
        for (const auto &n : stringScancodePairs) {
            if (n.first == value) {
                return n.second;
            }
        }
        // unknown key
        return 0;
    }

    std::string InputManager::hashGLFWKeyToString(const int value) const {
        for (const auto &n : stringScancodePairs) {
            if (n.second == value) {
                return n.first;
            }
        }
        return std::string("Unknown");
    }

    std::string InputManager::hashInputActionToString(const BLUE_InputAction &value) const {
        for (const auto &n : stringActionPairs) {
            if (n.second == value) {
                return n.first;
            }
        }
        return std::string("Unknown");
    }

    std::string InputManager::hashInputTypeToString(const BLUE_InputType &value) const {
        for (const auto &n : stringInputTypePairs) {
            if (n.second == value) {
                return n.first;
            }
        }
        return std::string("DEFAULT");
    }

    void InputManager::bindKey(BLUE_InputAction action, luabridge::LuaRef &inputTable,
                               std::string value) {

        const luabridge::LuaRef inputRef = inputTable[std::move(value)];

        if (inputRef.isString()) {
            const auto input    = inputRef.cast<std::string>();
            InputMap.at(action) = hashStringToGLFWKey(input);
            // InputMap.insert(std::pair<BLUE_InputAction, int>(action, hashStringToGLFWKey(input)));
        }
    }

    void InputManager::bindKey(BLUE_InputAction action, int key) {
        for (auto &n : InputMap) {
            if (n.second == key) {
                n.second = GLFW_KEY_UNKNOWN;
            }
        }
        InputMap.at(action) = key;
    }

    void InputManager::resetKeyStates() {
        for (auto &n : KeyStates) {
            n = false;
        }
    }

    void InputManager::recordKeyStates(GLEQevent &event) {
        if (event.type == GLEQ_KEY_PRESSED) {
            KeyStates[event.keyboard.key] = true;
        } else if (event.type == GLEQ_KEY_RELEASED) {
            KeyStates[event.keyboard.key] = false;
        }
    }

    const int *InputManager::getKeyStates() const {
        return KeyStates;
    }

    void InputManager::readLuaInputTable(luabridge::LuaRef inputTable) {

        bindKey(BLUE_InputAction::INPUT_JUMP, inputTable, "JUMP");
        bindKey(BLUE_InputAction::INPUT_SPRINT, inputTable, "SPRINT");
        bindKey(BLUE_InputAction::INPUT_MOVE_FORWARD, inputTable, "MOVE_FORWARD");
        bindKey(BLUE_InputAction::INPUT_MOVE_LEFT, inputTable, "MOVE_LEFT");
        bindKey(BLUE_InputAction::INPUT_MOVE_RIGHT, inputTable, "MOVE_RIGHT");
        bindKey(BLUE_InputAction::INPUT_MOVE_BACKWARD, inputTable, "MOVE_BACKWARD");
        bindKey(BLUE_InputAction::INPUT_ACTION_1, inputTable, "ACTION_1");
        bindKey(BLUE_InputAction::INPUT_ACTION_2, inputTable, "ACTION_2");
        bindKey(BLUE_InputAction::INPUT_ACTION_3, inputTable, "ACTION_3");
        bindKey(BLUE_InputAction::INPUT_ACTION_4, inputTable, "ACTION_4");
        bindKey(BLUE_InputAction::INPUT_ESCAPE, inputTable, "ESCAPE");
        bindKey(BLUE_InputAction::INPUT_CROUCH, inputTable, "CROUCH");
        bindKey(BLUE_InputAction::INPUT_SPRINT, inputTable, "SPRINT");
        bindKey(BLUE_InputAction::MOUSE_LEFT, inputTable, "MOUSE_LEFT");
        bindKey(BLUE_InputAction::MOUSE_MIDDLE, inputTable, "MOUSE_MIDDLE");
        bindKey(BLUE_InputAction::MOUSE_RIGHT, inputTable, "MOUSE_RIGHT");
    }

    void InputManager::DefaultInputMap() {
        InputMap.at(BLUE_InputAction::INPUT_JUMP)          = GLFW_KEY_SPACE;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_FORWARD)  = GLFW_KEY_W;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_BACKWARD) = GLFW_KEY_S;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_LEFT)     = GLFW_KEY_A;
        InputMap.at(BLUE_InputAction::INPUT_MOVE_RIGHT)    = GLFW_KEY_D;
        InputMap.at(BLUE_InputAction::INPUT_ACTION_1)      = GLFW_KEY_E;
        InputMap.at(BLUE_InputAction::INPUT_ACTION_2)      = GLFW_KEY_K;
        InputMap.at(BLUE_InputAction::INPUT_ACTION_3)      = GLFW_KEY_M;
        InputMap.at(BLUE_InputAction::INPUT_ACTION_4)      = GLFW_KEY_X;
        InputMap.at(BLUE_InputAction::INPUT_SPRINT)        = GLFW_KEY_LEFT_SHIFT;
        InputMap.at(BLUE_InputAction::INPUT_CROUCH)        = GLFW_KEY_LEFT_CONTROL;
        InputMap.at(BLUE_InputAction::INPUT_ESCAPE)        = GLFW_KEY_ESCAPE;
    }

    std::map<BLUE_InputAction, int> &InputManager::getInputMap() {
        return InputMap;
    }

    void InputManager::createEnumStringPairs() {
        stringScancodePairs.clear();
        stringScancodePairs.emplace_back("1", GLFW_KEY_1);
        stringScancodePairs.emplace_back("2", GLFW_KEY_2);
        stringScancodePairs.emplace_back("3", GLFW_KEY_3);
        stringScancodePairs.emplace_back("4", GLFW_KEY_4);
        stringScancodePairs.emplace_back("5", GLFW_KEY_5);
        stringScancodePairs.emplace_back("6", GLFW_KEY_6);
        stringScancodePairs.emplace_back("7", GLFW_KEY_7);
        stringScancodePairs.emplace_back("8", GLFW_KEY_8);
        stringScancodePairs.emplace_back("9", GLFW_KEY_9);
        stringScancodePairs.emplace_back("0", GLFW_KEY_0);
        stringScancodePairs.emplace_back("A", GLFW_KEY_A);
        stringScancodePairs.emplace_back("B", GLFW_KEY_B);
        stringScancodePairs.emplace_back("C", GLFW_KEY_C);
        stringScancodePairs.emplace_back("D", GLFW_KEY_D);
        stringScancodePairs.emplace_back("E", GLFW_KEY_E);
        stringScancodePairs.emplace_back("F", GLFW_KEY_F);
        stringScancodePairs.emplace_back("G", GLFW_KEY_G);
        stringScancodePairs.emplace_back("H", GLFW_KEY_H);
        stringScancodePairs.emplace_back("I", GLFW_KEY_I);
        stringScancodePairs.emplace_back("J", GLFW_KEY_J);
        stringScancodePairs.emplace_back("K", GLFW_KEY_K);
        stringScancodePairs.emplace_back("L", GLFW_KEY_L);
        stringScancodePairs.emplace_back("M", GLFW_KEY_M);
        stringScancodePairs.emplace_back("N", GLFW_KEY_N);
        stringScancodePairs.emplace_back("O", GLFW_KEY_O);
        stringScancodePairs.emplace_back("P", GLFW_KEY_P);
        stringScancodePairs.emplace_back("Q", GLFW_KEY_Q);
        stringScancodePairs.emplace_back("R", GLFW_KEY_R);
        stringScancodePairs.emplace_back("S", GLFW_KEY_S);
        stringScancodePairs.emplace_back("T", GLFW_KEY_T);
        stringScancodePairs.emplace_back("U", GLFW_KEY_U);
        stringScancodePairs.emplace_back("V", GLFW_KEY_V);
        stringScancodePairs.emplace_back("W", GLFW_KEY_W);
        stringScancodePairs.emplace_back("X", GLFW_KEY_X);
        stringScancodePairs.emplace_back("Y", GLFW_KEY_Y);
        stringScancodePairs.emplace_back("Z", GLFW_KEY_Z);
        stringScancodePairs.emplace_back("Space", GLFW_KEY_SPACE);
        stringScancodePairs.emplace_back("LSHIFT", GLFW_KEY_LEFT_SHIFT);
        stringScancodePairs.emplace_back("LCTRL", GLFW_KEY_LEFT_CONTROL);
        stringScancodePairs.emplace_back("TAB", GLFW_KEY_TAB);
        stringScancodePairs.emplace_back("LALT", GLFW_KEY_LEFT_ALT);
        stringScancodePairs.emplace_back("ESCAPE", GLFW_KEY_ESCAPE);

        stringActionPairs.emplace_back("Move Forward", BLUE_InputAction::INPUT_MOVE_FORWARD);
        stringActionPairs.emplace_back("Move Backward", BLUE_InputAction::INPUT_MOVE_BACKWARD);
        stringActionPairs.emplace_back("Move Left", BLUE_InputAction::INPUT_MOVE_LEFT);
        stringActionPairs.emplace_back("Move Right", BLUE_InputAction::INPUT_MOVE_RIGHT);
        stringActionPairs.emplace_back("Jump", BLUE_InputAction::INPUT_JUMP);
        stringActionPairs.emplace_back("Sprint", BLUE_InputAction::INPUT_SPRINT);
        stringActionPairs.emplace_back("Crouch", BLUE_InputAction::INPUT_CROUCH);
        stringActionPairs.emplace_back("Escape", BLUE_InputAction::INPUT_ESCAPE);
        stringActionPairs.emplace_back("Action 1", BLUE_InputAction::INPUT_ACTION_1);
        stringActionPairs.emplace_back("Action 2", BLUE_InputAction::INPUT_ACTION_2);
        stringActionPairs.emplace_back("Action 3", BLUE_InputAction::INPUT_ACTION_3);
        stringActionPairs.emplace_back("Action 4", BLUE_InputAction::INPUT_ACTION_4);
        stringActionPairs.emplace_back("Mouse Left", BLUE_InputAction::MOUSE_LEFT);
        stringActionPairs.emplace_back("Mouse Middle", BLUE_InputAction::MOUSE_MIDDLE);
        stringActionPairs.emplace_back("Mouse Right", BLUE_InputAction::MOUSE_RIGHT);

        stringInputTypePairs.emplace_back("DEFAULT", BLUE_InputType::DEFAULT_TYPE);
        stringInputTypePairs.emplace_back("KeyPress", BLUE_InputType::KEY_PRESS);
        stringInputTypePairs.emplace_back("KeyRelease", BLUE_InputType::KEY_RELEASE);
        stringInputTypePairs.emplace_back("MouseButtonPress", BLUE_InputType::MOUSE_BUTTONDOWN);
        stringInputTypePairs.emplace_back("MouseButtonRelease", BLUE_InputType::MOUSE_BUTTONUP);
        stringInputTypePairs.emplace_back("MouseMotion", BLUE_InputType::MOUSE_MOTION);
        stringInputTypePairs.emplace_back("MouseWheel", BLUE_InputType::MOUSE_WHEEL);
        stringInputTypePairs.emplace_back("WindowResize", BLUE_InputType::WINDOW_RESIZE);
    }

    const std::vector<std::pair<std::string, int>> &InputManager::getStringScancodePairs() const {
        return stringScancodePairs;
    }

    InputManager::~InputManager() {
    }

    void InputManager::populateInputMap() { // Populates Input map with all actions to allow mapping inputs to them

        InputMap.insert(std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_JUMP, GLFW_KEY_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_MOVE_FORWARD,
                                                         GLFW_KEY_UNKNOWN));
        InputMap.insert(std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_MOVE_BACKWARD,
                                                         GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_MOVE_LEFT, GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_MOVE_RIGHT, GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_SPRINT, GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_CROUCH, GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_ESCAPE, GLFW_KEY_UNKNOWN));

        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_ACTION_1, GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_ACTION_2, GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_ACTION_3, GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_ACTION_4, GLFW_KEY_UNKNOWN));

        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_LOOK_UP, GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_LOOK_DOWN, GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_LOOK_LEFT, GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_LOOK_RIGHT, GLFW_KEY_UNKNOWN));
        InputMap.insert(
            std::pair<BLUE_InputAction, int>(BLUE_InputAction::INPUT_DEFAULT, GLFW_KEY_UNKNOWN));
    }

}
