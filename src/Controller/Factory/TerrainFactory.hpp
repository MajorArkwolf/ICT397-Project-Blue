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
		 * @param the x coordinate that will determine where the chunk sits.
		 * @param the z coordinate that will determine where the chunk sits.
		 * @param They key to where the data will be mapped.
		 */
		void GenerateTerrain(Model::TerrainModel& newTerrain, int xcord, int zcord, Blue::Key key);
		/**
		 * @brief Generates a perlin noise map instead of loading one in.
		 * @param xcord The size of the X dimensions.
		 * @param zcord The size of the Z dimensions.
		 * @param key Key at where to generate the chunk.
		 */
		void GeneratePerlinNoise(int xsize, int zsize);
		/**
		 * @brief Getter for Chunk size.
		 * @return Returns the chunksize the factory is set too.
		 */
		int GetChunkSize() const;
        /**
         * @brief Loads LUA variables into be used by the factory for generation.
         */
		void LoadLua();
        /**
         * @brief Allows outside functions to know the max key side to ensure no out of bounds during generation.
         * @return Max key side.
         */
		size_t GetMaxKey();

	private:
	    /// Determines the max height and width
        int width = 0, height = 0;
		/// Determines how many squares fit into a single chunk
		int chunkSize = 100;
		/// Sets the max side of the play area
		int maxSize = 0;
		/// The max an object can travel before it falls out of bounds.
		size_t maxKey = 0;
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

		void GenerateWater(Model::Water &lake, int xcord, int zcord, const Blue::Key key);
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
        void AddDetail(std::vector<Blue::Vertex> &terrain, const Blue::Key key, int maxSize,
                       int chunkSize);
		/**
		 * @brief Generates indicies for terrains.
		 * @param reference to the terrain object.
		 * @param The max size across the x plane.
		 * @param The max size across the z plane.
		 */
		void GenerateIndicies(std::vector<unsigned int>& terrain, unsigned int xsize, unsigned int zsize);
		/**
		 * @brief cleans up the memory of the terrain chunk.
		 * @param reference to the terrain object.
		 */
		void CleanupChunk(Model::TerrainModel& terrain);
		/**
		 * @brief Loads perlin noise into the factory to be used for chunk generation.
		 * @param the filename of the image of perlin noise.
		 */
		void LoadPerlinNoise(const string filename);
        void GenerateNormals(std::vector<Blue::Vertex> &verticies, std::vector<unsigned int> indicies);
        /**
         * @brief Sets the max size based of which is smaller, width or height.
         */
        void SetMaxSize();
        /**
         * @brief Sets the max key size dependent on max size and chunk size.
         */
        void SetMaxKey();
	};
}