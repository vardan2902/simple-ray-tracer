#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

#include "Figures.h"
#include "Camera.h"
#include "Lights.h"

class Scene {
private:
    std::vector<std::shared_ptr<Figure>> figures;
    std::vector<std::shared_ptr<Light>> lights;
    Camera camera;
public:
    float shininess;

    Scene();

    void addFigure(const std::shared_ptr<Figure> &figure);
    void addLight(const std::shared_ptr<Light> &light);
    void setCamera(const Camera &cam);

    bool closestIntersection(const Ray &ray, float &closest_t, Vector3D &hitPoint, Vector3D &normal, Vector3D &color,
                             MaterialProperties &materialProps) const;
    bool isInShadow(const Ray &shadowRay, float distanceToLight, Vector3D &hitPoint,
                    Vector3D &normal) const;

    [[nodiscard]] Camera getCamera() const;
    [[nodiscard]] Vector3D calculateLighting(Vector3D &hitPoint, Vector3D &normal, const Vector3D &surfaceColor,
                           const Vector3D &viewDir) const;
};

class SceneParser {
private:
    std::unordered_map<std::string, std::function<void(const std::string &, Scene &)>> parseFunctions;
public:
    SceneParser();

    Scene parseScene(const std::string &filename);

    void parseShininess(const std::string &params, Scene &scene);
    void parseCamera(const std::string &params, Scene &scene);
    void parseSphere(const std::string &params, Scene &scene);
    void parsePlane(const std::string &params, Scene &scene);
    void parseTriangle(const std::string &params, Scene &scene);
    void parseMesh(const std::string &params, Scene &scene);
    void parsePointLight(const std::string &params, Scene &scene);
    void parseDirectionalLight(const std::string &params, Scene &scene);
    void parseSpotLight(const std::string &params, Scene &scene);
};

#endif // SCENE_H
