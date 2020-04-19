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
		void setTextures(unsigned int& snowTex, unsigned int& grasstex, unsigned int& dirtTex, unsigned int& sandTex);

        void AddToDraw();
		/**
		 * @brief Draw call for the terrain object.
		 * @param Projection matrix for the camera
		 * @param View matrix for the model
		 */
		void Draw(glm::mat4 projection, glm::mat4 view, const glm::dvec3& cameraPos);
		/**
		 * Set the height offsets for when each texture is applied and sent to the shader.
		 * @param newSnowHeight The height at which the snow trickles off.
		 * @param newDirtHeight The height at which the dirt trickles off.
		 * @param newGrassHeight The height at which the dirt trickles off.
		 * @param newSandHeight The height at which the sand starts.
		 */
		void setHeightOffsets(float newSnowHeight, float newDirtHeight, float newGrassHeight, float newSandHeight);
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
		unsigned int snowTextureID = 0;
		unsigned int grassTextureID = 0;
		unsigned int dirtTextureID = 0;
		unsigned int sandTextureID = 0;
        float snowHeight = 190.0f, dirtHeight = 170, grassHeight = 150, sandHeight = 130;
		/// Water
		Water water = {};

    };
}