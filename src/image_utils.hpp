#pragma once

#include "glbasimac/glbi_texture.hpp"
#include <map>
#include <string>

using namespace glbasimac;

struct ImageData {
    unsigned char* ptr = nullptr; // point toward the image
    std::string path; // the path we used
    int width = 0; // the width
    int height = 0; // the height
    int channel_number = 0; // the number of channels to describe a pixel
};

// the list of loaded images and textures
extern std::map<std::string, ImageData> loadedImages;
extern std::map<std::string, GLBI_Texture> loadedTextures;

// load an image and keep the pixel data in memory
const ImageData& loadImage(const std::string& path, const std::string& name);

// create an OpenGL texture from a previously loaded image
void createTextureFromImage(const std::string& imageName, const std::string& textureName);

// free all loaded images and textures
void freeAllResources();