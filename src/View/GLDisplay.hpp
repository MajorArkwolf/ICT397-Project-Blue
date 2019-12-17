#pragma once

#include <time.h>

#include <SDL2/SDL.h>

#include "Engine/Engine.hpp"

namespace View {

    class GLDisplay {

        int width    = 0;
        int height   = 0;
        double ratio = 0.0;

      public:
        GLDisplay();
        static auto get() -> GLDisplay &;
        auto display() -> void;
        auto update(double dt) -> void;
        auto drawRectangle(float width, float height) -> void;
        
    };

};