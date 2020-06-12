#include "GameState.hpp"
#include "Controller/Engine/LuaManager.hpp"

int Model::GameState::gameDifficulty() {
    auto df = Model::GameState::getInstance().getDifficulty();
    return static_cast<int>(df);
}

Model::GameState::GameState() {

}

Model::GameState& Model::GameState::getInstance() {
    static auto instance = GameState{};
    return instance;
}
Model::Difficulty Model::GameState::getDifficulty() const {
    return difficulty;
}
void Model::GameState::setDifficulty(Model::Difficulty newDifficulty) {
    difficulty = newDifficulty;
}
