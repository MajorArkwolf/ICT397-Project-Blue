#pragma once
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.hpp"
#include "View/Renderer/Shader.hpp"
namespace Model {
    class Model {
      public:
        std::vector<Texture> textures_loaded; // Stores all textures, needs to be global
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;

        Model(char *path, bool gamma);
        Model(std::string path, bool gamma);
        void Draw(Shader& shader);

      private:
        void loadModel(const std::string &path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                  std::string typeName);
    };
}