#pragma once
#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model/Models/Animation.hpp"
#include "Model/Models/DataTypes.hpp"


namespace Model {
    class Model;
}


namespace Controller {
    class Animator {
      public:
        Animator() = default;
        Animation* loadedAnimation = nullptr;
        std::vector<glm::mat4> Transforms = {};
        Model::Model* animatedModel = nullptr;
        void BoneTransform(double TimeInSeconds);
        void ReadNodeHeirarchy(const double &AnimationTime, const JointsName& jN,
                               const glm::mat4 &ParentTransform);

        glm::vec3 CalcInterpolatedPosition(double AnimationTime, const AnimJointNode *pNodeAnim);
        glm::quat CalcInterpolatedRotation(double AnimationTime, const AnimJointNode *pNodeAnim);
        void LoadAnimation(const std::string& newAnim, bool endWhenCompletedFlag = false);
        void ResetAnimationTime();
        bool IsAnimationedEnded() const;
      private:
        double animationTime = 0.0;
        bool endWhenCompleted = false;
        bool clipEnded = false;
    };
}

