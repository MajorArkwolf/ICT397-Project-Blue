//
// Created by becky on 28/12/2019.
//

#ifndef PROJECT_BLUE_INPUTMANAGER_HPP
#define PROJECT_BLUE_INPUTMANAGER_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>


class InputManager {
  public:
    enum keyStates { Null, Forward, Backward, Left, Right };
    InputManager();
    InputManager(SDL_Window *input_window);
    keyStates KeyBoardHandler(SDL_Event *key);
    glm::vec3 MouseHandler(float magnitude, int x, int y);

  private:
    SDL_Window *game_window;

};

#endif // PROJECT_BLUE_INPUTMANAGER_HPP
