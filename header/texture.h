#pragma once
#include "depedencies.h"
#include "glad/glad.h"
#include <string>


class Texture{
    u32 textureID;
    
public:
    Texture();
    ~Texture();

    void InitializeTextureFromFile(std::string fileName);

    void ActivateTexture(i32 textureUnit);
};