#ifndef RENDERER_H
#define RENDERER_H

#include <QImage>

#include "Scene.h"
#include "Camera.h"

class Renderer {
public:
    Renderer(const Scene &scene, const Camera &camera, int width, int height);

    QImage renderScene() const;

private:
    Scene scene;
    Camera camera;
    int imageWidth;
    int imageHeight;

    QColor calculatePixelColor(const Ray &ray, int depth) const;
};

#endif // RENDERER_H
