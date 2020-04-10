#pragma once
#include <unordered_map>
#include <map>
#include <glm/vec2.hpp>
#include <functional>
#include "Model/TerrainModel.hpp"
#include "TerrainFactory.hpp"
#include <string>
#include "vertix.hpp"
#include <functional>

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
		 * @param Projection matrix for the camera
		 * @param View matrix for the model
		 */
		void Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos);
		/**
		 * @brief Updatecall for the terrain model objects.
		 * @param the key to where the camera is relative to the chunk its in.
		 */
		void Update(glm::ivec2 key);
	private:
		/// The max size a key can be to stop out of bound checks on the terrain.
		size_t maxKey = 15;
		/// How many chunks are rendered in a circle around a set position. Usually based on the camera.
		int radSize = 99;
		/// How far the character can move inside the play area before a new chunk is laoded.
		int reloadDistance = 1;
		/// The factory object that is used to generate terrain for the manager.
		TerrainFactory factory = {};
		/// The last position the camera was at.
		Key lastPos = Key(999,999);
		/// Draw list of chunks to be sent to the renderer.
		std::vector<std::shared_ptr<Model::TerrainModel>> drawCircle = {};
		/// Unordered map of shared pointers to terrain models for quick access.
		std::unordered_map<Key, std::shared_ptr<Model::TerrainModel>, pair_hash> map = {};
		
		/**
		 * @brief Pythatogrious function to determine the distance of 2 cartesian coordinates.
		 * @param Key of the first square.
		 * @param Key of the second square.
		 * @return distance between the two keys.
		 */
		float Distance(const Key& left, const Key& right) const;
	};
}