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
    auto textures = factory.GetTextureID();
    snowTextureID = textures.at(0);
    grassTextureID = textures.at(1);
    dirtTextureID = textures.at(2);
    sandTextureID = textures.at(3);
    waterTextureID = textures.at(4);

    auto heights = factory.GetTerrainHeights();
    snowHeight = heights.at(0);
    dirtHeight = heights.at(1);
    grassHeight = heights.at(2);
    sandHeight = heights.at(3);
    waterHeight = heights.at(4);
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
    heightMap.heightRange = terrainFactory.GetHeightData();
    heightMap.position.x = 0;
    heightMap.position.z = 0;
    heightMap.position.y = (heightMap.heightRange.max + heightMap.heightRange.min) / 2;
    heightMap.rotation = glm::angleAxis(glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));
    heightMap.terrain = terrainFactory.ExportHeightMap();
}

void Controller::TerrainManager::Update(glm::ivec2 key) {
    if (updateTerrain) {
        for (auto &c : chunks) {
            c->level1.setTextures(snowTextureID, dirtTextureID, grassTextureID, sandTextureID);
            c->level2.setTextures(snowTextureID, dirtTextureID, grassTextureID, sandTextureID);
            c->level1.setHeightOffsets(snowHeight, dirtHeight, grassHeight, sandHeight);
            c->level2.setHeightOffsets(snowHeight, dirtHeight, grassHeight, sandHeight);
        }
        updateTerrain = false;
    }

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

void Controller::TerrainManager::UpdateInfo() {
    updateTerrain = true;
}

unsigned int Controller::TerrainManager::getSnowTextureId() const {
    return snowTextureID;
}

void Controller::TerrainManager::setSnowTextureId(unsigned int snowTextureId) {
    snowTextureID = snowTextureId;
}

unsigned int Controller::TerrainManager::getGrassTextureId() const {
    return grassTextureID;
}

void Controller::TerrainManager::setGrassTextureId(unsigned int grassTextureId) {
    grassTextureID = grassTextureId;
}

unsigned int Controller::TerrainManager::getDirtTextureId() const {
    return dirtTextureID;
}

void Controller::TerrainManager::setDirtTextureId(unsigned int dirtTextureId) {
    dirtTextureID = dirtTextureId;
}

unsigned int Controller::TerrainManager::getSandTextureId() const {
    return sandTextureID;
}

void Controller::TerrainManager::setSandTextureId(unsigned int sandTextureId) {
    sandTextureID = sandTextureId;
}

unsigned int Controller::TerrainManager::getWaterTextureId() const {
    return waterTextureID;
}

void Controller::TerrainManager::setWaterTextureId(unsigned int waterTextureId) {
    waterTextureID = waterTextureId;
}

float Controller::TerrainManager::getSnowHeight() const {
    return snowHeight;
}

void Controller::TerrainManager::setSnowHeight(float snowHeight) {
    TerrainManager::snowHeight = snowHeight;
}

float Controller::TerrainManager::getDirtHeight() const {
    return dirtHeight;
}

void Controller::TerrainManager::setDirtHeight(float dirtHeight) {
    TerrainManager::dirtHeight = dirtHeight;
}

float Controller::TerrainManager::getGrassHeight() const {
    return grassHeight;
}

void Controller::TerrainManager::setGrassHeight(float grassHeight) {
    TerrainManager::grassHeight = grassHeight;
}

float Controller::TerrainManager::getSandHeight() const {
    return sandHeight;
}

void Controller::TerrainManager::setSandHeight(float sandHeight) {
    TerrainManager::sandHeight = sandHeight;
}

float Controller::TerrainManager::getWaterHeight() const {
    return waterHeight;
}

void Controller::TerrainManager::setWaterHeight(float waterHeight) {
    TerrainManager::waterHeight = waterHeight;
}
