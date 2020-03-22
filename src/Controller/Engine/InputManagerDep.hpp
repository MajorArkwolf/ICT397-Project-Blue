#pragma  once
#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>


class InputManager {
  public:

    /**
    *  @brief enum for direction
    *  @param direction the movement in x direction
    *  @param cameraSpeed the speed which the camera moves
    *  @param deltaTime game time elapsed
    *  @param fps frames per second
    *  @return void
    */
    enum keyStates { Null, Forward, Backward, Left, Right };

    /**
    *  @brief default constructor
    *  @param
    *  @return void
    */
    InputManager();

    /**
    *  @brief parameterised constructor
    *  @param input_window SDL window object
    *  @return void
    */
    InputManager(SDL_Window *input_window);

    /**
    *  @brief handles keybaard event
    *  @param key the key pressed
    *  @return keyStates enum for direction
    */
    keyStates KeyBoardHandler(SDL_Event *key);

    /**
    *  @brief handles mouse events
    *  @param magnitude the sensitivity used to detect mouse movement
    *  @param x mouse movement left and right
    *  @param y mosue movement forwards and backwards
    *  @return vector representing degree of rotation
    */
    glm::vec3 MouseHandler(float magnitude, int x, int y);

  private:

    SDL_Window *game_window;

};

