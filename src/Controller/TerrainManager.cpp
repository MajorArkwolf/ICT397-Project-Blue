#include "TerrainManager.hpp"
#include <cmath>
#include <cstdlib>
#include "Factory/GameAssetFactory.hpp"
Controller::TerrainManager::TerrainManager() {
    id = BlueEngine::IDTracker::getInstance().getID();
    Init();
}

void Controller::TerrainManager::Init() {
    auto &factory = Controller::Factory::get().terrain;
    int mKey = static_cast<int>(maxKey);
    for (int key_x = mKey * -1; key_x < mKey; ++key_x) {
        for (int key_z = mKey * -1; key_z < mKey; ++key_z) {
            Blue::Key key = Blue::Key(key_x, key_z);
            map.emplace(key, std::make_shared<ChunkClod>());
            auto&e = map.at(key);
            factory.GenerateTerrain(e->level1, key);
            factory.GenerateTerrainL2(e->level2, key);
        }
    }
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
    heightMap.position.x = (static_cast<float>(terrainFactory.getWidth()) / 2.0f) * -1;
    heightMap.position.z = ((static_cast<float>(terrainFactory.getHeight()) / 2.0f) * -1);
    heightMap.rotation = {};
    heightMap.terrain = terrainFactory.ExportHeightMap();
}

void Controller::TerrainManager::Update(glm::ivec2 key) {
    auto &factory = Controller::Factory::get().terrain;
    Blue::Key updateKey = Blue::Key(key.x / factory.GetChunkSize() - 1, updateKey.second = key.y / factory.GetChunkSize() - 1);
    std::cout << "Key1: " << updateKey.first << "Key2: " << updateKey.second << "\n";
	if (abs(this->lastPos.first - updateKey.first) > reloadDistance || abs(this->lastPos.second - updateKey.second) > reloadDistance ) {
		drawCircle.clear();
		this->lastPos = updateKey;
		auto max = static_cast<int>(maxKey);
        int xlow = -1 * max;
		int zlow = -1 * max;
		int xhigh = max;
		int zhigh = max;
		auto updatedRadSize = static_cast<float>(radSize);

		for (int x = xlow; x <= xhigh; ++x) {
			for (int z = zlow; z <= zhigh; ++z) {
                Blue::Key newKey(x, z);
				if (abs(newKey.first) < maxKey && abs(newKey.second) < maxKey) {
					float distance = Distance(updateKey, newKey);
					if (updatedRadSize >= distance - 0.2f) {
						if (map.find(newKey) == map.end()) {
							map.emplace(newKey, std::make_shared<ChunkClod>());
							auto& e = map.at(newKey);
							factory.GenerateTerrain(e->level1, newKey);
							factory.GenerateTerrainL2(e->level2, newKey);
							drawCircle.push_back(&e->level1);
						}
						else {
							drawCircle.push_back(&map.at(newKey)->level1);
						}
					} else {
                        if(map.find(newKey) != map.end()) {
                            drawCircle.push_back(&map.at(newKey)->level2);
                        }
                    }
				}
			}
		}
	}
}

void Controller::TerrainManager::AddToDraw() {
    for (const auto& e : drawCircle) {
        e->AddToDraw();
    }
}

float Controller::TerrainManager::GetBLHeight(glm::vec2 currentCord) {
    auto &factory = Controller::Factory::get().terrain;
    auto currentKey = GenerateKey(glm::ivec2(floor(currentCord.x), floor(currentCord.y)));
    currentCord.x -= currentKey.first * factory.GetChunkSize();
    currentCord.y -= currentKey.second * factory.GetChunkSize();
    return factory.GetBLHeight(currentKey, currentCord);
}

Blue::Key Controller::TerrainManager::GenerateKey(glm::ivec2 currentCord) {
    auto chunkSize = Controller::Factory::get().terrain.GetChunkSize();
    Blue::Key key = {};
    Blue::Key currentKey(floor(currentCord.x) / chunkSize, floor(currentCord.y) / chunkSize);
    if (currentCord.x < 0) {
        key.first -= 1;
    }
    if (currentCord.y < 0) {
        key.second -= 1;
    }
    return key;
}
