#pragma once
#include <utility>
#include <vector>

namespace View {
    class Renderer {
        /**
         * Initialises the renderer.
         */
        virtual void Init() = 0;
        /**
         * The default draw interface.
         */
        virtual void Draw() = 0;
        /**
         * The default de init interface.
         */
        virtual void DeInit() = 0;
        /**
         * The default toggle wire frame interface.
         */
        virtual void ToggleWireFrame() = 0;
    };
}
