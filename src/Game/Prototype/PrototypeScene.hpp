//
// Created by Arkwolf on 19/12/2019.
//

#ifndef PROJECT_BLUE_PROTOTYPESCENE_HPP
#define PROJECT_BLUE_PROTOTYPESCENE_HPP


#include <Engine/BaseState.hpp>

class PrototypeScene : public BaseState {
    PrototypeScene();
    ~PrototypeScene();

    auto display() -> void;
    auto update(double dt) -> void;

    void hardInit();
    void softInit();
    void handleInput(SDL_Event &event);
};


#endif //PROJECT_BLUE_PROTOTYPESCENE_HPP
