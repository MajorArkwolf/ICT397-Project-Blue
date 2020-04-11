#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <array>

namespace Blue {
	using Key = std::pair<int, int>;

	struct Vertex {
		glm::vec3 position = {};
		glm::vec2 texCoords = {};
		glm::vec3 normals = {};
	};

	struct Faces {
		unsigned int indicies[3] = {};
		glm::vec3 normal = {};
	};

	struct Perlin {
		float height = 0;
		glm::vec3 color = {};
	};
}