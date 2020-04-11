#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <map>
#include <string>
#include <vector>

#define GLEQ_IMPLEMENTATION
#define GLEQ_STATIC
#include "gleq.h"

#include <glm/vec2.hpp>

#include "Controller/Engine/LuaManager.hpp"
#include "Controller/Enums.hpp"

namespace Controller {
    namespace Input {
        /// Struct used to hold all input data required for a scene to handle
        struct InputData {
            glm::ivec2 mouseMotionRelative = {0, 0};
            glm::ivec2 mouseMotionAbsolute = {0, 0};
            float mouseWheelMotion         = 0.f;
            BLUE_InputAction inputAction;
            BLUE_InputType inputType;
        };

        /*
         * @class InputManager
         * @brief Class used to handle all user  inputs received by the
         * application, allows rebindable keys to functions.
         */
        class InputManager {
          public:
            /*
             * @brief Returns the static instance of the InputManager
             * @return The static instance of the InputManager
             */
            static InputManager &getInstance();

            /*
             * @brief Converts an SDL_Event into an InputData struct usable by a scene
             * Chooses which action enum to use based on the mapping contained within InputMap
             * @param event The SDL_Event that is read from in order to map a user input to an actionable event based on the mapping currently set
             * @return An InputData struct containing the information required to act on user input for a scene
             */

            InputData ProcessInput(GLEQevent &event);

            /*
             * @brief Reads the lua script that can be used to map particular keys to particular actions
             */
            void ReadBindings();

            /*
             * @brief Loads the default input mapping standardly used by the developers
             */
            void DefaultInputMap();

            /*
             * @brief Returns a reference to the input map
             * @return A const reference to the input map
             */
            std::map<BLUE_InputAction, int> &getInputMap();

            /*
             * @brief Creates all pairings between strings and sdl scancodes, and strings and input actions
             */
            void createEnumStringPairs();

            /*
             * @brief Gets a const reference to the vector of pairs linking strings to scancodes
             * @return A const reference to the vector of pairs linking strings to scancodes
             */
            const std::vector<std::pair<std::string, int>> &getStringScancodePairs() const;
            /*
             * @brief Hashes an input string to an SDL_Scancode enum
             * @param value  The string to convert to an SDL_Scancode enum if the equivalent exists
             * @return An SDL scancode
             */
            int hashStringToGLFWKey(const std::string &value) const;

            /*
             * @brief Hashes an SDL scancode to a string
             * @param value The SDL Scancode to convert to a string
             * @return A string representing thethe SDL scancode
             */
            std::string hashGLFWKeyToString(const int value) const;

            /*
             * @brief Hashes an input string to an SDL_Scancode enum
             * @param value The string to convert to a BLUE_InputAction of one exists
             * @return The equivalent InputAction
             */
            std::string hashInputActionToString(const BLUE_InputAction &value) const;

            /*
             * @brief Binds an action to a particular key given the action, the
             * lua table to read from, and the text to search for.
             */
            void bindKey(BLUE_InputAction action, int key);

          private:
            /// A map containing key value pairs between a game action and a particular key
            std::map<BLUE_InputAction, int> InputMap;

            /*
             * @brief Reads the lua table containing the input mappings
             * @param inputTable The lua input mapping table to be read
             */
            void readLuaInputTable(luabridge::LuaRef inputTable);

            /*
             * @brief Binds an action to a particular key given the action, the
             * lua table to read from, and the text to search for.
             */
            void bindKey(BLUE_InputAction, luabridge::LuaRef &inputTable, std::string value);

            /*
             * @brief Private default constructor
             */
            InputManager();

            /*
             * @brief Private destructor
             */
            ~InputManager();

            /*
             * @brief Deleted copy constructor
             */
            InputManager(const InputManager &other) = delete;

            /*
             * @brief Deleted assignment operator
             */
            InputManager operator=(InputManager &rhs) = delete;

            /*
             * @brief Populates the InputMap with a complete map of actions
             * linked to an empty key, this is to allow the mappings to be
             * changed on the fly. This should be called any time the map is
             * empty or does not have a full complement of action keys.
             */
            void populateInputMap();

            /// A vector of pairs linking together a string and a GLFW key
            std::vector<std::pair<std::string, int>> stringScancodePairs;
            /// A vector of pairs linking a string and an input action
            std::vector<std::pair<std::string, BLUE_InputAction>> stringActionPairs;
        };
    }
}
