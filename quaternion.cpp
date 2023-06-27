#include <cmath>
#include "quaternion.h"

// Addition Operations
Quaternion Quaternion::operator+(const Quaternion& q) const {
    return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
}

// Multiplication Operations
Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion(
            w*q.w - x*q.x - y*q.y - z*q.z,
            w*q.x + x*q.w + y*q.z - z*q.y,
            w*q.y - x*q.z + y*q.w + z*q.x,
            w*q.z + x*q.y - y*q.x + z*q.w
    );
}

// Conjugating
Quaternion Quaternion::conjugate() const {
    return Quaternion(w, -x, -y, -z);
}

// Norm
double Quaternion::norm() const {
    return std::sqrt(w*w + x*x + y*y + z*z);
}

// Unitary Quaternions
Quaternion Quaternion::unit() const {
    double n = norm();
    return Quaternion(w/n, x/n, y/n, z/n);
}

// Scalar product
double Quaternion::dot(const Quaternion& q) const {
    return w*q.w + x*q.x + y*q.y + z*q.z;
}

// Vectorial product
Quaternion Quaternion::cross(const Quaternion& q) const {

    return Quaternion(0, 0, 0, 0);
}

// Matrcial product
Quaternion Quaternion::multiply(const Quaternion& q) const {
    return (*this) * q;

}

std::array<std::array<double, 3>, 3> Quaternion::QuaternionToMatrix() const {
    std::array<std::array<double, 3>, 3> matrix;

    double ww = w * w;
    double xx = x * x;
    double yy = y * y;
    double zz = z * z;

    matrix[0][0] = ww + xx - yy - zz;
    matrix[0][1] = 2.0 * (x*y - w*z);
    matrix[0][2] = 2.0 * (x*z + w*y);

    matrix[1][0] = 2.0 * (x*y + w*z);
    matrix[1][1] = ww - xx + yy - zz;
    matrix[1][2] = 2.0 * (y*z - w*x);

    matrix[2][0] = 2.0 * (x*z - w*y);
    matrix[2][1] = 2.0 * (y*z + w*x);
    matrix[2][2] = ww - xx - yy + zz;

    return matrix;
}

Quaternion Quaternion::MatrixToQuaternion(const std::array<std::array<double, 3>, 3>& matrix) {
    double trace = matrix[0][0] + matrix[1][1] + matrix[2][2];
    Quaternion q;

    if (trace > 0) {
        double s = 0.5 / std::sqrt(trace + 1.0);
        q.w = 0.25 / s;
        q.x = (matrix[2][1] - matrix[1][2]) * s;
        q.y = (matrix[0][2] - matrix[2][0]) * s;
        q.z = (matrix[1][0] - matrix[0][1]) * s;
    } else {
        if (matrix[0][0] > matrix[1][1] && matrix[0][0] > matrix[2][2]) {
            double s = 2.0 * std::sqrt(1.0 + matrix[0][0] - matrix[1][1] - matrix[2][2]);
            q.w = (matrix[2][1] - matrix[1][2]) / s;
            q.x = 0.25 * s;
            q.y = (matrix[0][1] + matrix[1][0]) / s;
            q.z = (matrix[0][2] + matrix[2][0]) / s;
        } else if (matrix[1][1] > matrix[2][2]) {
            double s = 2.0 * std::sqrt(1.0 + matrix[1][1] - matrix[0][0] - matrix[2][2]);
            q.w = (matrix[0][2] - matrix[2][0]) / s;
            q.x = (matrix[0][1] + matrix[1][0]) / s;
            q.y = 0.25 * s;
            q.z = (matrix[1][2] + matrix[2][1]) / s;
        } else {
            double s = 2.0 * std::sqrt(1.0 + matrix[2][2] - matrix[0][0] - matrix[1][1]);
            q.w = (matrix[1][0] - matrix[0][1]) / s;
            q.x = (matrix[0][2] + matrix[2][0]) / s;
            q.y = (matrix[1][2] + matrix[2][1]) / s;
            q.z = 0.25 * s;
        }
    }

    return q;
}

Quaternion Quaternion::fromAxisAngle(const std::array<double, 3>& axis, double angle) {
    Quaternion q;
    double s = std::sin(angle / 2);

    q.w = std::cos(angle / 2);
    q.x = axis[0] * s;
    q.y = axis[1] * s;
    q.z = axis[2] * s;

    return q;
}

