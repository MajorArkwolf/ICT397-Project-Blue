#pragma once

namespace Controller {

    namespace Input {

        enum BLUE_Input {
            INPUT_DEFAULT,
            INPUT_JUMP,
            INPUT_MOVE_FORWARD,
            INPUT_MOVE_BACKWARD,
            INPUT_MOVE_LEFT,
            INPUT_MOVE_RIGHT,
            INPUT_LOOK_UP,
            INPUT_LOOK_DOWN,
            INPUT_LOOK_LEFT,
            INPUT_LOOK_RIGHT,
            INPUT_ACTION_1,
            INPUT_ACTION_2,
            INPUT_ACTION_3,
            INPUT_ACTION_4
        };

        enum BLUE_InputType {
            DEFAULT_TYPE,
            KEY_DOWN,
            KEY_RELEASE,
            MOUSE_MOTION,
            MOUSE_WHEEL,
            MOUSE_BUTTONDOWN,
            MOUSE_BUTTONUP
        };
    }
    enum class MethodResult {
        METHOD_SUCCESS,
        METHOD_FAILURE,
        METHOD_PARTIAL_SUCCESS
    };
}
