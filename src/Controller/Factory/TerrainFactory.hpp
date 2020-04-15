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
		 * @param Reference to the terrain chunk to be modified.
		 * @param They key to where the data will be mapped.
		 */
		void GenerateTerrain(Model::TerrainModel& newTerrain, const Blue::Key key);
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
        /**
         * @brief Lets the factory be populated with LUA information
         */
		void LoadLua();
        /**
         * @brief Getter for width
         * @return the width of the height map
         */
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
        void ExportHeightMap(float *heightMap);

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

        /**
         * @brief Generates verticies for terrains.
         * @param lake reference to the water object.
         * @param key to the chunk.
         */
		void GenerateWater(Model::Water &lake, const Blue::Key key);
		/**
		 * @brief Generates texture coordinates.
		 * @param terrain reference to the terrain object.
		 */
        void GenerateTextureCords(std::vector<Blue::Vertex> &terrain);
		/**
		 * @brief Generates verticies for terrains.
		 * @param terrain reference to the terrain object.
		 * @param xsize The max size across the x plane.
		 * @param zsize The max size across the z plane.
		 */
        void GenerateVerticies(std::vector<Blue::Vertex> &terrain, unsigned int xsize,
                               unsigned int zsize);
		/**
		 * @brief Generates verticies for terrains.
		 * @param reference to the terrain object.
		 * @param key the max size of the chunk.
		 * @param maxSize The size of a chunk.
		 */
        void AddDetail(std::vector<Blue::Vertex> &terrain, Blue::Key key, int chunkSize);
		/**
		 * @brief Generates indicies for terrains.
		 * @param reference to the terrain object.
		 * @param The max size across the x plane.
		 * @param The max size across the z plane.
		 */
		void GenerateIndicies(std::vector<unsigned int>& terrain, unsigned int xsize, unsigned int zsize);
		/**
		 * @brief cleans up the memory of the terrain chunk.
		 * @param terrain reference to the terrain object.
		 */
		void CleanupChunk(Model::TerrainModel& terrain);
		/**
		 * @brief Loads perlin noise into the factory to be used for chunk generation.
		 * @param filename the filename of the image of perlin noise.
		 */
		void LoadPerlinNoise(const string& filename);
        /**
         * @brief Generates soft normals for the terrain
         * @param verticies the verticies to generate from
         * @param indicies the indecies to generate from
         */
        void GenerateNormals(std::vector<Blue::Vertex> &verticies, std::vector<unsigned int> indicies);
	};
}