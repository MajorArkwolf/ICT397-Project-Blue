#include "TerrainFactory.hpp"

#include <cassert>
#include <iostream>
#include <map>

#include <glad/glad.h>
#include <glm/gtc/noise.hpp>
#include <glm/gtx/normal.hpp>

#include "Controller/Engine/Engine.hpp"
#include "Controller/Engine/LuaManager.hpp"
#include "Controller/TextureManager.hpp"
#include "GameAssetFactory.hpp"
#include "stb_image.h"

void Controller::TerrainFactory::Init() {
    terrainShader =
        std::make_shared<Shader>("./res/shader/terrain_vert.vs", "./res/shader/terrain_frag.fs");
    waterShader =
        std::make_shared<Shader>("./res/shader/water_vert.vs", "./res/shader/water_frag.fs");

    LoadLua();
    LoadPerlinNoise(perlinPath);
    auto &texManager = ResourceManager::getInstance().GetTextureManager();
    snowTextureID    = texManager.getTexture("snow").TextureID;
    grassTextureID   = texManager.getTexture("grass").TextureID;
    dirtTextureID    = texManager.getTexture("dirt").TextureID;
    sandTextureID    = texManager.getTexture("sand").TextureID;
    waterTextureID   = texManager.getTexture("water").TextureID;

    if (this->width > this->height) {
        maxKeySize = ((width / 2) / ChunkSize) - 1;
    } else {
        maxKeySize = ((height / 2) / ChunkSize) - 1;
    }
    AddWallBoundary();
    GenerateHeightOffSet();

    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .beginNamespace("TerrainFactory")
        .addProperty("chunkSize", &Controller::TerrainFactory::LuaMapSize)
        .addFunction("heightAt", &Controller::TerrainFactory::LuaBLHeight)
        .endNamespace();
}

void Controller::TerrainFactory::AddWallBoundary() {
    size_t maxXSize = fValues.size();
    size_t maxZSize = fValues.at(0).size();
    auto playArea   = maxKeySize * static_cast<unsigned>(ChunkSize) * 2;
    auto depth      = (maxXSize - playArea) / 2;
    // South
    for (auto &x : fValues) {
        auto newheight = 300.f;
        for (size_t y = 0; y <= 50; ++y) {
            newheight -= 1.0f;
            x.at(depth + y).height = newheight;
        }
    }
    // North
    auto oppDepth = maxXSize - depth;
    for (auto &x : fValues) {
        auto newheight = 300.f;
        for (size_t y = 0; y <= 50; ++y) {
            newheight -= 1.0f;
            x.at(oppDepth - y).height = newheight;
        }
    }

    // East
    for (size_t z = 0; z < maxZSize; ++z) {
        auto newheight = 300.f;
        for (size_t y = 0; y <= 50; ++y) {
            newheight -= 1.0f;
            fValues.at(depth + y).at(z).height = newheight;
        }
        fValues.at(depth).at(z).height = 300.f;
    }

    // West
    for (size_t z = 0; z < maxZSize; ++z) {
        auto newheight = 300.f;
        for (size_t y = 0; y <= 50; ++y) {
            newheight -= 1.0f;
            fValues.at(maxZSize - depth - y).at(z).height = newheight;
        }
        fValues.at(depth).at(z).height = 300.f;
    }
}

void Controller::TerrainFactory::LoadLua() {
    using namespace luabridge;
    auto *L         = LuaManager::getInstance().getLuaState();
    auto &basePath  = BlueEngine::Engine::get().basepath;
    auto scriptPath = basePath + "res/scripts/TerrainConfig.lua";
    if (!luaL_dofile(L, scriptPath.c_str())) {

        std::string heightMapPath;
        std::string grassTextureName;
        std::string snowTextureName;
        std::string dirtTextureName;
        std::string sandTextureName;
        std::string waterTextureName;
        bool generatePerlin   = false;
        size_t chunkSizeValue = {};

        auto heightMap    = getGlobal(L, "HeightMap");
        auto grassTexture = getGlobal(L, "GrassTexture");
        auto snowTexture  = getGlobal(L, "SnowTexture");
        auto dirtTexture  = getGlobal(L, "DirtTexture");
        auto sandTexture  = getGlobal(L, "SandTexture");
        auto waterTexture = getGlobal(L, "WaterTexture");
        auto loadPerlin   = getGlobal(L, "LoadPerlin");
        auto chunkSize    = getGlobal(L, "ChunkSize");

        if (heightMap.isString()) {
            heightMapPath    = heightMap.cast<string>();
            this->perlinPath = basePath + heightMapPath;
        }
        if (grassTexture.isString()) {
            grassTextureName = grassTexture.cast<string>();
        }
        if (snowTexture.isString()) {
            snowTextureName = snowTexture.cast<string>();
        }
        if (dirtTexture.isString()) {
            dirtTextureName = dirtTexture.cast<string>();
        }
        if (sandTexture.isString()) {
            sandTextureName = sandTexture.cast<string>();
        }
        if (waterTexture.isString()) {
            waterTextureName = waterTexture.cast<string>();
        }
        if (loadPerlin.isBool()) {
            generatePerlin = loadPerlin.cast<bool>();
        }
        if (chunkSize.isNumber()) {
            chunkSizeValue = chunkSize.cast<size_t>();
        }
    }
}

void Controller::TerrainFactory::GenerateTerrain(Model::TerrainModel &newTerrain, const Blue::Key &key) {
    unsigned int xsize                 = static_cast<unsigned int>(ChunkSize + 1);
    unsigned int zsize                 = static_cast<unsigned int>(ChunkSize + 1);
    std::vector<Blue::Vertex> vertices = {};
    std::vector<unsigned int> indicies = {};
    /// Pass a shared pointer to our terrain.
    newTerrain.LoadShader(terrainShader);
    newTerrain.water.SetShader(waterShader);
    /// Generate vertices to form a giant square.
    GenerateVertices(vertices, xsize, zsize);
    /// Give heights to the y values using perlin noise.
    AddDetailV2(vertices, key);
    // AddDetail(vertices, key, ChunkSize);
    /// Generate indicies for the vertices.
    GenerateIndices(indicies, xsize, zsize);
    /// Generate the texture coordinates of the squares.
    GenerateTextureCords(vertices);
    /// Generate Soft Normals
    GenerateNormals(vertices, indicies);
    /// Sets the height at which levels the textures will set.
    newTerrain.setHeightOffsets(snowHeight, dirtHeight, grassHeight, sandHeight);
    /// Send the chunk to OpenGL to be stored in the GPU.
    newTerrain.SetupModel(vertices, indicies);
    /// Set the location of the chunk.
    newTerrain.position.x = key.first * ChunkSize;
    newTerrain.position.z = key.second * ChunkSize;
    GenerateWater(newTerrain.water, key, xsize, zsize, 1);
    newTerrain.water.position = glm::vec3{key.first * ChunkSize, waterHeight, key.second * ChunkSize};
    /// Load the textures for the model.
    newTerrain.setTextures(snowTextureID, grassTextureID, dirtTextureID, sandTextureID);
    /// Clean up the useless data to save room in ram.
    CleanupChunk(newTerrain);
}

void Controller::TerrainFactory::GenerateWater(Model::Water &lake, const Blue::Key &key,
                                               unsigned int xsize, unsigned int zsize,
                                               unsigned int increment) {
    std::vector<Blue::Vertex> vertices = {};
    std::vector<unsigned int> indicies = {};
    GenerateVertices(vertices, xsize, zsize, 0, 0, increment);
    auto sizeOfX = static_cast<unsigned int>(glm::sqrt(vertices.size()));
    GenerateIndices(indicies, sizeOfX, sizeOfX);
    GenerateTextureCords(vertices);
    // This is a hack to auto set the water normals to reduce computational time.
    for (auto &v : vertices) {
        v.normals = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    lake.SetTexture(waterTextureID);
    lake.SetupModel(vertices, indicies);
}

void Controller::TerrainFactory::GenerateVertices(std::vector<Blue::Vertex> &terrain,
                                                  unsigned int xsize, unsigned int zsize) {
    GenerateVertices(terrain, xsize, zsize, 0, 0, 1);
}

void Controller::TerrainFactory::GenerateVertices(std::vector<Blue::Vertex> &terrain, unsigned int xsize,
                                                  unsigned int zsize, unsigned int xstart,
                                                  unsigned int zstart, unsigned int increment) {
    Blue::Vertex vertex{};
    for (unsigned i = xstart; i < xsize; i += increment) {
        for (unsigned j = zstart; j < zsize; j += increment) {
            vertex.position.x = i;
            vertex.position.z = j;
            terrain.push_back(vertex);
            vertex = {};
        }
    }
}

void Controller::TerrainFactory::GenerateIndices(std::vector<unsigned int> &terrain,
                                                 unsigned int xsize, unsigned int zsize) {
    for (unsigned int x = 0; x < xsize - 1; ++x) {
        for (unsigned int y = 0; y < zsize - 1; ++y) {
            terrain.push_back((x * zsize + y));             // 0
            terrain.push_back(((x * zsize + 1) + y));       // 1
            terrain.push_back((((x + 1) * zsize) + y));     // 3
            terrain.push_back(((x * zsize + 1) + y));       // 1
            terrain.push_back(((x + 1) * zsize) + (y + 1)); // 2
            terrain.push_back((((x + 1) * zsize) + y));     // 3
        }
    }
}

void Controller::TerrainFactory::GenerateTextureCords(std::vector<Blue::Vertex> &terrain) {
    unsigned int tracker = 0;
    float prevx          = terrain.at(0).position.x;
    int size             = 1;
    int x                = 0;
    int y                = 0;
    for (auto &vert : terrain) {
        if (static_cast<int>(prevx) != static_cast<int>(vert.position.x)) {
            x++;
            y     = 0;
            prevx = vert.position.x;
        }
        if (tracker == 0) {
            vert.texCoords.x = static_cast<float>(x) / static_cast<float>(size);
            vert.texCoords.y = static_cast<float>(y) / static_cast<float>(size);
            tracker++;
        } else {
            vert.texCoords.x = static_cast<float>(x) / static_cast<float>(size);
            vert.texCoords.y = static_cast<float>(y) / static_cast<float>(size);
            tracker          = 0;
        }
        y++;
    }
}

void Controller::TerrainFactory::GeneratePerlinNoise(int xsize, int zsize) {
    fValues.resize(static_cast<size_t>(xsize));
    float xFactor = 1.0f / (xsize - 1);
    float yFactor = 1.0f / (zsize - 1);
    float a       = 5;
    float b       = 0.5;

    for (int row = 0; row < zsize; row++) {
        for (int col = 0; col < xsize; col++) {
            float x     = xFactor * col;
            float y     = yFactor * row;
            float sum   = 0.0f;
            float freq  = a;
            float scale = b;

            // Compute the sum for each octave
            for (int oct = 0; oct < 1; oct++) {
                glm::vec2 p(x * freq, y * freq);
                float val = glm::perlin(p) / scale;
                sum += val;
                float result = (sum + 1.0f) / 2.0f;
                fValues.at(static_cast<size_t>(row)).at(static_cast<size_t>(col)).height =
                    result * 255.0f;
                freq *= 2.0f; // Double the frequency
                scale *= b;   // Next power of b
            }
        }
    }
}

void Controller::TerrainFactory::AddDetail(std::vector<Blue::Vertex> &terrain, const Blue::Key &key,
                                           const int chunkSize) {
    int row = (height / 2) + key.first * chunkSize;
    int col = (width / 2) + key.second * chunkSize;
    auto y  = col;
    float x = -1;
    for (auto &e : terrain) {
        if (x != e.position.x) {
            y = col;
            ++row;
            x = e.position.x;
        }
        e.position.y = fValues.at(static_cast<size_t>(row)).at(static_cast<size_t>(y)).height;
        ++y;
    }
}

void Controller::TerrainFactory::CleanupChunk(Model::TerrainModel &terrain) {
    // terrain.vertices.clear();
    // terrain.vertices.shrink_to_fit();
    // terrain.water.vertices.clear();
    // terrain.water.vertices.shrink_to_fit();
    // terrain.indicies.clear();
    // terrain.indicies.shrink_to_fit();
}

void Controller::TerrainFactory::LoadPerlinNoise(const string &filename) {
    int nrComponents    = {};
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    assert(data != nullptr);

    fValues.resize(static_cast<size_t>(width));
    for (auto &e : fValues) {
        e.resize(static_cast<size_t>(height));
    }
    for (auto x = 0; x <= height - 1; ++x) {
        for (auto y = 0; y <= width - 1; ++y) {
            this->fValues.at(static_cast<size_t>(x)).at(static_cast<size_t>(y)).height =
                static_cast<float>(data[((x * width) + y) * 3]);
        }
    }
    int runtime = 1;
    for (auto run = 0; run < runtime; ++run) {
        for (auto x = 1; x <= height - 2; ++x) {
            for (auto y = 1; y <= width - 2; ++y) {
                float sum = {};
                sum += this->fValues.at(x).at(y).height;
                sum += this->fValues.at(x - 1).at(y).height;
                sum += this->fValues.at(x + 1).at(y).height;
                sum += this->fValues.at(x).at(y + 1).height;
                sum += this->fValues.at(x).at(y - 1).height;
                sum                              = sum / 5;
                this->fValues.at(x).at(y).height = sum;
            }
        }
    }
    stbi_image_free(data);
}

int Controller::TerrainFactory::GetChunkSize() const {
    return this->ChunkSize;
}

void Controller::TerrainFactory::GenerateNormals(std::vector<Blue::Vertex> &vertices,
                                                 const std::vector<unsigned int> &indices) {
    // append triangle normals to every vertex
    for (size_t index = 0; index < indices.size(); index += 3) {
        Blue::Vertex &vert1 = vertices[indices[index]];
        Blue::Vertex &vert2 = vertices[indices[index + 1]];
        Blue::Vertex &vert3 = vertices[indices[index + 2]];
        // glm::triangleNormal() probably returns normalized vector,
        // which is better to compute unnormalized
        glm::vec3 triNormal = glm::triangleNormal(vert1.position, vert2.position, vert3.position);
        vert1.normals += triNormal;
        vert2.normals += triNormal;
        vert3.normals += triNormal;
    }

    // normalize normal vectors
    for (size_t vert = 0; vert < vertices.size(); ++vert) {
        Blue::Vertex &vertBlue = vertices[vert];
        vertBlue.normals       = glm::normalize(vertBlue.normals);
    }
}

int Controller::TerrainFactory::getWidth() const {
    return width;
}

int Controller::TerrainFactory::getHeight() const {
    return height;
}

float *Controller::TerrainFactory::ExportHeightMap() {
    size_t maxIndex = (width) * (height);
    auto *heightMap = new float[maxIndex];
    size_t count    = 0;
    for (auto &x : fValues) {
        for (auto y = height - 1; y >= 0; --y) {
            if (count < maxIndex) {
                heightMap[count] = x.at(y).height;
                ++count;
            } else {
                std::cerr << "ERROR: TerrainFactory::ExportHeightMap out of bounds!\n";
            }
        }
    }
    assert(count == maxIndex);
    return heightMap;
}

void Controller::TerrainFactory::GenerateTerrainL2(Model::TerrainModel &newTerrain,
                                                   const Blue::Key &key) {
    unsigned int xsize                 = static_cast<unsigned int>(ChunkSize + 1);
    unsigned int zsize                 = xsize;
    std::vector<Blue::Vertex> vertices = {};
    std::vector<unsigned int> indicies = {};
    /// Set the location of the chunk.
    newTerrain.position.x = key.first * ChunkSize;
    newTerrain.position.z = key.second * ChunkSize;
    /// Pass a shared pointer to our terrain.
    newTerrain.LoadShader(terrainShader);
    newTerrain.water.SetShader(waterShader);
    /// Generate vertices to form a giant square.
    GenerateVertices(vertices, xsize, zsize, 0, 0, 5);
    /// Give heights to the y values using perlin noise.
    AddDetailV2(vertices, key);
    /// Generate indicies for the vertices.
    auto sizeOfX = static_cast<unsigned int>(glm::sqrt(vertices.size()));
    auto sizeOfY = sizeOfX;
    GenerateIndices(indicies, sizeOfX, sizeOfY);
    /// Generate the texture coordinates of the squares.
    GenerateTextureCords(vertices);
    /// Generate Soft Normals
    GenerateNormals(vertices, indicies);
    /// Sets the height at which levels the textures will set.
    // StitchSeemedvertices(newTerrain, key);
    newTerrain.setHeightOffsets(snowHeight, dirtHeight, grassHeight, sandHeight);
    /// Send the chunk to OpenGL to be stored in the GPU.
    newTerrain.SetupModel(vertices, indicies);
    GenerateWater(newTerrain.water, key, xsize, zsize, 5);
    newTerrain.water.position = glm::vec3{key.first * ChunkSize, waterHeight, key.second * ChunkSize};
    /// Load the textures for the model.
    newTerrain.setTextures(snowTextureID, grassTextureID, dirtTextureID, sandTextureID);
    /// Clean up the useless data to save room in ram.
    newTerrain.EBO_Size = indicies.size();
    CleanupChunk(newTerrain);
}

void Controller::TerrainFactory::StitchSeemedVertices(Model::TerrainModel &newTerrain,
                                                      const Blue::Key &key) {
    /// This function is not working as of yet, it is designed to stitch a high quality chunk to a lower quality chunk.
    //    auto length = static_cast<unsigned int>(glm::sqrt(newTerrain.vertices.size()));
    //    auto size = newTerrain.vertices.size();
    //    size_t newSize = size;
    //    //Bottom row, left to right
    //    Blue::Vertex lowVertex = {};
    //    Blue::Vertex highVertex = {};
    //    lowVertex.position.x = 0.0f;
    //    highVertex.position.x = 1.0f;
    //    Blue::Vertex height1 = newTerrain.vertices.at(0);
    //    Blue::Vertex height2 = newTerrain.vertices.at(1);
    //    int count = 0;
    //    size_t oldIndex = 0;
    //    for (unsigned int index = 0; index <= ChunkSize; ++index) {
    //        if (count == 7) {
    //            count = 0;
    //            ++oldIndex;
    //            height1 = newTerrain.vertices.at(oldIndex);
    //            height2 = newTerrain.vertices.at(oldIndex + 1);
    //        }
    //        if (index == 0) {
    //            lowVertex.position.z = static_cast<float>(index);
    //            highVertex.position.z = static_cast<float>(index);
    //            lowVertex.position.y = GetDetailAt(key, lowVertex.position.x, lowVertex.position.z);
    //            highVertex.position.y = GetDetailAt(key, highVertex.position.x, highVertex.position.z);
    //            newTerrain.vertices.push_back(lowVertex);
    //            newTerrain.vertices.push_back(highVertex);
    //            newSize += 2;
    //        } else {
    //            lowVertex.position.z = static_cast<float>(index);
    //            highVertex.position.z = static_cast<float>(index);
    //            lowVertex.position.y = GetDetailAt(key, lowVertex.position.x, lowVertex.position.z);
    //            if (index == ChunkSize) {
    //                highVertex.position.y = GetDetailAt(key, highVertex.position.x, highVertex.position.z);
    //            } else {
    //                highVertex.position = height1.position;
    //            }
    //            newSize += 2;
    //            newTerrain.vertices.push_back(lowVertex);
    //            newTerrain.vertices.push_back(highVertex);
    //            newTerrain.indicies.push_back(newSize - 4);             // 0
    //            newTerrain.indicies.push_back(newSize - 2);       // 1
    //            newTerrain.indicies.push_back(newSize - 3);     // 3
    //            newTerrain.indicies.push_back(newSize - 2);       // 1
    //            newTerrain.indicies.push_back(newSize - 1); // 2
    //            newTerrain.indicies.push_back(newSize - 3);     // 3
    //        }
    //        ++count;
    //    }
    //    //Top row, left to right
    //    height1 = newTerrain.vertices.at(length * (length - 1));
    //    height2 = newTerrain.vertices.at(length * (length - 1) + 1);
    //    lowVertex.position = height1.position;
    //    lowVertex.position.x += 1;
    //    highVertex.position = height2.position;
    //    count = 0;
    //    oldIndex = length * (length - 1);
    //    for (unsigned int index = 0; index <= ChunkSize; ++index) {
    //        if (count == 7) {
    //            count = 0;
    //            ++oldIndex;
    //            height1 = newTerrain.vertices.at(oldIndex);
    //            height2 = newTerrain.vertices.at(oldIndex + 1);
    //        }
    //        if (index == 0) {
    //            lowVertex.position.z = static_cast<float>(index);
    //            highVertex.position.z = static_cast<float>(index);
    //            lowVertex.position.y = GetDetailAt(key, lowVertex.position.x, lowVertex.position.z);
    //            highVertex.position.y = GetDetailAt(key, highVertex.position.x, highVertex.position.z);
    //            newTerrain.vertices.push_back(lowVertex);
    //            newTerrain.vertices.push_back(highVertex);
    //            newSize += 2;
    //        } else {
    //            lowVertex.position.z = static_cast<float>(index);
    //            highVertex.position.z = static_cast<float>(index);
    //            lowVertex.position.y = GetDetailAt(key, lowVertex.position.x, lowVertex.position.z);
    //            if (index == ChunkSize) {
    //                highVertex.position.y = GetDetailAt(key, highVertex.position.x, highVertex.position.z);
    //            } else {
    //                highVertex.position = height1.position;
    //            }
    //            newSize += 2;
    //            newTerrain.vertices.push_back(lowVertex);
    //            newTerrain.vertices.push_back(highVertex);
    //            newTerrain.indicies.push_back(newSize - 4);     // 0
    //            newTerrain.indicies.push_back(newSize - 2);     // 1
    //            newTerrain.indicies.push_back(newSize - 3);     // 3
    //            newTerrain.indicies.push_back(newSize - 2);     // 1
    //            newTerrain.indicies.push_back(newSize - 1);     // 2
    //            newTerrain.indicies.push_back(newSize - 3);     // 3
    //        }
    //        ++count;
    //    }

    //    // Bottom, Left to Right stitch.
    //    for (unsigned int index = 0; index < length - 1; ++index) {
    //        Blue::Vertex first = newTerrain.vertices.at(index);
    //        Blue::Vertex second = newTerrain.vertices.at(index + 1);
    //        auto diff = static_cast<unsigned int>(second.position.z - first.position.z);
    //        for (unsigned i = 1; i < diff; ++i) {
    //            first.position.z += diff * 0.2;
    //            first.position.y = GetDetailAt(key, first.position.x, first.position.z);
    //            newTerrain.vertices.push_back(first);
    //            newTerrain.indicies.push_back(index);
    //            newTerrain.indicies.push_back(length + index);
    //            newTerrain.indicies.push_back(newSize);
    //            ++newSize;
    //        }
    //    }
    //    // Top row, left to right.
    //    for (unsigned int index = length * (length - 1); index < size - 1; ++index) {
    //        Blue::Vertex first = newTerrain.vertices.at(index);
    //        Blue::Vertex second = newTerrain.vertices.at(index + 1);
    //        auto diff = static_cast<unsigned int>(second.position.z - first.position.z);
    //        for (unsigned i = 1; i < diff; ++i) {
    //            first.position.z += diff * 0.2;
    //            first.position.y = GetDetailAt(key, first.position.x, first.position.z);
    //            newTerrain.vertices.push_back(first);
    //            newTerrain.indicies.push_back(index);
    //            newTerrain.indicies.push_back(index - length + 1);
    //            newTerrain.indicies.push_back(newSize);
    //            ++newSize;
    //        }
    //    }
    //
    //    // Left Side, Bottom to top.
    //    for (unsigned int index = 0; index < (size - length); index += length) {
    //        Blue::Vertex first = newTerrain.vertices.at(index);
    //        Blue::Vertex second = newTerrain.vertices.at(index + length);
    //        auto diff = static_cast<unsigned int>(second.position.x) - static_cast<unsigned
    //        int>(first.position.x); for (unsigned i = 1; i < diff; ++i) {
    //            first.position.x += diff * 0.2;
    //            first.position.y = GetDetailAt(key, first.position.x, first.position.z);
    //            newTerrain.vertices.push_back(first);
    //            newTerrain.indicies.push_back(index);
    //            newTerrain.indicies.push_back(index + 1);
    //            newTerrain.indicies.push_back(newSize);
    //            ++newSize;
    //        }
    //    }
    //
    //    // Right Side, Bottom to top.
    //    for (unsigned int index = length - 1; index < size - 1; index += length) {
    //        Blue::Vertex first = newTerrain.vertices.at(index);
    //        Blue::Vertex second = newTerrain.vertices.at(index + length);
    //        auto diff = static_cast<unsigned int>(second.position.x) - static_cast<unsigned
    //        int>(first.position.x); for (unsigned i = 1; i < diff; ++i) {
    //            first.position.x += diff * 0.2;
    //            first.position.y = GetDetailAt(key, first.position.x, first.position.z);
    //            newTerrain.vertices.push_back(first);
    //            newTerrain.indicies.push_back(index);
    //            newTerrain.indicies.push_back(index + length - 1);
    //            newTerrain.indicies.push_back(newSize);
    //            ++newSize;
    //        }
    //    }
}

float Controller::TerrainFactory::GetDetailAt(const Blue::Key &key, const int xcord, const int zcord) {
    float result = {};
    if (abs(key.first) <= maxKeySize && abs(key.second) <= maxKeySize) {
        int x  = (height / 2) + key.first * ChunkSize + xcord;
        int z  = (width / 2) + key.second * ChunkSize + zcord;
        result = fValues.at(static_cast<size_t>(x)).at(static_cast<size_t>(z)).height;
    }
    return result;
}

void Controller::TerrainFactory::AddDetailV2(std::vector<Blue::Vertex> &newTerrain,
                                             const Blue::Key &key) {
    for (auto &vert : newTerrain) {
        vert.position.y =
            GetDetailAt(key, static_cast<int>(vert.position.x), static_cast<int>(vert.position.z));
    }
}

unsigned int Controller::TerrainFactory::getMaxKeySize() const {
    return maxKeySize;
}

float Controller::TerrainFactory::GetBLHeight(Blue::Key currentKey, glm::vec2 currentCord) {
    float result_height = {};
    auto intCord        = glm::ivec2(floor(currentCord.x), floor(currentCord.y));
    auto hBL            = GetDetailAt(currentKey, intCord.x, intCord.y);
    auto hBR            = GetDetailAt(currentKey, intCord.x, intCord.y + 1);
    auto hTL            = GetDetailAt(currentKey, intCord.x + 1, intCord.y);
    auto hTR            = GetDetailAt(currentKey, intCord.x + 1, intCord.y + 1);
    float x             = currentCord.x - floor(currentCord.x);
    float y             = currentCord.y - floor(currentCord.y);

    auto y1       = glm::mix(hBL, hTL, x);
    auto y2       = glm::mix(hBR, hTR, x);
    result_height = glm::mix(y1, y2, y);
    return result_height;
}

Blue::HeightRange Controller::TerrainFactory::GetHeightData() const {
    return heightValues;
}

void Controller::TerrainFactory::GenerateHeightOffSet() {
    float min = fValues.at(0).at(0).height;
    float max = fValues.at(0).at(0).height;
    for (auto &x : fValues) {
        for (auto &y : x) {
            if (y.height > max) {
                max = y.height;
            } else if (y.height < min) {
                min = y.height;
            }
        }
    }
    heightValues.min   = min;
    heightValues.max   = max;
    heightValues.range = (max + min) / 2;
}

void Controller::TerrainFactory::ExportHeightMesh(Blue::SimpleMesh &simpleMesh) {
    std::vector<Blue::Vertex> blueVert = {};
    /// Generate vertices to form a giant square.
    GenerateVertices(blueVert, width + 1, height + 1, 0, 0, 1);
    /// Give heights to the y values using perlin noise.
    size_t count = 0;
    for (auto &x : fValues) {
        for (auto &y : x) {
            simpleMesh.vertex.emplace_back(
                glm::vec3(blueVert.at(count).position.x, y.height, blueVert.at(count).position.z));
            //            simpleMesh.vertex.at(count).x = blueVert.at(count).position.x;
            //            simpleMesh.vertex.at(count).y = y.height;
            //            simpleMesh.vertex.at(count).z = blueVert.at(count).position.z;
            ++count;
        }
    }
    /// Generate indices for the vertices.
    auto sizeOfX = static_cast<unsigned int>(glm::sqrt(blueVert.size()));
    auto sizeOfY = sizeOfX;
    GenerateIndices(simpleMesh.indices, sizeOfX, sizeOfY);
}

std::vector<unsigned int> Controller::TerrainFactory::GetTextureID() const {
    std::vector<unsigned int> textureIDs = {};
    textureIDs.push_back(snowTextureID);
    textureIDs.push_back(grassTextureID);
    textureIDs.push_back(dirtTextureID);
    textureIDs.push_back(sandTextureID);
    textureIDs.push_back(waterTextureID);
    return std::move(textureIDs);
}

std::vector<unsigned int> Controller::TerrainFactory::GetTerrainHeights() const {
    std::vector<unsigned int> terrainHeights = {};
    terrainHeights.push_back(snowHeight);
    terrainHeights.push_back(dirtHeight);
    terrainHeights.push_back(grassHeight);
    terrainHeights.push_back(sandHeight);
    terrainHeights.push_back(waterHeight);
    return std::move(terrainHeights);
}

float Controller::TerrainFactory::LuaBLHeight(float x, float y) {
    auto &factory    = Controller::Factory::get().terrain;
    auto ChunkSize   = factory.GetChunkSize();
    auto currentKey  = Blue::Key(floor(x), floor(y));
    auto currentCord = glm::vec2(x, y);
    currentKey.first /= ChunkSize;
    currentKey.second /= ChunkSize;
    if (currentKey.first < 0) {
        currentKey.first -= 1;
    }
    if (currentKey.second < 0) {
        currentKey.second -= 1;
    }
    currentCord.x -= currentKey.first * ChunkSize;
    currentCord.y -= currentKey.second * ChunkSize;
    return factory.GetBLHeight(currentKey, currentCord);
}

int Controller::TerrainFactory::LuaMapSize() {
    return Controller::Factory::get().terrain.getMaxKeySize() *
           Controller::Factory::get().terrain.GetChunkSize();
}