#pragma once
#include "TerrainFactory.hpp"

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
      private:
        /**
         * @brief Default constructor, privatised due to singleton pattern.
         */
        Factory();
    };
}
