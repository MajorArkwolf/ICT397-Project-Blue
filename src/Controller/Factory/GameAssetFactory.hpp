#pragma once
#include "TerrainFactory.hpp"

    /// Internal Dependencies
#include "Model/GameObject/GameObject.hpp"

namespace Controller {
    class Factory {
      public:
        /**
         * @brief Default move constructor, defaulted
         * @param rhs the factory to be moved in.
         */
        Factory(Factory && rhs)    = default;
        /**
         * @brief Default copy constructor, deleted
         * @param rhs the factory to be moved in.
         */
        Factory(const Factory & rhs) = delete;
        /**
         * @brief Default copy assignment, deleted
         * @param rhs the factory to be moved in.
         * @return LHS value
         */
        Factory &operator=(const Factory & rhs) = delete;
        /**
         * @brief Default move assignment, defaulted
         * @param rhs the factory to be moved in.
         * @return LHS value
         */
        Factory &operator=(Factory && rhs) = default;
        /**
         * @brief Default Destructor.
         */
        ~Factory() = default;
        /**
         * @brief Getter for the singleton of the factory.
         * @return returns the instance to this factory
         */
        static auto get() -> Factory &;

        ///Terrain factory used for generating terrain.
        TerrainFactory terrain = {};

            /*!
             * @brief Parameterised GameObject Factory.
             * @param [in] type A GameObject type identifier for the target factory output.
             * @return A pointer to a newly assigned GameObject, or nullptr on error.
             */
        std::shared_ptr<GameObj_Base> GameObject(GameObjType type);
      private:
        /**
         * @brief Default constructor, privatised due to singleton pattern.
         */
        Factory();
    };
}
