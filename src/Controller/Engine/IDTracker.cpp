#include "IDTracker.hpp"

BlueEngine::ID BlueEngine::IDTracker::getID() {
    return ++id;
}

BlueEngine::IDTracker &BlueEngine::IDTracker::getInstance() {
    static auto instance = IDTracker{};
    return instance;
}
