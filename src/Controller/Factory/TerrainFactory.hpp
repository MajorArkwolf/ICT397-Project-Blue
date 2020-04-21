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
         * @return Returns the chunksize the factory is set too.
         */
        int GetChunkSize() const;

        void LoadLua();

        int getWidth() const;
        /**
         * @brief Getter for height
         * @return the height of the height map
         */
        int getHeight() const;
        /**
         * @brief Getter for height
         * @param heightMap a float pointer array.
         */
        float * ExportHeightMap();

	private:
		/// Determines how many squares fit into a single chunk
		int ChunkSize = 100;
		/// Sets the max side of the play area
		int maxSize = 0;
		/// Max width of the height map
		int width = 0;
		/// Max height of the height map
        int height = 0;
		/// Heightmap of floats used for terrain.
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
         * @brief Generates verticies for terrains.
         * @param reference to the terrain object.
         * @param The max size across the x plane.
         * @param The max size across the z plane.
         */
        void GenerateVerticies(std::vector<Blue::Vertex> &terrain, unsigned int xsize,
                               unsigned int zsize);
        /**
         * @brief Generates verticies for terrains.
         * @param reference to the terrain object.
         * @param the max size of the chunk.
         * @param The size of a chunk.
         */
        void AddDetail(std::vector<Blue::Vertex> &terrain, const Blue::Key& key, int chunkSize);
        /**
         * @brief Generates indicies for terrains.
         * @param reference to the terrain object.
         * @param The max size across the x plane.
         * @param The max size across the z plane.
         */
        void GenerateIndicies(std::vector<unsigned int> &terrain, unsigned int xsize,
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
         * Generate soft normals for the verticies
         * @param verticies the be soft normales.
         * @param indicies to generate the hard normals
         */
        void GenerateNormals(std::vector<Blue::Vertex> &verticies, std::vector<unsigned int> indicies);
        /**
         * Overloaded function to generate verticies for the terrain.
         * @param terrain The terrain model to add verticies to.
         * @param xsize The max X size of verticies to generate.
         * @param zsize The max Z size of verticies to generate.
         * @param xstart The min X value to start from.
         * @param zstart The min Z value to start from.
         * @param increment The amount to increment each verticie by.
         */
        void
        GenerateVerticies(vector<Blue::Vertex> &terrain, unsigned int xsize, unsigned int zsize, unsigned int xstart,
                          unsigned int zstart, unsigned int increment);

        void StitchSeemedVerticies(Model::TerrainModel &newTerrain, const Blue::Key& key);

        float GetDetailAt(const Blue::Key &key, int xcord, int zcord);

        void AddDetailV2(std::vector<Blue::Vertex> &newTerrain, const Blue::Key& key);
    };
}