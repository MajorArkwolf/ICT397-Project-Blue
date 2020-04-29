#pragma once

namespace Controller::Input {

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

    struct InputData {
        glm::ivec2 mouseMotionRelative = {0, 0};
        glm::ivec2 mouseMotionAbsolute = {0, 0};
        float mouseWheelMotion         = 0.f;
        BLUE_InputAction inputAction = BLUE_InputAction::INPUT_DEFAULT;
        BLUE_InputType inputType = BLUE_InputType::DEFAULT_TYPE;
    };

}