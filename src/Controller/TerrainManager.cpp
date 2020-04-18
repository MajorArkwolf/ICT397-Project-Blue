#include "TerrainManager.hpp"
#include <cmath>
#include <cstdlib>
#include "Factory/GameAssetFactory.hpp"
Controller::TerrainManager::TerrainManager() {

}

void Controller::TerrainManager::Init() {
    Blue::Key updateKey = {};
	updateKey.first = 0;
	updateKey.second = 0;
}

void Controller::TerrainManager::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
	for (const auto& e : drawCircle) {
		e->Draw(projection, view, cameraPos);
	}
}

float Controller::TerrainManager::Distance(const Blue::Key &left, const Blue::Key &right) const {
	const float x_diff = left.first - right.first;
	const float y_diff = left.second - right.second;
	return std::sqrt(x_diff * x_diff + y_diff * y_diff);
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

		for (int x = xlow; x <= xhigh; ++x) {
			for (int z = zlow; z <= zhigh; ++z) {
                Blue::Key newKey(x, z);
				if (abs(newKey.first) < maxKey && abs(newKey.second) < maxKey) {
					float distance = Distance(updateKey, newKey);
					if (radSize >= distance - 0.2f) {
						if (map.find(newKey) == map.end()) {
							map.emplace(newKey, std::make_unique<Model::TerrainModel>());
							auto& e = map.at(newKey);
							factory.GenerateTerrain(*e, newKey.first, newKey.second, newKey);
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

void Controller::TerrainManager::SetTerrainTextures(size_t snow, size_t grass, size_t dirt,
                                                    size_t sand) {
    for (auto &n : map) {
        n.second->setTextures(snow, grass, dirt, sand);
	}
}
