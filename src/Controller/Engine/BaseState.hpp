#pragma once

#include <SDL2/SDL.h>

/**
 * @class BaseState
 * @brief Pure virtual class for a game state
 */
class BaseState {
  public:
    /**
     * @brief Virtual destructor for BaseState
     */
    virtual ~BaseState() = default;

    /// Window width
    int width = 0;
    /// Window height
    int height = 0;
    /// Window aspect ratio
    double ratio = 0;
    /// Whether mouse is set to relative mode (reset to center of window each frame)
    bool relativeMouse = 1;

    /**
     * @brief Virtual hard initialisation function for a gamestate
     * Used to load in memory objects and other things that should only be done once
     */
    virtual void hardInit() = 0;

    /**
     * @brief Virtual soft initialisation function for a gamestate
     * Used seperately from a hard init to reset variables needed for gamestate function
     */
    virtual void softInit() = 0;

    /**
     * @brief Virtual soft initialisation function for a gamestate
     * Used seperately from a hard init to reset variables needed for gamestate function
     */
    virtual void display() = 0;

    /**
     * @brief Virtual uninitialisation function for a gamestate
     * Used to free memory from the gamestate, called right before popping the game stack
     */
    virtual void unInit() = 0;

    /**
     * @brief Virtual function for handling input events encased within an SDL event
     * All input events will be sent to the current gamestate at the top of the stack
     * @param event The SDL event that contains the user input
     */
    virtual void handleInput(SDL_Event &event) = 0;

    /**
     * @brief Virtual update function for updating physics within a gamestate
     * @param dt Delta time since last frame
     */
    virtual void update(double dt) = 0;
};
