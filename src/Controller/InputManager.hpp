#pragma once

#define GLFW_INCLUDE_NONE
#include <map>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>

#define GLEQ_IMPLEMENTATION
#define GLEQ_STATIC
#include <glm/vec2.hpp>

#include "Controller/Engine/LuaManager.hpp"
#include "Controller/Enums.hpp"
#include "gleq.h"

namespace Controller::Input {
        /// Struct used to hold all input data required for a scene to handle
        struct InputData {
            glm::ivec2 mouseMotionRelative = {0, 0};
            glm::ivec2 mouseMotionAbsolute = {0, 0};
            float mouseWheelMotion         = 0.f;
            BLUE_InputAction inputAction = {};
            BLUE_InputType inputType = {};
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
             * @brief Converts a GLEQEvent into an InputData struct usable by a scene
             * Chooses which action enum to use based on the mapping contained within InputMap
             * @param event The GLEQEvent that is read from in order to map a user input to an actionable event based on the mapping currently set
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
             * @brief Creates all pairings between strings and GLFW keys, and strings and input actions
             */
            void createEnumStringPairs();

            /*
             * @brief Gets a const reference to the vector of pairs linking strings to scancodes
             * @return A const reference to the vector of pairs linking strings to scancodes
             */
            const std::vector<std::pair<std::string, int>> &getStringScancodePairs() const;
            /*
             * @brief Hashes an input string to a GLFW key
             * @param value  The string to convert to an GLFW int if the equivalent exists
             * @return A GLFW key
             */
            int hashStringToGLFWKey(const std::string &value) const;

            /*
             * @brief Hashes an GLFW key to a string
             * @param value The GLFW key to convert to a string
             * @return A string representing the GLFW key
             */
            std::string hashGLFWKeyToString(int value) const;

            /*
             * @brief Hashes an input string to an GLFW key
             * @param value The string to convert to a BLUE_InputAction of one exists
             * @return The equivalent InputAction
             */
            std::string hashInputActionToString(const BLUE_InputAction &value) const;

            /*
             * @brief Binds an action to a particular key given the action, the
             * lua table to read from, and the text to search for.
             */
            void bindKey(BLUE_InputAction action, int key);

            /*
             * @brief Resets the current key state array
             */
            void resetKeyStates();
            /*
             * @brief Records the keys that have been pressed for a particular frame
             * @param event the GleqEvent to read the key states from
             */
            void recordKeyStates(GLEQevent &event);

            /*
             * @brief Returns the keys that have been pressed for a particular frame
             * @return A pointer to the key states
             */
            const int *getKeyStates();

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

            /// The key states array
            int KeyStates[GLFW_KEY_LAST];
        };
    }
