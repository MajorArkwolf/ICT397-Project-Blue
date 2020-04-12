#pragma once
#include "TerrainFactory.hpp"

namespace Controller {
    class Factory {
      public:
        Factory(Factory &&)    = default;
        Factory(const Factory &) = delete;
        Factory &operator=(const Factory &) = delete;
        Factory &operator=(Factory &&) = default;
        ~Factory() = default;
        static auto get() -> Factory &;
        TerrainFactory terrain = {};
      private:
        Factory();
    };
}