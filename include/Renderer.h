#ifndef RENDERER_H
#define RENDERER_H

#include <QImage>

#include "Scene.h"
#include "Camera.h"

class Renderer {
public:
    Renderer(const Scene &scene, int width, int height);

    [[nodiscard]] QImage renderScene() const;

private:
    Scene scene;
    Camera camera;
    int imageWidth;
    int imageHeight;

    [[nodiscard]] QColor traceRay(const Ray &ray, int depth) const;
};

#endif // RENDERER_H
