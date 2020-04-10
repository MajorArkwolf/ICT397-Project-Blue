#include "TerrainFactory.hpp"
#include <glad/glad.h>
#include <glm/gtc/noise.hpp>
#include <glm/gtx/normal.hpp>
#include <iostream>
#include <map>
#include <cassert>
#include "stb_image.h"
#include "View/Renderer/OpenGLProxy.hpp"


void Controller::TerrainFactory::Init() {
    terrainShader = std::make_shared<Shader>("./res/shader/terrain_vert.vs", "./res/shader/terrain_frag.fs");
    waterShader = std::make_shared<Shader>("./res/shader/water_vert.vs", "./res/shader/water_frag.fs");
    LoadPerlinNoise(".//res//images//test2.jpg");
    snowTextureID = BlueEngine::RenderCode::TextureFromFile("snow.jpg", "./res/images");
    grassTextureID = BlueEngine::RenderCode::TextureFromFile("grass.jpg", "./res/images");
    dirtTextureID  = BlueEngine::RenderCode::TextureFromFile("dirt.jpg", "./res/images");
    sandTextureID  = BlueEngine::RenderCode::TextureFromFile("sand.jpg", "./res/images");
    waterTextureID = BlueEngine::RenderCode::TextureFromFile("water.jpg", "./res/images");
}

void Controller::TerrainFactory::GenerateTerrain(Model::TerrainModel &newTerrain, int xcord,
                                                 int zcord, const Blue::Key key) {

    int xsize = ChunkSize + 1;
    int zsize = ChunkSize + 1;
    ///Pass a shared pointer to our terrain.
    newTerrain.LoadShader(terrainShader);
    newTerrain.water.SetShader(waterShader);
    ///Generate verticies to form a giant square.
    GenerateVerticies(newTerrain.verticies, xsize, zsize);
    ///Give heights to the y values using perlin noise.
    AddDetail(newTerrain.verticies, key, maxSize, ChunkSize);
    ///Generate indicies for the verticies.
    GenerateIndicies(newTerrain.indicies, xsize, zsize);
    ///Generate the texture coordinates of the squares.
    GenerateTextureCords(newTerrain.verticies);
    ///Generate Soft Normals
    GenerateNormals(newTerrain.verticies, newTerrain.indicies);
    ///Send the chunk to OpenGL to be stored in the GPU.
    newTerrain.SetupModel();
    ///Set the location of the chunk.
    newTerrain.position.x = xcord * ChunkSize;
    newTerrain.position.z = zcord * ChunkSize;
    GenerateWater(newTerrain.water, xcord, zcord, key);
    newTerrain.water.position = glm::vec3{ xcord * ChunkSize , 105, zcord * ChunkSize };
    ///Load the textures for the model.
    newTerrain.setTextures(snowTextureID, grassTextureID, dirtTextureID, sandTextureID);
    ///Clean up the useless data to save room in ram.
    CleanupChunk(newTerrain);
}

void Controller::TerrainFactory::GenerateWater(Model::Water &lake, int xcord, int zcord,
                                               const Blue::Key key) {
    int xsize = ChunkSize + 1;
    int zsize = ChunkSize + 1;
    GenerateVerticies(lake.verticies, xsize, zsize);
    GenerateIndicies(lake.indicies, xsize, zsize);
    GenerateTextureCords(lake.verticies);
    GenerateNormals(lake.verticies, lake.indicies);
    lake.SetTexture(waterTextureID);
    lake.SetupModel();

}

void Controller::TerrainFactory::GenerateVerticies(std::vector<Blue::Vertex> &terrain,
                                                   unsigned int xsize, unsigned int zsize) {
    Blue::Vertex vertex{};
    for (unsigned i = 0; i < xsize; ++i) {
        for (unsigned j = 0; j < zsize; ++j) {
            vertex.position.x = i;
            vertex.position.z = j;
            terrain.push_back(vertex);
            vertex = {};
        }
    }
}

void Controller::TerrainFactory::GenerateIndicies(std::vector<unsigned int>& terrain, unsigned int xsize, unsigned int zsize) {
    for (unsigned int x = 0; x < xsize - 1; ++x) {
        for (unsigned int y = 0; y < zsize - 1; ++y) {
            terrain.push_back(unsigned int(x * zsize + y)); // 0
            terrain.push_back(unsigned int((x * zsize + 1) + y)); // 1
            terrain.push_back(unsigned int(((x + 1) * zsize) + y)); // 3
            terrain.push_back(unsigned int((x * zsize + 1) + y)); // 1
            terrain.push_back(unsigned int((x + 1) * zsize) + (y + 1)); // 2
            terrain.push_back(unsigned int(((x + 1) * zsize) + y)); // 3
        }
    }
}

void Controller::TerrainFactory::GenerateTextureCords(std::vector<Blue::Vertex> &terrain) {
    unsigned int tracker = 0;
    unsigned int switcher = 0;
    float prevx = 0;
    int size = 1;
    int x = 0; int y = 0;
    prevx = terrain.at(0).position.x;
    for (auto& vert : terrain) {
        if (prevx != vert.position.x) {
            x++;
            y = 0;
            prevx = vert.position.x;
        }
        if (tracker == 0) {
            vert.texCoords.x = static_cast<float>(x) / static_cast<float>(size);
            vert.texCoords.y = static_cast<float>(y) / static_cast<float>(size);
            tracker++;
        }
        else {
            vert.texCoords.x = static_cast<float>(x) / static_cast<float>(size);
            vert.texCoords.y = static_cast<float>(y) / static_cast<float>(size);
            tracker = 0;
        }
        y++;
    }
}

void Controller::TerrainFactory::GeneratePerlinNoise(int xsize, int zsize) {
    fValues.resize(xsize);
    int width = xsize;
    int height = zsize; 
    float xFactor = 1.0f / (width - 1);
    float yFactor = 1.0f / (height - 1);
    float a = 5;
    float b = 0.5;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            float x = xFactor * col;
            float y = yFactor * row;
            float sum = 0.0f;
            float freq = a;
            float scale = b;

            // Compute the sum for each octave
            for (int oct = 0; oct < 1; oct++) {
                glm::vec2 p(x * freq, y * freq);
                float val = glm::perlin(p) / scale;
                sum += val;
                float result = (sum + 1.0f) / 2.0f;
                fValues.at(row).at(col).height = result * 255.0f;
                freq *= 2.0f;   // Double the frequency
                scale *= b;     // Next power of b
            }
        }
    }
}

void Controller::TerrainFactory::AddDetail(std::vector<Blue::Vertex> &terrain, const Blue::Key key,
                                           int maxSize, int chunkSize) {
    int row = (maxSize / 2) + key.first * chunkSize;
    int max_row = row + chunkSize;
    int col = (maxSize / 2) + key.second * chunkSize;
    int max_col = col + chunkSize;
    auto y = col;
    float x = -1;
    for (auto& e : terrain) {
        if (x != e.position.x) {
            y = col;
            ++row;
            x = e.position.x;
        }
        e.position.y = fValues.at(row).at(y).height;
        ++y;
   }
}

void Controller::TerrainFactory::CleanupChunk(Model::TerrainModel& terrain) {
    terrain.verticies.clear();
    terrain.verticies.shrink_to_fit();
    terrain.indicie_size = terrain.indicies.size();
    terrain.indicies.clear();
    terrain.indicies.shrink_to_fit();
}

void Controller::TerrainFactory::LoadPerlinNoise(const string filename) {
    int width, height, nrComponents;
    const unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    assert(data != nullptr, "ERROR: Failed to LoadPerlinNoise from file\n");
    //Verify this frees
    stbi_image_free(0);
    fValues.resize(width + 1);
    for (auto& e : fValues) {
        e.resize(height + 1);
    }
    for (size_t x = 0; x <= height - 1; ++x) {
        for (size_t y = 0; y <= width - 1; ++y) {
            this->fValues.at(x).at(y).height = static_cast<float>(data[((x * width) + y) * 3]);
        }
    }
    int runtime = 1;
    for (size_t run = 0; run < runtime; ++run) {
        for (size_t x = 1; x <= height - 1; ++x) {
            for (size_t y = 1; y <= width - 1; ++y) {
                float sum = {};
                sum += this->fValues.at(x).at(y).height;
                sum += this->fValues.at(x - 1).at(y).height;
                sum += this->fValues.at(x + 1).at(y).height;
                sum += this->fValues.at(x).at(y + 1).height;
                sum += this->fValues.at(x).at(y - 1).height;
                sum = sum / 5;
                this->fValues.at(x).at(y).height = sum;
            }
        }
    }
    
}

int Controller::TerrainFactory::GetChunkSize() const {
    return this->ChunkSize;
}

void Controller::TerrainFactory::GenerateNormals(std::vector<Blue::Vertex> &verticies,
                                                 std::vector<unsigned int> indicies) {
    std::vector<Blue::Faces> faces;
    using Pair = std::pair<unsigned int, size_t>;
    std::multimap<unsigned int, size_t> setFaces;

    for (size_t index = 0; index < indicies.size(); index += 3) {
        faces.push_back(Blue::Faces{});
        auto& face = faces.at(faces.size() - 1);
        face.indicies[0] = indicies.at(index);
        face.indicies[1] = indicies.at(index + 1);
        face.indicies[2] = indicies.at(index + 2);
        face.normal = glm::triangleNormal(verticies.at(face.indicies[0]).position, verticies.at(face.indicies[1]).position, verticies.at(face.indicies[2]).position);
        const auto size = faces.size() - 1;
        setFaces.emplace(face.indicies[0], size);
        setFaces.emplace(face.indicies[1], size);
        setFaces.emplace(face.indicies[2], size);
    }
    
    for (size_t index = 0; index < verticies.size(); ++index) {
        int count = 0;
        auto itr1 = setFaces.lower_bound(index);
        auto itr2 = setFaces.upper_bound(index);
        auto avgNormal = glm::vec3{};
        while (itr1 != itr2) {
            if (itr1->first == index) {
                avgNormal += faces.at(itr1->second).normal;
                ++count;
            }
            ++itr1;
        }
        verticies.at(index).normals = avgNormal / static_cast<float>(count);
    }
}