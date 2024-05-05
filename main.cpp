#include <iostream>
#include <fstream>
#include <QApplication>
#include <QLabel>
#include <QImage>
#include <QPixmap>

#include "Renderer.h"
#include "Scene.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    std::string filePath = "../resources/scenes/example_scene.txt";
    if (argc > 1) {
        filePath = argv[1];
    }
    SceneParser parser;

    Scene scene = parser.parseScene(filePath);
    Renderer renderer(scene, 800, 600);

    QImage image = renderer.renderScene();

    QLabel label;
    label.setPixmap(QPixmap::fromImage(image));
    label.show();

    return app.exec();
}