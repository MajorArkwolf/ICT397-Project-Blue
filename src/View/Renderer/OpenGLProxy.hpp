#pragma once

#include <vector>
#include "Model/Models/DataTypes.hpp"
#include "View/Renderer/Shader.hpp"

namespace BlueEngine {
	namespace RenderCode {
        void DrawModel(Shader shader, unsigned int &VAO,
                       const std::vector<TextureB> &textures,
                       const std::vector<unsigned int> &indices);

		void SetupMesh(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO,
                       std::vector<Vertex> &vertices,
                       std::vector<unsigned int> &indices);
		
        unsigned int TextureFromFile(const char *path, const std::string &directory,
                                     bool gamma = false);

        void HardInit(); 
        void ResizeWindow();
        void Display();
        void EndDisplay();
        void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear,
                            GLdouble zFar);
	}
}
