#pragma once

#if defined(__APPLE__)
#    define GL_SILENCE_DEPRECATION
#endif

#include <SDL2/SDL_opengl.h>

#if defined(_WIN32)
#    include <windows.h>
/* windows.h *helpfully* defines a macro for near and far. */
#    undef near
#    undef far
#endif

#if __has_include(<OpenGL/gl.h>)
#    include <OpenGL/glu.h>
#else
#    include <GL/glu.h>
#endif

#if defined(_WIN32)
/* Windows doesn't have the normal BGR. */
#    ifndef GL_BGR
#        define GL_BGR GL_BGR_EXT
#    endif
#endif