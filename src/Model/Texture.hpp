#pragma once
#include <string>

#include "glad/glad.h"

struct Texture {
    ///Constructor of the texture that takes an id, width, and height
    Texture(GLuint id, int h, int w) : TextureID(id), height(h), width(w){};
    ///The opengl texture id of the texture
    const GLuint TextureID;
    ///The height of the texture
    const int height;
    ///The width of the texture
    const int width;
};
