#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"

#include "texture.hpp"
#include "../global/global.hpp" 

using namespace glbasimac;

std::map<std::string, ImageData> loadedImages {};
std::map<std::string, GLBI_Texture> loadedTextures {};

// load an image and keep the pixel data in memory
const ImageData& loadImage(const std::string& path, const std::string& name) {
    auto it = loadedImages.find(name);
    if (it != loadedImages.end()) {
        return it->second;
    }

    ImageData data {};
    data.path = texturesPath + path;
    data.ptr = stbi_load(data.path.c_str(), &data.width, &data.height, &data.channel_number, 0);//ERR

    if (data.ptr == nullptr) {
        throw std::runtime_error("Image " + name + " (" + data.path + ") non chargé\n");
    }

    auto inserted = loadedImages.emplace(name, std::move(data));
    return inserted.first->second;
}

void createTextureFromImage(const std::string& imageName, const std::string& textureName) {
    // If image is not already loaded, load it first
    auto imageIt = loadedImages.find(imageName);
    if (imageIt == loadedImages.end()) {
        // Load the image with the same name as used to store it
        loadImage(imageName, imageName);
        imageIt = loadedImages.find(imageName);
    }

    const ImageData& image = imageIt->second;
    GLBI_Texture texture;
    texture.createTexture();
    texture.loadImage(static_cast<unsigned int>(image.width), static_cast<unsigned int>(image.height), static_cast<unsigned int>(image.channel_number), image.ptr);
    loadedTextures.emplace(textureName, std::move(texture));
}

void startTextureRender(const std::string& textureName) {
    myEngine.activateTexturing(true);
    auto& t = loadedTextures.at(textureName);
    t.attachTexture();
}

void endTextureRender(const std::string& textureName) {
    auto& t = loadedTextures.at(textureName);
    t.detachTexture();
    myEngine.activateTexturing(false);
}

void freeAllResources() {
    loadedTextures.clear();

    for (auto& [name, img] : loadedImages) {
        if (img.ptr) {
            stbi_image_free(img.ptr); //ERR
            img.ptr = nullptr;
        }
    }
    loadedImages.clear();
}