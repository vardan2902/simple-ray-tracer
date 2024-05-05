#include <fstream>
#include <sstream>

#include "Scene.h"
#include "Camera.h"

SceneParser::SceneParser() {
    parseFunctions["shininess"] = [this](auto &&PH1, auto &&PH2) {
        parseShininess(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    };
    parseFunctions["camera"] = [this](auto &&PH1, auto &&PH2) {
        parseCamera(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    };
    parseFunctions["sphere"] = [this](auto &&PH1, auto &&PH2) {
        parseSphere(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    };
    parseFunctions["plane"] = [this](auto &&PH1, auto &&PH2) {
        parsePlane(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    };
    parseFunctions["triangle"] = [this](auto &&PH1, auto &&PH2) {
        parseTriangle(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    };
    parseFunctions["mesh"] = [this](auto &&PH1, auto &&PH2) {
        parseMesh(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    };
    parseFunctions["point-light"] = [this](auto &&PH1, auto &&PH2) {
        parsePointLight(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    };;
    parseFunctions["directional-light"] = [this](auto &&PH1, auto &&PH2) {
        parseDirectionalLight(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    };
    parseFunctions["spot-light"] = [this](auto &&PH1, auto &&PH2) {
        parseSpotLight(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    };
}


void SceneParser::parseShininess(const std::string &params, Scene &scene) {
    std::istringstream iss(params);
    std::string type;   // To store the "scene-params" keyword
    float shininess;    // Camera position

    // Parse the camera parameters
    iss >> type >> shininess;
    if (iss.fail())
        throw std::runtime_error("Error parsing camera parameters.");

    scene.shininess = shininess;
}

void SceneParser::parseCamera(const std::string &params, Scene &scene) {
    std::istringstream iss(params);
    std::string type;  // To store the "camera" keyword
    float px, py, pz;  // Camera position
    float dx, dy, dz;  // Camera direction
    float fov;         // Field of view

    // Parse the camera parameters
    iss >> type >> px >> py >> pz >> dx >> dy >> dz >> fov;
    if (iss.fail()) {
        // Handle parsing error, e.g., log an error message or throw an exception
        throw std::runtime_error("Error parsing camera parameters.");
    }

    Vector3D up(0, 1, 0);

    // Create and set the camera in the scene
    Camera camera(Vector3D(px, py, pz), Vector3D(dx, dy, dz), up, fov);

    scene.setCamera(camera);
}

void SceneParser::parseSphere(const std::string &params, Scene &scene) {
    std::istringstream iss(params);
    std::string type;  // To store the "sphere" keyword
    float x, y, z;     // Sphere center
    float radius;      // Sphere radius
    float r, g, b;     // Sphere color
    float reflectivity, transparency, refractiveIndex;

    // Parse the sphere parameters
    iss >> type >> x >> y >> z >> radius >> r >> g >> b >> reflectivity >> transparency >> refractiveIndex;
    if (iss.fail()) {
        // Handle parsing error
        throw std::runtime_error("Error parsing sphere parameters.");
    }

    // Create and add the sphere to the scene
    auto sphere = std::make_shared<Sphere>(Vector3D(x, y, z), radius, Vector3D(r, g, b), reflectivity, transparency,
                                           refractiveIndex);
    scene.addFigure(sphere);
}

void SceneParser::parsePlane(const std::string &params, Scene &scene) {
    std::istringstream iss(params);
    std::string type;  // To store the "plane" keyword
    float px, py, pz;  // Plane point
    float nx, ny, nz;  // Plane normal
    float r, g, b;     // Plane color
    float reflectivity, transparency, refractiveIndex;

    // Parse the plane parameters
    iss >> type >> px >> py >> pz >> nx >> ny >> nz >> r >> g >> b >> reflectivity >> transparency >> refractiveIndex;
    if (iss.fail()) {
        // Handle parsing error
        throw std::runtime_error("Error parsing plane parameters.");
    }

    // Create and add the plane to the scene
    auto plane = std::make_shared<Plane>(Vector3D(px, py, pz), Vector3D(nx, ny, nz).normalize(),
                                         Vector3D(r, g, b), reflectivity, transparency, refractiveIndex);
    scene.addFigure(plane);
}

void SceneParser::parseTriangle(const std::string &params, Scene &scene) {
    std::istringstream iss(params);
    std::string type;  // To store the "triangle" keyword
    float x1, y1, z1;  // Coordinates of the first vertex
    float x2, y2, z2;  // Coordinates of the second vertex
    float x3, y3, z3;  // Coordinates of the third vertex
    float r, g, b;     // Triangle color
    float reflectivity, transparency, refractiveIndex;

    // Parse the triangle parameters
    iss >> type >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3 >> r >> g >> b >> reflectivity >> transparency
        >> refractiveIndex;
    if (iss.fail()) {
        // Handle parsing error
        throw std::runtime_error("Error parsing triangle parameters.");
    }

    // Create and add the triangle to the scene
    auto triangle = std::make_shared<Triangle>(Vector3D(x1, y1, z1), Vector3D(x2, y2, z2), Vector3D(x3, y3, z3),
                                               Vector3D(r, g, b), reflectivity, transparency, refractiveIndex);
    scene.addFigure(triangle);
}

void SceneParser::parseMesh(const std::string &params, Scene &scene) {
    std::istringstream iss(params);
    std::string type;  // To store the "mesh" keyword
    int numVertices, numFaces;
    std::vector<Vector3D> vertices;
    std::vector<Triangle> faces;
    float r, g, b;     // Mesh color
    float reflectivity, transparency, refractiveIndex;  // Material properties

    // Parse mesh header with material properties and color
    iss >> type >> numVertices >> numFaces >> r >> g >> b >> reflectivity >> transparency >> refractiveIndex;
    if (iss.fail()) {
        throw std::runtime_error("Error parsing mesh header.");
    }

    // Parse vertices
    for (int i = 0; i < numVertices; ++i) {
        float x, y, z;
        iss >> x >> y >> z;
        vertices.emplace_back(x, y, z);
    }

    // Parse faces (triangles)
    for (int i = 0; i < numFaces; ++i) {
        int v1, v2, v3;
        iss >> v1 >> v2 >> v3;
        faces.emplace_back(vertices[v1], vertices[v2], vertices[v3], Vector3D(r, g, b), reflectivity, transparency,
                           refractiveIndex);
    }

    // Create and add the mesh to the scene
    auto mesh = std::make_shared<Mesh>(faces, Vector3D(r, g, b), reflectivity, transparency, refractiveIndex);
    scene.addFigure(mesh);
}

void SceneParser::parsePointLight(const std::string &params, Scene &scene) {
    std::istringstream iss(params);
    std::string type;  // To store the "point-light" keyword
    float x, y, z;     // Light position
    float r, g, b;     // Light color
    float intensity;   // Light intensity
    // Optional: Attenuation factors (constant, linear, quadratic)
    float constantAttenuation = 1.0, linearAttenuation = 0.0, quadraticAttenuation = 0.0;

    // Parse the point light parameters
    iss >> type >> x >> y >> z >> r >> g >> b >> intensity;
    // Optional: Parse attenuation factors if provided
    iss >> constantAttenuation >> linearAttenuation >> quadraticAttenuation;

    if (iss.fail())
        throw std::runtime_error("Error parsing point light parameters.");

    // Create and add the point light to the scene
    auto pointLight = std::make_shared<PointLight>(Vector3D(x, y, z), Vector3D(r, g, b), intensity,
                                                   constantAttenuation, linearAttenuation, quadraticAttenuation);
    scene.addLight(pointLight);
}

void SceneParser::parseDirectionalLight(const std::string &params, Scene &scene) {
    std::istringstream iss(params);
    std::string type;  // To store the "directional-light" keyword
    float dx, dy, dz;  // Light direction
    float r, g, b;     // Light color
    float intensity;   // Light intensity

    // Parse the directional light parameters
    iss >> type >> dx >> dy >> dz >> r >> g >> b >> intensity;
    if (iss.fail())
        throw std::runtime_error("Error parsing directional light parameters.");

    // Create and add the directional light to the scene
    auto directionalLight = std::make_shared<DirectionalLight>(Vector3D(dx, dy, dz), Vector3D(r, g, b), intensity);
    scene.addLight(directionalLight);
}

void SceneParser::parseSpotLight(const std::string &params, Scene &scene) {
    std::istringstream iss(params);
    std::string type;    // To store the "spotlight" keyword
    float px, py, pz;    // Light position
    float dx, dy, dz;    // Light direction
    float cutoff;        // Cutoff angle
    float falloff;       // Falloff factor
    float r, g, b;       // Light color
    float intensity;     // Light intensity

    // Parse the spotlight parameters
    iss >> type >> px >> py >> pz >> dx >> dy >> dz >> cutoff >> falloff >> r >> g >> b >> intensity;
    if (iss.fail())
        throw std::runtime_error("Error parsing spotlight parameters.");

    // Normalize the direction vector
    Vector3D direction(dx, dy, dz);
    direction.normalize();
    // Create and add the spotlight to the scene
    auto spotLight = std::make_shared<SpotLight>(Vector3D(px, py, pz), direction, cutoff, falloff, Vector3D(r, g, b), intensity);
    scene.addLight(spotLight);
}

Scene SceneParser::parseScene(const std::string &filename) {
    Scene scene;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (parseFunctions.find(type) != parseFunctions.end())
            parseFunctions[type](line, scene);
    }

    return scene;
}