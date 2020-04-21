#pragma once
#include "TerrainFactory.hpp"

    /// Internal Dependencies
#include "Model/GameObject/GameObject.hpp"

namespace Controller {
    class Factory {
      public:
        /**
         * @brief Default move constructor, defaulted
         * @param Factory&& the factory to be moved in.
         */
        Factory(Factory &&)    = default;
        /**
         * @brief Default copy constructor, deleted
         * @param Factory&& the factory to be moved in.
         */
        Factory(const Factory &) = delete;
        /**
         * @brief Default copy assignment, deleted
         * @param Factory&& the factory to be moved in.
         * @return LHS value
         */
        Factory &operator=(const Factory &) = delete;
        /**
         * @brief Default move assignment, defaulted
         * @param Factory&& the factory to be moved in.
         * @return LHS value
         */
        Factory &operator=(Factory &&) = default;
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
