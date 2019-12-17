#include "GLDisplay.hpp"

#include <SDL2/SDL.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>

#include "Engine/Engine.hpp"
#include "Engine/OpenGL.hpp"

using View::GLDisplay;

GLDisplay::GLDisplay() {
    auto &engine = SDLEngine::Engine::get();

    SDL_GL_GetDrawableSize(engine.window.get(), &width, &height);
    GLDisplay::ratio = static_cast<double>(width) / static_cast<double>(height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(60, GLDisplay::ratio, 1, 50000);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.f, 0.f, 0.f, 1.f);

    gluLookAt(0.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f);
}

auto GLDisplay::display() -> void {
    auto &engine = SDLEngine::Engine::get();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
    glTranslatef(0.f, 0.f, -10.f);
    drawRectangle(1, 1);
    glPopMatrix();

    glDisable(GL_DEPTH_TEST);
    SDL_GL_SwapWindow(engine.window.get());
}

auto GLDisplay::update(double dt) -> void {
    // dt == delta time
}

auto GLDisplay::get() -> GLDisplay & {
    static auto instance = GLDisplay{};

    return instance;
}

auto GLDisplay::drawRectangle(float width, float height) -> void{
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f * width, 0.5f * height, 0);
    glVertex3f(0.5f * width, 0.5f * height, 0);
    glVertex3f(0.5f * width, -0.5f * height, 0);
    glVertex3f(-0.5f * width, -0.5f * height, 0);
    glEnd();
}