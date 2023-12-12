#include <fstream>
#include <sstream>

#include "Scene.h"

Scene SceneParser::parseScene(const std::string &filename) {
    Scene scene;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "sphere") {
            float x, y, z, radius, r, g, b, reflectivity, transparency, refractiveIndex;
            iss >> x >> y >> z >> radius >> r >> g >> b >> reflectivity >> transparency >> refractiveIndex;
            // Create sphere with color, reflectivity, transparency, and refractive index
            Sphere sphere(Vector3D(x, y, z), radius, Vector3D(r, g, b), reflectivity, transparency, refractiveIndex);
            // Add the sphere to the scene
            scene.addSphere(sphere);
        } else if (type == "light") {
            float x, y, z, r, g, b;
            iss >> x >> y >> z >> r >> g >> b;
            // Add light to the scene
            scene.addLight(Light(Vector3D(x, y, z), Vector3D(r, g, b)));
        }
    }

    return scene;
}