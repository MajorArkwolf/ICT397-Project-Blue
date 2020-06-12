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
        /**
         * Default constructor
         */
        Animator() = default;
        /// animation that will be played.
        Animation* loadedAnimation = nullptr;
        /// The transforms after they have been updated.
        std::vector<glm::mat4> Transforms = {};
        /// Animated model.
        Model::Model* animatedModel = nullptr;

        /**
         * Function that will update bones based on time.
         * @param TimeInSeconds Delta time variable should be passed in.
         */
        void BoneTransform(double TimeInSeconds);

        /**
         * Find the node that will
         * @param AnimationTime
         * @param jN
         * @param ParentTransform
         */
        void ReadNodeHeirarchy(const double &AnimationTime, const JointsName& jN,
                               const glm::mat4 &ParentTransform);

        /**
         * Calculate the position between two points.
         * @param AnimationTime time passed between key 1 and key 2.
         * @param pNodeAnim next animation.
         * @return the resultant vector.
         */
        glm::vec3 CalcInterpolatedPosition(double AnimationTime, const AnimJointNode *pNodeAnim);

        /**
         * Calculate the position between two points.
         * @param AnimationTime time passed between key 1 and key 2.
         * @param pNodeAnim next animation.
         * @return the resultant quat.
         */
        glm::quat CalcInterpolatedRotation(double AnimationTime, const AnimJointNode *pNodeAnim);

        /**
         * Load animation
         * @param newAnim
         * @param endWhenCompletedFlag
         */
        void LoadAnimation(const std::string& newAnim, bool endWhenCompletedFlag = false);

        /**
         * load the model based of the models id.
         * @param modelID
         */
        void LinkToModel(size_t modelID);

        /**
         * Reset the animation time back to zero.
         */
        void ResetAnimationTime();

        /**
         * Checks to see if an animation has ended
         * @return true if it has
         */
        bool IsAnimationedEnded() const;
      private:
        /// Animation time
        double animationTime = 0.0;
        /// Checks to see if the animation should loop or end
        bool endWhenCompleted = false;
        /// True if the clip has ended.
        bool clipEnded = false;
    };
}

