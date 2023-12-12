#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D {
public:
    float x, y, z;

    // Constructors
    Vector3D();
    Vector3D(float x, float y, float z);
    Vector3D(const Vector3D &v);

    // Operator Overloads
    Vector3D operator-() const;
    Vector3D operator+(const Vector3D &v) const;
    Vector3D operator-(const Vector3D &v) const;
    Vector3D operator*(float scalar) const;

    // Vector Operations
    float dot(const Vector3D &v) const;
    float length() const;
    Vector3D cross(const Vector3D &v) const;
    Vector3D normalize() const;
    Vector3D multiply(const Vector3D &other) const;
};

#endif // VECTOR3D_H
