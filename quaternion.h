#ifndef QUATERNION_H
#define QUATERNION_H

#include <array>

class Quaternion {
private:
    double w, x, y, z;

public:
    // Default constructor
    Quaternion() : w(1.0), x(0.0), y(0.0), z(0.0) {}

    // Constructor
    Quaternion(double nw, double nx, double ny, double nz) : w(nw), x(nx), y(ny), z(nz) {}

    // Addition Operations
    Quaternion operator+(const Quaternion& q) const;

    // Multiplication Operations
    Quaternion operator*(const Quaternion& q) const;

    // Conjugating
    Quaternion conjugate() const;

    // Norm
    double norm() const;

    // Unitary Quaternions
    Quaternion unit() const;

    // Scalar product
    double dot(const Quaternion& q) const;

    // Vectorial product
    Quaternion cross(const Quaternion& q) const;

    // Matrcial product
    Quaternion multiply(const Quaternion& q) const;

    Quaternion MatrixToQuaternion(const std::array<std::array<double, 3>, 3>& matrix);
    std::array<std::array<double, 3>, 3> QuaternionToMatrix() const;
    static Quaternion fromAxisAngle(const std::array<double, 3>& axis, double angle);

    double getW() const { return w; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Setter methods
    void setW(double nw) { w = nw; }
    void setX(double nx) { x = nx; }
    void setY(double ny) { y = ny; }
    void setZ(double nz) { z = nz; }
};

#endif // QUATERNION_H
