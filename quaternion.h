#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
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

    std::array<std::array<double, 3>, 3> QuaternionToMatrix(const Quaternion& q) {
        std::array<std::array<double, 3>, 3> matrix;

        double w = q.getW();
        double x = q.getX();
        double y = q.getY();
        double z = q.getZ();

        double w2 = w * w;
        double x2 = x * x;
        double y2 = y * y;
        double z2 = z * z;

        matrix[0][0] = w2 + x2 - y2 - z2;
        matrix[0][1] = 2 * (x * y - w * z);
        matrix[0][2] = 2 * (x * z + w * y);

        matrix[1][0] = 2 * (x * y + w * z);
        matrix[1][1] = w2 - x2 + y2 - z2;
        matrix[1][2] = 2 * (y * z - w * x);

        matrix[2][0] = 2 * (x * z - w * y);
        matrix[2][1] = 2 * (y * z + w * x);
        matrix[2][2] = w2 - x2 - y2 + z2;

        return matrix;
    }

    Quaternion MatrixToQuaternion(const std::array<std::array<double, 3>, 3>& matrix) {
        double m11 = matrix[0][0];
        double m12 = matrix[0][1];
        double m13 = matrix[0][2];
        double m21 = matrix[1][0];
        double m22 = matrix[1][1];
        double m23 = matrix[1][2];
        double m31 = matrix[2][0];
        double m32 = matrix[2][1];
        double m33 = matrix[2][2];

        double trace = m11 + m22 + m33;

        if (trace > 0) {
            double s = 0.5 / std::sqrt(trace + 1.0);
            double w = 0.25 / s;
            double x = (m32 - m23) * s;
            double y = (m13 - m31) * s;
            double z = (m21 - m12) * s;

            return Quaternion(w, x, y, z);
        }
        else if (m11 > m22 && m11 > m33) {
            double s = 2.0 * std::sqrt(1.0 + m11 - m22 - m33);
            double w = (m32 - m23) / s;
            double x = 0.25 * s;
            double y = (m12 + m21) / s;
            double z = (m13 + m31) / s;

            return Quaternion(w, x, y, z);
        }
        else if (m22 > m33) {
            double s = 2.0 * std::sqrt(1.0 + m22 - m11 - m33);
            double w = (m13 - m31) / s;
            double x = (m12 + m21) / s;
            double y = 0.25 * s;
            double z = (m23 + m32) / s;

            return Quaternion(w, x, y, z);
        }
        else {
            double s = 2.0 * std::sqrt(1.0 + m33 - m11 - m22);
            double w = (m21 - m12) / s;
            double x = (m13 + m31) / s;
            double y = (m23 + m32) / s;
            double z = 0.25 * s;

            return Quaternion(w, x, y, z);
        }
    }

    double getW() const { return w; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }





};

#endif  // QUATERNION_H
