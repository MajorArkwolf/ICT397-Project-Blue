#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/matrix4x4.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.hpp"
#include "Model/Models/Animation.hpp"
#include "Model/Models/DataTypes.hpp"
#include "View/Renderer/Shader.hpp"

namespace Model {
    class Model {
      public:
        /// Textures IDs that have been loaded.
        std::vector<TextureB> textures_loaded = {}; // Stores all textures, needs to be global
        /// Meshes of models.
        std::vector<Mesh> meshes = {};
        /// The directory of the model.
        std::string directory = {};
        /// Does the model need gamma correction.
        bool gammaCorrection = {};

        /**
         * Constructor for the model.
         * @param path path to the model
         * @param gamma correction if required.
         */
        Model(char *path, bool gamma);
        /**
         * Constructor for the model.
         * @param path path to the model
         * @param gamma correction if required.
         */
        Model(const std::string& path, bool gamma);

        /**
         * Draw call for the model
         * @param shader used to draw the model.
         */
        void Draw(Shader& shader);

        void Update(float t, float dt);

        /*----------------*/
        unsigned numBones = 0;
        std::vector<BoneInfo> boneInfo;
        std::vector<Animation> animation = {};
        Animation* getAnimation(const std::string& animName);

      public:
        /**
         * Loads a model from file.
         * @param path to the model.
         */
        void loadModel(const std::string &path);
        /**
         * Process Nodes from ASSIMP into the models.
         * @param node of the model.
         * @param scene the model loaded in.
         */
        void processNode(aiNode *node, const aiScene *scene);

        /**
         * Process the mesh of a model.
         * @param mesh of the model.
         * @param scene scene the model loaded in.
         * @return returns the next mesh.
         */
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<TextureB> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                  const std::string& typeName);

        std::map<std::string, unsigned int> boneMapping = {};
        glm::mat4 globalInverseTransform = {};
        void LoadBones(unsigned int MeshIndex, const aiMesh *pMesh);
        void LoadAnimations(const aiScene *scene);
        void LoadJoints(aiMesh* mesh, aiNode* root);
        JointsName rootJoint;
        bool isAnimated = true;
        std::string name = "";
    };
}

