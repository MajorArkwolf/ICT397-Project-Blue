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
	    /**
	     * Default Constructor
	     */
		Water() = default;
		/**
		 * Default destructor
		 */
		~Water() = default;
		/**
		 * Draw call to renderer the object.
		 * @param projection The projection matrix
		 * @param view The view matrix
		 * @param cameraPos The position of the camera needed for lighting.
		 */
		void Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos);
		/**
		 * Set the shader used for water.
		 * @param newWater water shader.
		 */
		void SetShader(std::shared_ptr<Shader> newWater);
		/**
		 * Sets the texture of the new texture to be used.
		 * @param newTex
		 */
		void SetTexture(unsigned int newTex);
		/**
		 * @brief Sets up the model for opengl.
		 */
        void SetupModel(const std::vector<Blue::Vertex> &vertices,
                        const std::vector<unsigned int> &indices);
        /**
         * Sets the height at which the water is rendered.
         * @param newWaterHeight the height to set the water.
         */
		void SetWaterHeight(float newWaterHeight);
		/// position where to draw the water
		glm::vec3 position = { 0, 105, 0 };

		/**
		 * Adds the water to the draw call.
		 */
		void AddToDraw();

	private:
        /// Shader used to draw the water.
        std::shared_ptr<Shader> shader = nullptr;
        /// Buffer Object ID's
		unsigned int VBO = 0, VAO = 0, EBO = 0, EBO_Size = 0;
        /// Vector of water textures.
        std::vector<unsigned int> textures = {};
        /// Scale of the water model
		glm::vec3 scale{};
		/// Model matrix.
		glm::mat4 model = glm::mat4(1.0f);
	};
}
