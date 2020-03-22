#include <cstddef>

#include "Controller/Engine/Engine.hpp"

#if defined(__WINDOWS__)
#define SDL_MAIN_HANDLED
int wmain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    main(argc, argv);
}
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    BlueEngine::Engine::run();

    return EXIT_SUCCESS;
}