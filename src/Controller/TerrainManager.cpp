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
    maxKey = factory.getMaxKeySize();
    int mKey = static_cast<int>(maxKey);
    for (int key_x = mKey * -1; key_x < mKey; ++key_x) {
        for (int key_z = mKey * -1; key_z < mKey; ++key_z) {
            auto e = std::make_shared<ChunkClod>();
            e->key = Blue::Key(key_x, key_z);
            factory.GenerateTerrain(e->level1, e->key);
            factory.GenerateTerrainL2(e->level2, e->key);
            chunks.push_back(e);
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
    heightMap.position.x = static_cast<float>(terrainFactory.getWidth() / 2);
    heightMap.position.z = static_cast<float>(terrainFactory.getHeight() / 2);
    heightMap.rotation = {};
    heightMap.terrain = terrainFactory.ExportHeightMap();
}

void Controller::TerrainManager::Update(glm::ivec2 key) {
    auto &factory = Controller::Factory::get().terrain;
    Blue::Key updateKey = GenerateKey(key);
	if (abs(this->lastPos.first - updateKey.first) > reloadDistance || abs(this->lastPos.second - updateKey.second) > reloadDistance ) {
		drawCircle.clear();
		this->lastPos = updateKey;
		auto updatedRadSize = static_cast<float>(radSize);

		for (auto &c : chunks) {
            float distance = Distance(updateKey, c->key);
            if (updatedRadSize >= distance - 0.2f) {
                drawCircle.push_back(&c->level1);
            } else {
                drawCircle.push_back(&c->level2);
            }
		}
	}
}

void Controller::TerrainManager::AddToDraw() {
    for (const auto& e : drawCircle) {
        e->AddToDraw();
    }
}

void Controller::TerrainManager::setCLODLevel(unsigned int newSize) {
    radSize = newSize;
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
    Blue::Key key(currentCord.x / chunkSize, currentCord.y / chunkSize);
    if (currentCord.x < 0) {
        key.first -= 1;
    }
    if (currentCord.y < 0) {
        key.second -= 1;
    }
    return key;
}
