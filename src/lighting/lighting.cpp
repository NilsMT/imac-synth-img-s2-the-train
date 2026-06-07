#include "lighting.hpp"

void handleMainLighting(double time) {
    //TODO: do the "sun" like lightning, maybe animate it with the time
    const float angle{15.};
    const float hauteur{10.};
    Vector4D light_pos(0,20,0,0);
    myEngine.setLightPosition({
        sin(time) * angle,
        hauteur,
        cos(time) * angle,
        0.0f
    }, 0);
    // couleur light
    Vector3D light_intensite(1,0.7,0.7);
    myEngine.setLightIntensity(light_intensite);

    Vector3D light_attenuation(1,0,0);
    myEngine.setAttenuationFactor(light_attenuation);

    myEngine.setShininess(24.);

    Vector3D reflet_couleur_objet(1,1,1);
    myEngine.setSpecularColor(reflet_couleur_objet);

};

void handleTrainLighting(float x, float y, float z) {
    //TODO: place the train light at the given coords (it's the front of train)
    Vector4D position(x,y,z,1.);
    Vector3D couleur(1.,0.5,0.7);
    myEngine.addALight(position,couleur);
}