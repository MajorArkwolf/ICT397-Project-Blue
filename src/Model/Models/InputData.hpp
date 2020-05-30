#pragma once
#include <string>

#include "glm/vec2.hpp"

namespace Controller::Input {

    ///Enum class used to represent a game action by the user
    enum class BLUE_InputAction {
        INPUT_DEFAULT,
        INPUT_JUMP,
        INPUT_MOVE_FORWARD,
        INPUT_MOVE_BACKWARD,
        INPUT_MOVE_LEFT,
        INPUT_MOVE_RIGHT,
        INPUT_SPRINT,
        INPUT_CROUCH,
        INPUT_LOOK_UP,
        INPUT_LOOK_DOWN,
        INPUT_LOOK_LEFT,
        INPUT_LOOK_RIGHT,
        INPUT_ESCAPE,
        INPUT_ACTION_1,
        INPUT_ACTION_2,
        INPUT_ACTION_3,
        INPUT_ACTION_4
    };

    ///Enum classed used to represent the type of input sent by the user
    enum class BLUE_InputType {
        DEFAULT_TYPE,
        KEY_PRESS,
        KEY_RELEASE,
        MOUSE_MOTION,
        MOUSE_WHEEL,
        MOUSE_BUTTONDOWN,
        MOUSE_BUTTONUP,
        WINDOW_RESIZE
    };

    ///A struct used to store an input event
    struct InputData {
        ///The relative mouse motion in the event
        glm::ivec2 mouseMotionRelative = {0, 0};
        ///The absolute mouse motion in the event
        glm::ivec2 mouseMotionAbsolute = {0, 0};
        ///The amount of mouse wheel motion
        double mouseWheelMotion         = 0.0;
        ///The type of action
        BLUE_InputAction inputAction = BLUE_InputAction::INPUT_DEFAULT;
        ///The action type
        BLUE_InputType inputType = BLUE_InputType::DEFAULT_TYPE;

        std::string actionString = "DEFAULT";
        std::string typeString = "DEFAULT";

    };

}
