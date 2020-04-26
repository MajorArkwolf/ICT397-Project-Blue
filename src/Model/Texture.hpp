#pragma once
#include <string>

#include "glad/glad.h"

class Texture {
  public:
    Texture(GLuint id, int h, int w);
    const GLuint TextureID;
    const int height;
    const int width;
};
