#include <iostream>
#include <fstream>
#include <QApplication>
#include <QLabel>
#include <QImage>
#include <QPixmap>

#include "Camera.h"
#include "Renderer.h"
#include "Scene.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    std::string filePath = "../resources/scenes/example_scene.txt";
    if (argc > 1) {
        filePath = argv[1];
    }

    Scene scene = SceneParser::parseScene(filePath);
    Camera camera(Vector3D(0, 0, -2), Vector3D(0, 0, -1), 90.0f);
    Renderer renderer(scene, camera, 800, 600);

    QImage image = renderer.renderScene();

    QLabel label;
    label.setPixmap(QPixmap::fromImage(image));
    label.show();

    return app.exec();
}