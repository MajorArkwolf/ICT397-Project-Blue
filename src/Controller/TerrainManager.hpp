#pragma once
#include <functional>
#include <map>
#include <string>
#include <unordered_map>

#include <glm/vec2.hpp>

#include "Controller/Engine/IDTracker.hpp"
#include "Model/TerrainModel.hpp"
#include "Model/Vertix.hpp"

namespace Controller {
    /// Struct used to store the two different levels of detail for a chunk
    struct ChunkClod {
        /// The first level of detail
        Model::TerrainModel level1 = {};
        /// The second level of detail
        Model::TerrainModel level2 = {};
        // The key location of the chunk
        Blue::Key key = {};
    };
    /**
     * @class TerrainManager
     * @brief Uses a fly weight pattern to manage terrain chunks.
     */
    class TerrainManager {
      public:
        /**
         * @brief Default constructor.
         */
        TerrainManager();
        /**
         * @brief Default destructor.
         */
        ~TerrainManager() = default;
        /**
         * @brief Initialises the manager for generating terrain.
         */
        void Init();
        /**
         * @brief Draw call for the terrain model objects.
         * @param projection matrix for the camera
         * @param view matrix for the model
         * @param cameraPos The position of the camera
         */

        void DeInit();

        void Draw(const glm::mat4 &projection, const glm::mat4 &view, const glm::dvec3 &cameraPos);
        /**
         * @brief Update call for the terrain model objects.
         * @param key to where the camera is relative to the chunk its in.
         */
        void Update(glm::ivec2 key);

        /**
         * Iterates all the chunks and adds them to the draw call.
         */
        void AddToDraw();

        /**
         * @brief GenerateHeightMap to be used for anything that needs the heightmap
         * @param heightMap a struct used to store multiple values.
         */
        void GenerateHeightMap(Blue::HeightMap &heightMap);

        /**
         * Sets the radius of where level of detail around the character goes from level 1 to level 2.
         * @param newSize radius of the new circle.
         */
        void setCLODLevel(unsigned int newSize);

        /**
         * Get the height at any point on the terrain.
         * @param currentCord X value and Z value in the world
         * @return Returns the given height on the terrain object.
         */
        float GetBLHeight(glm::vec2 currentCord);

        /**
         * Generates a key from world coordinates. All values need to be rounded down.
         * @param currentCord current X and Z cords.
         * @return returns a key value.
         */
        Blue::Key GenerateKey(glm::ivec2 currentCord);

        /**
         * Tells the terrain manager to update the chunks.
         */
        void UpdateInfo();

      private:
        BlueEngine::ID id = 0;
        /// The max size a key can be to stop out of bound checks on the terrain.
        size_t maxKey = 15;
        /// How many chunks are rendered in a circle around a set position. Usually based on the camera.
        unsigned int radSize = 3;
        /// How far the character can move inside the play area before a new chunk is loaded.
        int reloadDistance = 1;
        /// The last position the camera was at.
        Blue::Key lastPos = Blue::Key(999, 999);
        /// Draw list of chunks to be sent to the renderer.
        std::vector<Model::TerrainModel*> drawCircle = {};
        /// All the chunks in a scene.
        std::vector<std::unique_ptr<ChunkClod>> chunks = {};
        /// Textures used for the chunks.
        unsigned int snowTextureID = {}, grassTextureID = {}, dirtTextureID = {},
                     sandTextureID = {}, waterTextureID = {};

      private:
        /// Height of each element.
        float snowHeight = 190.0f, dirtHeight = 150.0f, grassHeight = 128.0f, sandHeight = 108.0f,
              waterHeight = 105.0f;
        /// Flag to check if values have been updated.
        bool updateTerrain = false;

        /**
         * @brief Pythagoras function to determine the distance of 2 cartesian coordinates.
         * @param Key of the first square.
         * @param Key of the second square.
         * @return distance between the two keys.
         */
        float Distance(const Blue::Key &left, const Blue::Key &right) const;

      public:
        unsigned int getSnowTextureId() const;

        void setSnowTextureId(unsigned int snowTextureId);

        unsigned int getGrassTextureId() const;

        void setGrassTextureId(unsigned int grassTextureId);

        unsigned int getDirtTextureId() const;

        void setDirtTextureId(unsigned int dirtTextureId);

        unsigned int getSandTextureId() const;

        void setSandTextureId(unsigned int sandTextureId);

        unsigned int getWaterTextureId() const;

        void setWaterTextureId(unsigned int waterTextureId);

        float getSnowHeight() const;

        void setSnowHeight(float snowHeight);

        float getDirtHeight() const;

        void setDirtHeight(float dirtHeight);

        float getGrassHeight() const;

        void setGrassHeight(float grassHeight);

        float getSandHeight() const;

        void setSandHeight(float sandHeight);

        float getWaterHeight() const;

        void setWaterHeight(float waterHeight);
    };
}
