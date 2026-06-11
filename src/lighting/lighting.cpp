#include "lighting.hpp"

bool lightInitialized = false;

void initMainLighting() {
    Vector3D color(1,1,0); // couleur
    
    myEngine.setLightIntensity(color, 0);
};

void initTrainLighting() {
    Vector3D light_attenuation(1,0,0); // puissance
    Vector3D color(2,0,0); // couleur
    
    myEngine.addALight({0,0,0,1}, color);
};

void initLights() {
    Vector3D attenuation(1.0f,1.0f,1.0f);
    Vector3D quantity(1.0f,1.0f,1.0f);
    float shininess = 0.0f;

    //if light not placed yet AND we are on the shader that use lighting
    if (!lightInitialized && myEngine.currentShader == 1) {
        lightInitialized = true;

        myEngine.setAttenuationFactor(attenuation);
        myEngine.setShininess(shininess);
        myEngine.setSpecularColor(quantity);

        initMainLighting();
        initTrainLighting();
    }
}

void handleMainLighting(double time) {
    const float radius{10.0f};
    const float height{25.0f};
    const float speed{0.5};
    const float x_offset = 0.0f;
    const float z_offset = -50.f;

    myEngine.setLightPosition({
        (float)(sin(time * speed) * radius) + x_offset,
        height,
        (float)(cos(time * speed) * radius) + z_offset,
        0.0f
    }, 0);
};

void handleTrainLighting(float x, float y, float z) {
    myEngine.setLightPosition({x,y,z,1}, 1);
}