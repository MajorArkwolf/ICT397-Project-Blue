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
	struct ChunkClod {
	    Model::TerrainModel level1 = {};
	    Model::TerrainModel level2 = {};
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
		 */
		void Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos);
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
		void GenerateHeightMap(Blue::HeightMap& heightMap);

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
        std::vector<std::shared_ptr<ChunkClod>> chunks = {};
        /**
         * @brief Pythagoras function to determine the distance of 2 cartesian coordinates.
         * @param Key of the first square.
         * @param Key of the second square.
         * @return distance between the two keys.
         */
        float Distance(const Blue::Key &left, const Blue::Key &right) const;
    };
}
