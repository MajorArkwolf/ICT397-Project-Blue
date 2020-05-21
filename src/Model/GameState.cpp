#include "GameState.hpp"

Model::GameState::GameState() {
    //Place all constructors needed in here.
}

Model::GameState Model::GameState::getInstance() {
    static auto instance = GameState{};
    return instance;
}
