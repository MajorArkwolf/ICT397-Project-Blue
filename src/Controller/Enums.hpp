#pragma once

namespace Controller {

    namespace Input {

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
            MOUSE_BUTTONUP
        };

        enum class BLUE_InputDevice {
            UNKNOWN,
            KEY_0,
            KEY_1,
            KEY_2,
            KEY_3,
            KEY_4,
            KEY_5,
            KEY_6,
            KEY_7,
            KEY_8,
            KEY_9,
            KEY_A,
            KEY_B,
            KEY_C,
            KEY_D,
            KEY_E,
            KEY_F,
            KEY_G,
            KEY_H,
            KEY_I,
            KEY_J,
            KEY_K,
            KEY_L,
            KEY_M,
            KEY_N,
            KEY_O,
            KEY_P,
            KEY_Q,
            KEY_R,
            KEY_S,
            KEY_T,
            KEY_U,
            KEY_V,
            KEY_W,
            KEY_X,
            KEY_Y,
            KEY_Z,
            KEY_LSHIFT,
            KEY_RSHIFT,
            KEY_LCTRL,
            KEY_RCTRL,
            KEY_LALT,
            KEY_RALT,
            KEY_SPACE,
            KEY_UP,
            KEY_DOWN,
            KEY_LEFT,
            KEY_RIGHT,
            KEY_ESCAPE,
            MOUSE_LEFT,
            MOUSE_RIGHT,
            MOUSE_MIDDLE,
            MOUSE_MOVE,
            MOUSE_SCROLL
        };
    }
    enum class MethodResult {
        METHOD_SUCCESS,
        METHOD_FAILURE,
        METHOD_PARTIAL_SUCCESS
    };
}
