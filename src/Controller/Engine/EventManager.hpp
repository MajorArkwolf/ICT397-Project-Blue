#pragma once

#include <GLFW/glfw3.h>
#include <queue>

namespace BlueEngine {
    enum class BE_Event {
        BE_NONE,
        BE_WINDOW_MOVED,
        BE_WINDOW_RESIZED,
        BE_WINDOW_CLOSED,
        BE_WINDOW_REFRESH,
        BE_WINDOW_FOCUSED,
        BE_WINDOW_DEFOCUSED,
        BE_WINDOW_ICONIFIED,
        BE_WINDOW_UNICONIFIED,
        BE_FRAMEBUFFER_RESIZED,
        BE_BUTTON_PRESSED,
        BE_BUTTON_RELEASED,
        BE_CURSOR_MOVED,
        BE_CURSOR_ENTERED,
        BE_CURSOR_LEFT,
        BE_SCROLLED,
        BE_KEY_PRESSED,
        BE_KEY_REPEATED,
        BE_KEY_RELEASED,
        BE_CODEPOINT_INPUT,
        BE_MONITOR_CONNECTED,
        BE_MONITOR_DISCONNECTED,
        BE_FILE_DROPPED,
        BE_JOYSTICK_CONNECTED,
        BE_JOYSTICK_DISCONNECTED,
        BE_WINDOW_MAXIMIZED,
        BE_WINDOW_UNMAXIMIZED,
        BE_WINDOW_SCALE_CHANGED,
    };

    struct BEevent {
        BEtype type;
        union {
            GLFWwindow *window;
            GLFWmonitor *monitor;
            int joystick;
        };
        union {
            struct pos {
                int x;
                int y;
            };
            struct size{
                int width;
                int height;
            };
            struct scroll {
                double x;
                double y;
            };
            struct keyboard {
                int key;
                int scancode;
                int mods;
            };
            struct mouse {
                int button;
                int mods;
            };
            unsigned int codepoint;
            struct file {
                char **paths;
                int count;
            };
            struct scale {
                float x;
                float y;
            };
        };
    };
    class EventManager {
        EventManager() = default;
        ~EventManager() = default;
        std::queue
    };
}