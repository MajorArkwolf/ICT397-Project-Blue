#pragma once
#include <memory>

#include "Model/TerrainModel.hpp"
#include "Model/Vertix.hpp"

namespace Controller {
    /**
     * @class TerrainFactory
     * @brief Used to generate terrain objects.
     */
    class TerrainFactory {
      public:
        /**
         * @brief Default constructor.
         */
        TerrainFactory() = default;
        /**
         * @brief Default Destructor.
         */
        ~TerrainFactory() = default;
        /**
         * @brief Initalises the factory for generating terrain.
         */
        void Init();
        /**
         * @brief Generates a single chunk of terrain.
         * @param newTerrain Reference to the terrain chunk to be modified.
         * @param key They key to where the data will be mapped.
         */
        void GenerateTerrain(Model::TerrainModel &newTerrain, const Blue::Key& key);
        /**
         * Generates a lower level terrain chunk
         * @param newTerrain the terrain chunk to be generated.
         * @param key the location of the key.
         */
        void GenerateTerrainL2(Model::TerrainModel &newTerrain, const Blue::Key& key);
        /**
         * @brief Generates a perlin noise map instead of loading one in.
         * @param xsize The size of the X dimensions.
         * @param zsize The size of the Z dimensions.
         * @param key Key at where to generate the chunk.
         */
        void GeneratePerlinNoise(int xsize, int zsize);
        /**
         * @brief Getter for Chunk size.
         * @return Returns the chunk size the factory is set too.
         */
        int GetChunkSize() const;

        /**
         * Loads information in from LUA.
         */
        void LoadLua();

        /**
         * @brief Getter for width
         * @param heightMap a float pointer array.
         */
        int getWidth() const;

        /**
         * @brief Getter for height
         * @return the height of the height map
         */
        int getHeight() const;

        /**
         * Exports the height map
         * @return a pointer to the height map, you must handle the memory that is exported of this function.
         */
        float * ExportHeightMap();

        /**
         * Gets the maximum chunk size in a certain direction.
         * @return the max size.
         */
        unsigned int getMaxKeySize();

        float getHeightAtCord(glm::vec2 currentCord);

        void crashTest(glm::vec2 currentCord);
    /// change this back to private
	public:
		/// Determines how many squares fit into a single chunk
		int ChunkSize = 100;
		/// Sets the max size of the play area
		unsigned int maxKeySize = 0;
		/// Max width of the height map
		int width = 0;
		/// Max height of the height map
        int height = 0;
		/// Height map of floats used for terrain.
		std::vector<std::vector<Blue::Perlin>> fValues = {};
		/// A pointer to the terrain shader.
		std::shared_ptr<Shader> terrainShader = nullptr;
        /// A pointer to the water shader.
        std::shared_ptr<Shader> waterShader = nullptr;
        /// Snow Texture ID
        unsigned int snowTextureID = {};
        /// Grass Texture ID
        unsigned int grassTextureID = {};
        /// Dirt Texture ID
        unsigned int dirtTextureID = {};
        /// Sand Texture ID
        unsigned int sandTextureID = {};
        /// Water Texture ID
        unsigned int waterTextureID = {};
        float snowHeight = 190.0f, dirtHeight = 150.0f, grassHeight = 128.0f, sandHeight = 108.0f, waterHeight = 105.0f;
        ///Perlin Path
        std::string perlinPath = {};

        void GenerateWater(Model::Water &lake, const Blue::Key &key, unsigned int xsize,
                           unsigned int zsize, unsigned int increment);
        /**
         * @brief Generates texture coordinates.
         * @param reference to the terrain object.
         */
        void GenerateTextureCords(std::vector<Blue::Vertex> &terrain);
        /**
         * @brief Generates vertices for terrains.
         * @param reference to the terrain object.
         * @param The max size across the x plane.
         * @param The max size across the z plane.
         */
        void GenerateVertices(std::vector<Blue::Vertex> &terrain, unsigned int xsize,
                               unsigned int zsize);
        /**
         * @brief Generates vertices for terrains.
         * @param reference to the terrain object.
         * @param the max size of the chunk.
         * @param The size of a chunk.
         */
        void AddDetail(std::vector<Blue::Vertex> &terrain, const Blue::Key& key, int chunkSize);
        /**
         * @brief Generates indices for terrains.
         * @param reference to the terrain object.
         * @param The max size across the x plane.
         * @param The max size across the z plane.
         */
        void GenerateIndices(std::vector<unsigned int> &terrain, unsigned int xsize,
                              unsigned int zsize);
        /**
         * @brief cleans up the memory of the terrain chunk.
         * @param reference to the terrain object.
         */
        void CleanupChunk(Model::TerrainModel &terrain);
        /**
         * @brief Loads perlin noise into the factory to be used for chunk generation.
         * @param the filename of the image of perlin noise.
         */
        void LoadPerlinNoise(const string& filename);
        /**
         * Generate soft normals for the vertices
         * @param vertices the be soft normales.
         * @param indices to generate the hard normals
         */
        void GenerateNormals(std::vector<Blue::Vertex> &vertices, std::vector<unsigned int> indices);
        /**
         * Overloaded function to generate vertices for the terrain.
         * @param terrain The terrain model to add vertices to.
         * @param xsize The max X size of vertices to generate.
         * @param zsize The max Z size of vertices to generate.
         * @param xstart The min X value to start from.
         * @param zstart The min Z value to start from.
         * @param increment The amount to increment each verticie by.
         */
        void
        GenerateVertices(vector<Blue::Vertex> &terrain, unsigned int xsize, unsigned int zsize, unsigned int xstart,
                          unsigned int zstart, unsigned int increment);

        /**
         * Stitch a CLOD level 2 to a CLOD level 1
         * @param newTerrain the chunk to stitch
         * @param key the key position it sits on.
         */
        void StitchSeemedVertices(Model::TerrainModel &newTerrain, const Blue::Key& key);

        /**
         * Get the detail at a given coordinate.
         * @param key Key to the chunk.
         * @param xcord the xpos of that chunk.
         * @param zcord the zpos of that chunk.
         * @return the ypos.
         */
        float GetDetailAt(const Blue::Key &key, int xcord, int zcord);

        /**
         * Adds detain to an entire chunk.
         * @param newTerrain chunk.
         * @param key the location of the chunk.
         */
        void AddDetailV2(std::vector<Blue::Vertex> &newTerrain, const Blue::Key& key);
    };
}