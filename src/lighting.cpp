#include "lighting.hpp"

void handleMainLighting(double time) {
    myEngine.setLightPosition(
        {
            0,
            cell_size*5,
            cell_size*5,
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
    myEngine.setLightPosition({ x, y, z, 1.0 }, 0);
    myEngine.setLightIntensity({1.0, 1.0, 0.0}, 0);
    myEngine.setShininess(0.0f);
    myEngine.setSpecularColor({1.0, 1.0, 0.0});
    myEngine.setAttenuationFactor({1.0, 0.0, 0.0});
}