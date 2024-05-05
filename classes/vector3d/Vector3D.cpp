#include <cmath>

#include "Vector3D.h"

// Default constructor
Vector3D::Vector3D() : x(0), y(0), z(0) {}

// Constructor with parameters
Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

// Copy constructor
Vector3D::Vector3D(const Vector3D &v) = default;

// Vector addition
Vector3D Vector3D::operator+(const Vector3D &v) const {
    return {x + v.x, y + v.y, z + v.z};
}

// Vector subtraction
Vector3D Vector3D::operator-(const Vector3D &v) const {
    return {x - v.x, y - v.y, z - v.z};
}

// Scalar multiplication
Vector3D Vector3D::operator*(float scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

// Scalar division
Vector3D Vector3D::operator/(float scalar) const {
    return {x / scalar, y / scalar, z / scalar};
}

// Dot product
float Vector3D::dot(const Vector3D &v) const {
    return x * v.x + y * v.y + z * v.z;
}

// Cross product
Vector3D Vector3D::cross(const Vector3D &v) const {
    return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}

// Length of the vector
float Vector3D::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Normalize the vector
Vector3D Vector3D::normalize() const {
    const float EPSILON = 1e-8;
    float len = length();
    if (len > EPSILON)
        return {x / len, y / len, z / len};
}

Vector3D Vector3D::operator-() const {
    return {-x, -y, -z};
}

Vector3D Vector3D::multiply(const Vector3D &other) const {
    return {x * other.x, y * other.y, z * other.z};
}
