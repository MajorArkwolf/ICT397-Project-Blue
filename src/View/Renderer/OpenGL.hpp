#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Renderer.hpp"
#include "Shader.hpp"
#include "DrawStruct.hpp"
#include "Model/Models/DataTypes.hpp"
#include "Skybox.hpp"
#include "View/EulerCamera.hpp"
#include "Model/Models/Model.hpp"

namespace View {
    class OpenGL: public View::Renderer {
      public:
        OpenGL() = default;
        ~OpenGL() = default;
        void Draw() override;
        void Init() override;
        void DeInit() override;
        void AddToQue(Model::Model& newModel);
        static void SetupMesh(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO,
                       std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
        static void ResizeWindow();
        static unsigned int TextureFromFile(const char *path, const std::string &directory,
                                                   [[maybe_unused]] bool gamma);
        static void DrawModel(Shader& shader, unsigned int &VAO, const std::vector<Texture> &textures,
                              const std::vector<unsigned int> &indices);
        void SetCameraOnRender(Camera &mainCamera);

    private:
        std::vector<Model::Model*> drawQue = {};
        Camera *camera = nullptr;
        std::unique_ptr<Skybox> skyBox = nullptr;
        std::unique_ptr<Shader> shader = nullptr;
    };
}