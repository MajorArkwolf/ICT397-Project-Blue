#pragma once
#include <glm/vec3.hpp>

#include <vector>
#include <memory>
#include "View/Renderer/Shader.hpp"
#include "Model/Vertix.hpp"
#include "Model/WaterModel.hpp"

namespace Model {
	/**
	 * @class TerrainModel
	 * @brief Used to hold the data structure of the terrain.
	 */
	class TerrainModel {
	public:
		/**
		 * @brief Default constructor.
		 */
		TerrainModel();
		/**
		 * @brief Destructor to free OpenGL memory.
		 */
		~TerrainModel();
		/**
		 * @brief Sets up the model for opengl.
		 */
		void SetupModel();
		/**
		 * @brief Loads the shader used to draw the terrain.
		 * @param shared pointer to a shader object
		 */
		void LoadShader(std::shared_ptr<Shader> newTerrain);
		/**
		 * @brief Set the textures that will be used for the terrain object via id.
		 * @param ID to texture 1
		 * @param ID to texture 2
		 * @param ID to texture 3
		 */
		void setTextures(unsigned int tex1, unsigned int tex2, unsigned int tex3, unsigned int tex4);
		/**
		 * @brief Draw call for the terrain object.
		 * @param Projection matrix for the camera
		 * @param View matrix for the model
		 */
		void Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos);

		void AddToDraw();

        ///Model scale size
		glm::mat4 model = glm::mat4(0.5f);
		///The position that the chunk will be drawn at.
		glm::vec3 position = {};
		///Vector of verticies include positions and texture coordinates.
        std::vector<Blue::Vertex> verticies = {};
		///Vector of indicies.
		std::vector<unsigned int> indicies = {};
		///A shared pointer to the shader that will be used.
		std::shared_ptr<Shader> terrainShader = nullptr;
		/// OpenGL index locations
		unsigned int VBO = 0, VAO = 0, EBO = 0;
		/// Needed for the EBO.
		unsigned int indicie_size = 0;
		/// Texture ID's
		unsigned int textureID = 0, textureID2 = 0, textureID3 = 0, textureID4 = 0;
		/// Water
		Water water = {};

    };
}