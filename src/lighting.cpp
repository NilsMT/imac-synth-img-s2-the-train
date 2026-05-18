#include "lighting.hpp"

void handleMainLighting(double time) {
    myEngine.setLightPosition(
        {
            cos(time)*cell_size*5, 
            cell_size*5,
            sin(time)*cell_size*5,
            0.0
        }, 
        0 //light type (0 = SpotLight, 1 = PointLight)
    );
    myEngine.setLightIntensity({2.0, 2.0, 2.0}, 0);
    myEngine.setShininess(0.0f);
    myEngine.setSpecularColor({1.0, 1.0, 1.0});
    myEngine.setAttenuationFactor({0.75, 0.0, 0.0});
};

void handleTrainLighting(float x, float y, float z) {
    myEngine.setLightPosition({ x, y, z, 1.0 }, 0); // Position in world space
    myEngine.setLightIntensity({1.0, 1.0, 1.0}, 0); // White light
    myEngine.setShininess(0.0f);
    myEngine.setSpecularColor({1.0, 1.0, 0.0}); // White specular
    myEngine.setAttenuationFactor({1.0, 0.0, 0.0}); // No attenuation (omnidirectional)
}