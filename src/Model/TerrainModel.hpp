#pragma once
#include <memory>
#include <vector>

#include <glm/vec3.hpp>

#include "Model/Vertix.hpp"
#include "Model/WaterModel.hpp"
#include "View/Renderer/Shader.hpp"

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
        TerrainModel() = default;
        /**
         * @brief Destructor to free OpenGL memory.
         */
        ~TerrainModel();
        /**
         * @brief Sets up the model for opengl.
         * @param vertices The vertices of the model
         * @param indices The indices of the model
         */
        void SetupModel(const std::vector<Blue::Vertex> &vertices,
                        const std::vector<unsigned int> &indices);
        /**
         * @brief Loads the shader used to draw the terrain.
         * @param newTerrain shared pointer to a shader object
         */
        void LoadShader(std::shared_ptr<Shader> newTerrain);
        /**
         * @brief Set the textures that will be used for the terrain object via id.
         * @param snowTex Snow texture ID
         * @param grassTex Grass texture ID
         * @param dirtTex Dirt texture ID
         * @param sandTex Sand texture ID
         */
        void setTextures(unsigned int &snowTex, unsigned int &grassTex, unsigned int &dirtTex,
                         unsigned int &sandTex);

        /**
         * Adds the model to the drawl call.
         */
        void AddToDraw();
        /**
         * @brief Draw call for the terrain object.
         * @param projection The Projection matrix for the camera
         * @param view The View matrix for the model
         * @param cameraPos The camera position
         */
        void Draw(const glm::mat4 &projection, const glm::mat4 &view, const glm::dvec3 &cameraPos);
        /**
         * Set the height offsets for when each texture is applied and sent to the shader.
         * @param newSnowHeight The height at which the snow trickles off.
         * @param newDirtHeight The height at which the dirt trickles off.
         * @param newGrassHeight The height at which the dirt trickles off.
         * @param newSandHeight The height at which the sand starts.
         */
        void setHeightOffsets(float newSnowHeight, float newDirtHeight, float newGrassHeight,
                              float newSandHeight);
        /// Model scale size
        glm::mat4 model = glm::mat4(1.0f);
        /// The position that the chunk will be drawn at.
        glm::vec3 position = {};
        /// A shared pointer to the shader that will be used.
        std::shared_ptr<Shader> terrainShader = nullptr;
        /// OpenGL index locations
        unsigned int VBO = 0, VAO = 0, EBO = 0, EBO_Size = 0;
        /// Texture ID's
        std::vector<unsigned int> textures = {};
        /// Heights of the various textures
        float snowHeight = 0.0f, dirtHeight = 0.0f, grassHeight = 0.0f, sandHeight = 0.0f;
        /// Water
        Water water = {};
    };
}