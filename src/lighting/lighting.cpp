#include "lighting.hpp"

bool lightInitialized = false;

void initMainLighting() {
    Vector3D light_attenuation(0,0,0); // puissance
    Vector3D color(1,1,0); // couleur

    myEngine.setSpecularColor(color);
    myEngine.setAttenuationFactor(light_attenuation);
    myEngine.setShininess(0.0f);
    myEngine.setLightIntensity(color, 0);
};

void initTrainLighting() {
    Vector3D light_attenuation(1,0,0); // puissance
    Vector3D color(1,0,0); // couleur

    myEngine.setSpecularColor(color);
    myEngine.setAttenuationFactor(light_attenuation);
    myEngine.setShininess(0.0f);
    myEngine.addALight({0,0,0,1}, color);
};

void initLights() {
    //if light not placed yet AND we are on the shader that use lighting
    if (!lightInitialized && myEngine.currentShader == 1) {
        lightInitialized = true;
        initMainLighting();
        initTrainLighting();
    }
}

void handleMainLighting(double time) {
    const float radius{10.0f};
    const float height{25.0f};
    const float speed{0.5};

    myEngine.setLightPosition({
        (float)(sin(time * speed) * radius),
        height,
        (float)(cos(time * speed) * radius),
        0.0f
    }, 0);
};

void handleTrainLighting(float x, float y, float z) {
    myEngine.setLightPosition({x,y,z,1}, 1);
}