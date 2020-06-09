#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <map>
#include <string>
#include <vector>

struct AnimJointNode {
    unsigned numPosKeys = 0;
    unsigned numRotKeys = 0;
    //unsigned numScaleKeys = 0;
    std::vector<std::pair<double, glm::vec3>> posKey = {};
    std::vector<std::pair<double, glm::quat>> rotKey = {};
    //std::vector<std::pair<double, glm::vec3>> scaleKey = {};
};

class Animation {
  public:
    Animation() = default;
    Animation(double newDuration, double TPS);
    Animation(const std::string& newName, double newDuration, double TPS);
    std::map<std::string, AnimJointNode> animMap = {};

    unsigned int FindRotation(double AnimationTime, const AnimJointNode *pNodeAnim);

    unsigned int FindPosition(double AnimationTime, const AnimJointNode *pNodeAnim);

    unsigned int FindScaling(double AnimationTime, const AnimJointNode *pNodeAnim);

    AnimJointNode *FindNodeAnim(const std::string &NodeName);

    double getTicksPerSecond() const;
    double getDuration() const;
    const std::string &getName() const;

  private:
    double ticksPerSecond = 25.0;
    double duration = 0.0;
    std::string name = "";
};
