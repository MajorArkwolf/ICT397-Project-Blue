#pragma once
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.hpp"
#include "Renderer/shader.hpp"

using std::string;
using std::vector;

unsigned int TextureFromFile(const char *path, const string &directory,
                             bool gamma = false);

class Model {
  public:
    vector<Texture> textures_loaded; // Stores all textures, needs to be global
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    Model(char *path, bool gamma);
    Model(string path, bool gamma);
    void Draw(Shader shader);

  private:
    void loadModel(string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         string typeName);
};

unsigned int TextureFromFile(const char *path, const string &directory,
                             [[maybe_unused]] bool gamma);
