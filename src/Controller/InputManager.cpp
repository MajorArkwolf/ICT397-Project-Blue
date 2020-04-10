//#include "Controller/InputManager.hpp"
//
//#include <iostream>
//
//#include "Controller/Engine/Engine.hpp"
//
//namespace Controller::Input {
//
//    InputManager &InputManager::getInstance() {
//        static auto instance = InputManager{};
//
//        return instance;
//    }
//
//    InputData InputManager::ProcessInput(SDL_Event &event) {
//        // Handle input data from event
//        InputData inputEvent;
//
//        switch (event.type) {
//            case SDL_KEYDOWN: {
//                inputEvent.inputType = BLUE_InputType::KEY_PRESS;
//            } break;
//            case SDL_KEYUP: {
//                inputEvent.inputType = BLUE_InputType::KEY_RELEASE;
//            } break;
//            case SDL_MOUSEMOTION: {
//                inputEvent.inputType             = BLUE_InputType::MOUSE_MOTION;
//                inputEvent.mouseMotionRelative.x = event.motion.xrel;
//                inputEvent.mouseMotionRelative.y = event.motion.yrel;
//                inputEvent.mouseMotionAbsolute.x = event.motion.x;
//                inputEvent.mouseMotionAbsolute.y = event.motion.y;
//            } break;
//            case SDL_MOUSEBUTTONDOWN: {
//                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONDOWN;
//            } break;
//            case SDL_MOUSEBUTTONUP: {
//                inputEvent.inputType = BLUE_InputType::MOUSE_BUTTONUP;
//            } break;
//            case SDL_MOUSEWHEEL: {
//                inputEvent.inputType        = BLUE_InputType::MOUSE_WHEEL;
//                inputEvent.mouseWheelMotion = event.wheel.y;
//            } break;
//        }
//
//        switch (inputEvent.inputType) {
//            case BLUE_InputType::KEY_PRESS:
//            case BLUE_InputType::KEY_RELEASE: {
//                for (auto &itr : InputMap) {
//                    if (itr.second == event.key.keysym.scancode) {
//                        inputEvent.inputAction = itr.first;
//                    }
//                }
//            } break;
//
//            case BLUE_InputType::MOUSE_BUTTONDOWN:
//            case BLUE_InputType::MOUSE_BUTTONUP: {
//                if (event.button.button == SDL_BUTTON_LEFT) {
//                    inputEvent.inputAction = BLUE_InputAction::INPUT_ACTION_1;
//                } else if (event.button.button == SDL_BUTTON_RIGHT) {
//                    inputEvent.inputAction = BLUE_InputAction::INPUT_ACTION_2;
//                } else if (event.button.button == SDL_BUTTON_MIDDLE) {
//                    inputEvent.inputAction = BLUE_InputAction::INPUT_ACTION_3;
//                }
//            } break;
//            default: {
//
//            } break;
//        }
//
//        return inputEvent;
//    }
//
//    void InputManager::ReadBindings() {
//        std::string basePath = "";
//
//        char *base_path = SDL_GetBasePath();
//        if (base_path) {
//            basePath = std::string(base_path);
//        } else {
//            basePath = SDL_strdup("./");
//        }
//
//        SDL_free(base_path);
//        auto &LuaManager = LuaManager::getInstance();
//
//        auto luaState          = LuaManager.getLuaState();
//        std::string scriptPath = basePath + "scripts//InputBindings.lua";
//        if (luaL_dofile(luaState, scriptPath.c_str())) {
//            std::cout << "No script file found at '" << scriptPath << "', aborting input binding."
//                      << std::endl;
//        }
//        lua_pcall(luaState, 0, 0, 0);
//        luaL_openlibs(luaState);
//        luabridge::LuaRef table = luabridge::getGlobal(luaState, "InputBindings");
//        if (!table.isNil()) {
//            readLuaInputTable(table);
//        }
//    }
//
//    SDL_Scancode InputManager::hashStringToScancode(const std::string &value) const {
//        for (auto &n : stringScancodePairs) {
//            if (n.first == value) {
//                return n.second;
//            }
//        }
//        return SDL_SCANCODE_UNKNOWN;
//    }
//
//    std::string InputManager::hashScancodeToString(const SDL_Scancode &value) const {
//        for (auto &n : stringScancodePairs) {
//            if (n.second == value) {
//                return n.first;
//            }
//        }
//        return std::string("Unknown");
//    }
//
//    std::string InputManager::hashInputActionToString(const BLUE_InputAction &value) const {
//        for (auto &n : stringActionPairs) {
//            if (n.second == value) {
//                return n.first;
//            }
//        }
//        return std::string("Unknown");
//    }
//
//    void InputManager::bindKey(BLUE_InputAction action, luabridge::LuaRef &inputTable,
//                               std::string value) {
//
//        luabridge::LuaRef inputRef = inputTable[value];
//
//        if (inputRef.isString()) {
//            std::string input = inputRef.cast<std::string>();
//            std::cout << input << std::endl;
//            InputMap.insert(
//                std::pair<BLUE_InputAction, SDL_Scancode>(action, hashStringToScancode(input)));
//        }
//    }
//
//    void InputManager::bindKey(BLUE_InputAction action, SDL_Scancode scancode) {
//        for (auto &n : InputMap) {
//            if (n.second == scancode) {
//                n.second = SDL_SCANCODE_UNKNOWN;
//            }
//        }
//        InputMap.at(action) = scancode;
//    }
//
//    void InputManager::readLuaInputTable(luabridge::LuaRef inputTable) {
//
//        bindKey(BLUE_InputAction::INPUT_JUMP, inputTable, "JUMP");
//        bindKey(BLUE_InputAction::INPUT_SPRINT, inputTable, "SPRINT");
//        bindKey(BLUE_InputAction::INPUT_MOVE_FORWARD, inputTable, "MOVE_FORWARD");
//        bindKey(BLUE_InputAction::INPUT_MOVE_LEFT, inputTable, "MOVE_LEFT");
//        bindKey(BLUE_InputAction::INPUT_MOVE_RIGHT, inputTable, "MOVE_RIGHT");
//        bindKey(BLUE_InputAction::INPUT_MOVE_BACKWARD, inputTable, "MOVE_BACKWARD");
//    }
//
//    void InputManager::DefaultInputMap() {
//        InputMap.at(BLUE_InputAction::INPUT_JUMP)          = SDL_SCANCODE_SPACE;
//        InputMap.at(BLUE_InputAction::INPUT_MOVE_FORWARD)  = SDL_SCANCODE_W;
//        InputMap.at(BLUE_InputAction::INPUT_MOVE_BACKWARD) = SDL_SCANCODE_S;
//        InputMap.at(BLUE_InputAction::INPUT_MOVE_LEFT)     = SDL_SCANCODE_A;
//        InputMap.at(BLUE_InputAction::INPUT_MOVE_RIGHT)    = SDL_SCANCODE_D;
//        InputMap.at(BLUE_InputAction::INPUT_ACTION_1)      = SDL_SCANCODE_E;
//        InputMap.at(BLUE_InputAction::INPUT_ACTION_2)      = SDL_SCANCODE_R;
//        InputMap.at(BLUE_InputAction::INPUT_SPRINT)        = SDL_SCANCODE_LSHIFT;
//        InputMap.at(BLUE_InputAction::INPUT_CROUCH)        = SDL_SCANCODE_LCTRL;
//        InputMap.at(BLUE_InputAction::INPUT_ESCAPE)        = SDL_SCANCODE_ESCAPE;
//    }
//
//    std::map<BLUE_InputAction, SDL_Scancode> &InputManager::getInputMap() {
//        return InputMap;
//    }
//
//    void InputManager::createEnumStringPairs() {
//        stringScancodePairs.clear();
//        stringScancodePairs.clear();
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("A", SDL_SCANCODE_A));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("B", SDL_SCANCODE_B));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("C", SDL_SCANCODE_C));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("D", SDL_SCANCODE_D));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("E", SDL_SCANCODE_E));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("F", SDL_SCANCODE_F));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("G", SDL_SCANCODE_G));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("H", SDL_SCANCODE_H));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("I", SDL_SCANCODE_I));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("J", SDL_SCANCODE_J));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("K", SDL_SCANCODE_K));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("L", SDL_SCANCODE_L));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("M", SDL_SCANCODE_M));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("N", SDL_SCANCODE_N));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("O", SDL_SCANCODE_O));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("P", SDL_SCANCODE_P));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("Q", SDL_SCANCODE_Q));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("R", SDL_SCANCODE_R));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("S", SDL_SCANCODE_S));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("T", SDL_SCANCODE_T));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("U", SDL_SCANCODE_U));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("V", SDL_SCANCODE_V));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("W", SDL_SCANCODE_W));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("X", SDL_SCANCODE_X));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("Y", SDL_SCANCODE_Y));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("Z", SDL_SCANCODE_Z));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("Space", SDL_SCANCODE_SPACE));
//        stringScancodePairs.push_back(
//            std::pair<std::string, SDL_Scancode>("LSHIFT", SDL_SCANCODE_LSHIFT));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("LCTRL", SDL_SCANCODE_LCTRL));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("TAB", SDL_SCANCODE_TAB));
//        stringScancodePairs.push_back(std::pair<std::string, SDL_Scancode>("LALT", SDL_SCANCODE_LALT));
//        stringScancodePairs.push_back(
//            std::pair<std::string, SDL_Scancode>("ESCAPE", SDL_SCANCODE_ESCAPE));
//
//        stringActionPairs.push_back(std::pair<std::string, BLUE_InputAction>(
//            "Move Forward", BLUE_InputAction::INPUT_MOVE_FORWARD));
//        stringActionPairs.push_back(std::pair<std::string, BLUE_InputAction>(
//            "Move Backward", BLUE_InputAction::INPUT_MOVE_BACKWARD));
//        stringActionPairs.push_back(
//            std::pair<std::string, BLUE_InputAction>("Move Left", BLUE_InputAction::INPUT_MOVE_LEFT));
//        stringActionPairs.push_back(std::pair<std::string, BLUE_InputAction>(
//            "Move Right", BLUE_InputAction::INPUT_MOVE_RIGHT));
//        stringActionPairs.push_back(
//            std::pair<std::string, BLUE_InputAction>("Jump", BLUE_InputAction::INPUT_JUMP));
//        stringActionPairs.push_back(
//            std::pair<std::string, BLUE_InputAction>("Sprint", BLUE_InputAction::INPUT_SPRINT));
//        stringActionPairs.push_back(
//            std::pair<std::string, BLUE_InputAction>("Crouch", BLUE_InputAction::INPUT_CROUCH));
//        stringActionPairs.push_back(
//            std::pair<std::string, BLUE_InputAction>("Menu", BLUE_InputAction::INPUT_ESCAPE));
//        stringActionPairs.push_back(std::pair<std::string, BLUE_InputAction>(
//            "Move Forward", BLUE_InputAction::INPUT_MOVE_FORWARD));
//        stringActionPairs.push_back(
//            std::pair<std::string, BLUE_InputAction>("Action 1", BLUE_InputAction::INPUT_ACTION_1));
//        stringActionPairs.push_back(
//            std::pair<std::string, BLUE_InputAction>("Action 2", BLUE_InputAction::INPUT_ACTION_2));
//        stringActionPairs.push_back(
//            std::pair<std::string, BLUE_InputAction>("Action 3", BLUE_InputAction::INPUT_ACTION_3));
//        stringActionPairs.push_back(
//            std::pair<std::string, BLUE_InputAction>("Action 4", BLUE_InputAction::INPUT_ACTION_4));
//    }
//
//    const std::vector<std::pair<std::string, SDL_Scancode>> &InputManager::getStringScancodePairs() const {
//        return stringScancodePairs;
//    }
//
//    InputManager::~InputManager() {}
//    void InputManager::populateInputMap() { // Populates Input map with all actions to allow mapping inputs to them
//
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_JUMP,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
//            BLUE_InputAction::INPUT_MOVE_FORWARD, SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(
//            BLUE_InputAction::INPUT_MOVE_BACKWARD, SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_MOVE_LEFT,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_MOVE_RIGHT,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_SPRINT,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_CROUCH,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_ESCAPE,
//                                                                  SDL_SCANCODE_UNKNOWN));
//
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_ACTION_1,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_ACTION_2,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_ACTION_3,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_ACTION_4,
//                                                                  SDL_SCANCODE_UNKNOWN));
//
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_LOOK_UP,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_LOOK_DOWN,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_LOOK_LEFT,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_LOOK_RIGHT,
//                                                                  SDL_SCANCODE_UNKNOWN));
//        InputMap.insert(std::pair<BLUE_InputAction, SDL_Scancode>(BLUE_InputAction::INPUT_DEFAULT,
//                                                                  SDL_SCANCODE_UNKNOWN));
//    }
//
//    InputManager::InputManager() {
//        populateInputMap();
//        DefaultInputMap();
//        createEnumStringPairs();
//    }
//}
