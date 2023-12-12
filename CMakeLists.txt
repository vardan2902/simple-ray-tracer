cmake_minimum_required(VERSION 3.26)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/Users/varpet/Qt/6.6.1/macos/lib/cmake")

include_directories(
        "/Users/varpet/Qt/6.6.1/macos/include"
        "include"
)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(
    RayTracer main.cpp
        classes/vector3d/Vector3D.cpp
        include/Vector3D.h
        classes/ray/Ray.cpp
        include/Ray.h
        include/Figures.h
        classes/figures/Sphere.cpp
        include/Scene.h
        classes/scene/Scene.cpp
        include/Camera.h
        classes/scene/Camera.cpp
        include/Lights.h
        classes/lights/Light.cpp
        classes/scene/SceneParser.cpp
        include/Renderer.h
        classes/scene/Renderer.cpp
        include/constants.h
        utils/reflection_refraction_calculation_utils.cpp
        include/utils.h
)

target_link_libraries(RayTracer PRIVATE Qt6::Widgets)
