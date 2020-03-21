
#include "InputManagerDep.hpp"

InputManager::InputManager() {
    game_window = nullptr;
}

InputManager::InputManager(SDL_Window *input_window) {
    game_window = input_window;
};

InputManager::keyStates InputManager::KeyBoardHandler(SDL_Event *key) {
    keyStates direction = Null;

    switch (key->key.keysym.sym) {
        case SDLK_w:
            direction = Forward;
            std::cout << "direction: " << direction << std::endl;
            break;
        case SDLK_a:
            direction = Left;
            std::cout << "direction: " << direction << std::endl;
            break;
        case SDLK_s:
            direction = Backward;
            std::cout << "direction: " << direction << std::endl;
            break;
        case SDLK_d:
            direction = Right;
            std::cout << "direction: " << direction << std::endl;
            break;
        case SDLK_q:
            SDL_UpdateWindowSurface(game_window);
            SDL_DestroyWindow(game_window);
            SDL_Quit();
            exit(0);
        default: direction = Null; break;
    }

    return direction;
}

glm::vec3 InputManager::MouseHandler(float magnitude, int x, int y) {

    glm::vec3 mouseDelta = glm::vec3(0,0,0);
    int *screenX = new int;
    int *screenY = new int;

    SDL_GetWindowSize(game_window, screenX, screenY);

    int centreX = *screenX / 2;
    int centreY = *screenY / 2;

    glm::vec3 inputVector    = glm::vec3(x, y, 0);

    glm::vec3 centreVector   = glm::vec3(centreX, centreY, 0);

    glm::vec3 rotationVector = inputVector - centreVector;

    glm::vec3 rotationNorm;
    glm::vec3 resultDelta;


    if (abs(glm::length(rotationVector)) < magnitude) {
        resultDelta = glm::vec3(0, 0, 0);
    } else {
        // @see
        // https://books.google.com.au/books?id=RFF0AgAAQBAJ&pg=PA98&lpg=PA98&dq=deadzone+implementation+game+algorithm&source=bl&ots=fZCDZUNrPf&sig=ACfU3U3M4KSKOIelMGPKC9LFrcELk5aZTA&hl=en&sa=X&ved=2ahUKEwja_dnNkZzhAhUIeisKHaaTCzwQ6AEwAXoECAkQAQ#v=onepage&q=deadzone%20implementation%20game%20algorithm&f=false
        // calculate distance and work out the proportion of distance to center
        double percent = ((double)rotationVector.length() - magnitude) /
                         (magnitude + rotationVector.length());

        rotationNorm = glm::normalize(rotationVector);

        mouseDelta = rotationNorm * (float)(percent * 2);

        //resultDelta = glm::normalize(mouseDelta);
        resultDelta = mouseDelta;

        SDL_WarpMouseInWindow(game_window, centreX, centreY);
    }

    return resultDelta;
}
