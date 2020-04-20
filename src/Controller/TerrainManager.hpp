#pragma once
#include <functional>
#include <map>
#include <string>
#include <unordered_map>

#include <glm/vec2.hpp>

#include "Model/TerrainModel.hpp"
#include "Model/Vertix.hpp"
#include <functional>
#include "Controller/Engine/IDTracker.hpp"
#include "Model/Vertix.hpp"

namespace Controller {
	/// Hash function for the key into the map.
	struct pair_hash
	{
		template <class T1, class T2>
		std::size_t operator() (const std::pair<T1, T2>& key) const
		{
			return std::hash<T1>()(key.first) ^ std::hash<T2>()(key.second);
		}
	};
	struct ChunkClod {
	    Model::TerrainModel level1 = {};
	    Model::TerrainModel level2 = {};
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
		 * @brief Initalises the manager for generating terrain.
		 */
		void Init();
		/**
		 * @brief Draw call for the terrain model objects.
		 * @param projection matrix for the camera
		 * @param view matrix for the model
		 */
		void Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos);
		/**
		 * @brief Updatecall for the terrain model objects.
		 * @param key to where the camera is relative to the chunk its in.
		 */
		void Update(glm::ivec2 key);

		void AddToDraw();

        /**
         * @brief GenerateHeightMap to be used for anything that needs the heightmap
         * @param heightMap a struct used to store multiple values.
         */
		void GenerateHeightMap(Blue::HeightMap& heightMap);

		
	private:
	    BlueEngine::ID id = 0;
		/// The max size a key can be to stop out of bound checks on the terrain.
		size_t maxKey = 15;
		/// How many chunks are rendered in a circle around a set position. Usually based on the camera.
		int radSize = 3;
		/// How far the character can move inside the play area before a new chunk is laoded.
		int reloadDistance = 1;
		/// The last position the camera was at.
        Blue::Key lastPos = Blue::Key(999, 999);
        /// Draw list of chunks to be sent to the renderer.
        std::vector<Model::TerrainModel*> drawCircle = {};
        /// Unordered map of shared pointers to terrain models for quick access.
        std::unordered_map<Blue::Key, std::shared_ptr<ChunkClod>, pair_hash> map = {};
        /**
         * @brief Pythagoras function to determine the distance of 2 cartesian coordinates.
         * @param Key of the first square.
         * @param Key of the second square.
         * @return distance between the two keys.
         */
        float Distance(const Blue::Key &left, const Blue::Key &right) const;
    };
}