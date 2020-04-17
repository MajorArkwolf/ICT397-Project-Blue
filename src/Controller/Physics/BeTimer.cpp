#include "BeTimer.hpp"

BeTimer::BeTimer(){
    time = nullptr;
}

BeTimer::BeTimer(double timeStep) {
    time = new reactphysics3d::Timer(timeStep);
}

BeTimer::~BeTimer() {
    delete time;
}

reactphysics3d::Timer *BeTimer::GetTime() {
    return time;
}

void BeTimer::Start() {
    time->start();
}

double BeTimer::ComputeFactor() {
    return time->computeInterpolationFactor();
}

void BeTimer::Update() {
    time->update();
}

BeTimer BeTimer::operator=(BeTimer *rhs) {
    time = rhs->time;
    return *this;
}