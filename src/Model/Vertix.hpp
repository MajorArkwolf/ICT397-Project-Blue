#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <array>
#include <glm/detail/type_quat.hpp>
#include "Controller/Engine/IDTracker.hpp"
#include <vector>

namespace Blue {
    /// Used for chunk loading.
	using Key = std::pair<int, int>;
    /// Used for the terrain model generation.
	struct Vertex {
		glm::vec3 position = {};
		glm::vec2 texCoords = {};
		glm::vec3 normals = {};
	};

	struct Perlin {
		float height = 0;
		glm::vec3 color = {};
	};
    /// Used to transfer information from terrain to react.
    struct HeightRange {
        float min = 0.0f;
        float max = 0.0f;
        float range = 0.0f;
    };

	struct HeightMap {
        glm::vec3 position = {};
        glm::quat rotation = {};
        HeightRange heightRange = {};
        float mass = 1;
        int width = 0;
        int height = 0;
        float *terrain = nullptr;
        BlueEngine::ID targetId = 0;
	};

	struct SimpleMesh {
	    std::vector<glm::vec3> vertex = {};
	    std::vector<unsigned int> indices = {};
	};
}
