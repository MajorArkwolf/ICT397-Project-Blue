#pragma once

#include <engine/Timer.h>

class BeTimer {
  public:
    BeTimer();
    explicit BeTimer(double timeStep);
    ~BeTimer();
    reactphysics3d::Timer *GetTime();
    void Start();
    double ComputeFactor();
    void Update();
    BeTimer operator=(BeTimer *rhs);

  private:
    reactphysics3d::Timer *time;
};
