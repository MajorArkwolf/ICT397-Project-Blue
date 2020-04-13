#pragma once
#include <glad/glad.h>
#include "Controller/Engine/Engine.hpp"
#include "View/Renderer/Shader.hpp"
#include "Model/Vertix.hpp"
#include <vector>
#include <memory>

namespace Model {
	class Water {
	public:
		Water();
		~Water() = default;
		void Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos);
		void SetShader(std::shared_ptr<Shader> newWater);
		void SetTexture(unsigned int newTex) { texture1 = newTex; }
		/**
		 * @brief Sets up the model for opengl.
		 */
		void SetupModel();
		glm::vec3 position = { 0, 105, 0 };
        std::vector<Blue::Vertex> verticies = {};
		///Vector of indicies.
		std::vector<unsigned int> indicies = {};
		std::shared_ptr<Shader> shader = nullptr;
	private:
		unsigned int VBO = 0, VAO = 0, EBO = 0;
		unsigned int texture1 = 1, texture2 = 2;
		glm::vec3 scale{};		
		glm::mat4 model = glm::mat4(1.0f);
	};
}