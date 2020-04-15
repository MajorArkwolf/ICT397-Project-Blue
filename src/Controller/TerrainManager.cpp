#include "TerrainManager.hpp"
#include <cmath>
#include <cstdlib>
#include "Factory/GameAssetFactory.hpp"
Controller::TerrainManager::TerrainManager() {
    id = BlueEngine::IDTracker::getInstance().getID();
}

void Controller::TerrainManager::Init() {
}

void Controller::TerrainManager::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
	for (const auto& e : drawCircle) {
		e->Draw(projection, view, cameraPos);
	}
}

float Controller::TerrainManager::Distance(const Blue::Key &left, const Blue::Key &right) const {
	const auto x_diff = static_cast<float>(left.first - right.first);
	const auto y_diff = static_cast<float>(left.second - right.second);
	return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

void Controller::TerrainManager::GenerateHeightMap(Blue::HeightMap& heightMap) {
    auto& terrainFactory = Controller::Factory::get().terrain;
    heightMap.targetId = this->id;
    heightMap.width = terrainFactory.getWidth();
    heightMap.height = terrainFactory.getHeight();
    heightMap.position.x = static_cast<float>(terrainFactory.getWidth() / 2.0f);
    heightMap.position.z = static_cast<float>(terrainFactory.getHeight() / 2.0f);
    heightMap.rotation = {};
    terrainFactory.ExportHeightMap(heightMap.terrain);
}

void Controller::TerrainManager::Update(glm::ivec2 key) {
    auto &factory = Controller::Factory::get().terrain;
    Blue::Key updateKey{};
	if (key.x < 0) {
		updateKey.first = key.x / factory.GetChunkSize() - 1;
	}
	else {
		updateKey.first = key.x / factory.GetChunkSize();
	}
	if (key.y < 0) {
		updateKey.second = key.y / factory.GetChunkSize() - 1;
	}
	else {
		updateKey.second = key.y / factory.GetChunkSize();
	}
	if (abs(this->lastPos.first - updateKey.first) > reloadDistance || abs(this->lastPos.second - updateKey.second) > reloadDistance ) {
		drawCircle.clear();
		this->lastPos = updateKey;
		int xlow = updateKey.first - radSize;
		int zlow = updateKey.second - radSize;
		int xhigh = updateKey.first + radSize;
		int zhigh = updateKey.second + radSize;
		auto updatedRadSize = static_cast<float>(radSize);

		for (int x = xlow; x <= xhigh; ++x) {
			for (int z = zlow; z <= zhigh; ++z) {
                Blue::Key newKey(x, z);
				if (abs(newKey.first) < maxKey && abs(newKey.second) < maxKey) {
					float distance = Distance(updateKey, newKey);
					if (updatedRadSize >= distance - 0.2f) {
						if (map.find(newKey) == map.end()) {
							map.emplace(newKey, std::make_unique<Model::TerrainModel>());
							auto& e = map.at(newKey);
							factory.GenerateTerrain(*e, newKey);
							drawCircle.push_back(e);
						}
						else {
							drawCircle.push_back(map.at(newKey));
						}
					}
				}
			}
		}
	}
}