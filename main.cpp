
#include <iostream>
#include <cmath>
#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Quaternion {

private:

    double w, x, y, z;

public:

    // Default constructor
    Quaternion() : w(1.0), x(0.0), y(0.0), z(0.0) {}

    // Constructor
    Quaternion(double nw, double nx, double ny, double nz) : w(nw), x(nx), y(ny), z(nz) {}

    // Addition Operations
    Quaternion operator+(const Quaternion& q) const {

        return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);

    }

    //Multiplication Operations
    Quaternion operator*(const Quaternion& q) const {

        double nw = w * q.w - x * q.x - y * q.y - z * q.z;
        double nx = w * q.x + x * q.w + y * q.z - z * q.y;
        double ny = w * q.y - x * q.z + y * q.w + z * q.x;
        double nz = w * q.z + x * q.y - y * q.x + z * q.w;
        return Quaternion(nw, nx, ny, nz);

    }

    // Conjugating
    Quaternion conjugate() const {

        return Quaternion(w, -x, -y, -z);

    }

    // Norm
    double norm() const {

        return std::sqrt(w * w + x * x + y * y + z * z);

    }

    //Unitary Quaternons
    Quaternion unit() const {
        double n = norm();
        if (n != 0.0)
            return Quaternion(w / n, x / n, y / n, z / n);
        else
            return Quaternion();
    }

    // Scalar product
    double dot(const Quaternion& q) const {

        return w * q.w + x * q.x + y * q.y + z * q.z;
    }

    //Vectorial product
    Quaternion cross(const Quaternion& q) const {

        double nw = 0.0;
        double nx = y * q.z - z * q.y;
        double ny = z * q.x - x * q.z;
        double nz = x * q.y - y * q.x;
        return Quaternion(nw, nx, ny, nz);

    }

    //Matrcial product
    Quaternion multiply(const Quaternion& q) const {

        double nw = w * q.w - x * q.x - y * q.y - z * q.z;
        double nx = w * q.x + x * q.w + y * q.z - z * q.y;
        double ny = w * q.y - x * q.z + y * q.w + z * q.x;
        double nz = w * q.z + x * q.y - y * q.x + z * q.w;
        return Quaternion(nw, nx, ny, nz);

    }


    double getW() const { return w; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

};

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
Quaternion MatrixToQuaternion(const std::array<std::array<double, 3>, 3>& matrix);
std::array<std::array<double, 3>, 3> QuaternionToMatrix(const Quaternion& q);
void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat zoom = 1.0f;
bool isDragging = false;
double lastMouseX = 0.0;
double lastMouseY = 0.0;



int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mon espoir", NULL, NULL);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(halfScreenWidth, halfScreenHeight, -500);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);

        DrawCube(halfScreenWidth, halfScreenHeight, -500, 200);

        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();


    }

    glfwTerminate();

    return 0;

    /*Quaternion q(0.7, 0.0, 1.0, 0.0);

    std::array<std::array<double, 3>, 3> matrix = QuaternionToMatrix(q);
    std::cout << "Matrix : " << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    Quaternion convertedQuaternion = MatrixToQuaternion(matrix);
    std::cout << "Quaternion converted : " << convertedQuaternion.getW() << " "
              << convertedQuaternion.getX() << " " << convertedQuaternion.getY() << " "
              << convertedQuaternion.getZ() << std::endl;*/

}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const GLfloat rotationSpeed = 10;

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_UP:
                rotationX -= rotationSpeed;
                break;
            case GLFW_KEY_DOWN:
                rotationX += rotationSpeed;
                break;
            case GLFW_KEY_RIGHT:
                rotationY += rotationSpeed;
                break;
            case GLFW_KEY_LEFT:
                rotationY -= rotationSpeed;
                break;
        }
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        isDragging = true;
        glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        isDragging = false;
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (isDragging) {
        double deltaX = xpos - lastMouseX;
        double deltaY = ypos - lastMouseY;

        rotationY += deltaX * 0.1f;
        rotationX += deltaY * 0.1f;

        lastMouseX = xpos;
        lastMouseY = ypos;
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    const GLfloat zoomSpeed = 0.1f;
    zoom += yoffset * zoomSpeed;

    // Limit the zoom range
    if (zoom < 0.1f) {

        zoom = 0.1f;
    }
    else if (zoom > 10.0f) {

        zoom = 10.0f;
    }
}

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


void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f / zoom;

    GLfloat vertices[] =
            {
                    // Front face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

                    // Back face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left

                    // Left face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

                    // Right face
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

                    // Top face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left

                    // Bottom face
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
            };

    GLfloat colors[] =
            {
                    // Front face (red)
                    1.0f, 0.0f, 0.0f, 1.0f, // top left
                    1.0f, 0.0f, 0.0f, 1.0f, // top right
                    1.0f, 0.0f, 0.0f, 1.0f, // bottom right
                    1.0f, 0.0f, 0.0f, 1.0f, // bottom left

                    // Back face (green)
                    0.0f, 1.0f, 0.0f, 1.0f, // top left
                    0.0f, 1.0f, 0.0f, 1.0f, // top right
                    0.0f, 1.0f, 0.0f, 1.0f, // bottom right
                    0.0f, 1.0f, 0.0f, 1.0f, // bottom left

                    // Left face (blue)
                    0.0f, 0.0f, 1.0f, 1.0f, // top left
                    0.0f, 0.0f, 1.0f, 1.0f, // top right
                    0.0f, 0.0f, 1.0f, 1.0f, // bottom right
                    0.0f, 0.0f, 1.0f, 1.0f, // bottom left

                    // Right face (yellow)
                    1.0f, 1.0f, 0.0f, 1.0f, // top left
                    1.0f, 1.0f, 0.0f, 1.0f, // top right
                    1.0f, 1.0f, 0.0f, 1.0f, // bottom right
                    1.0f, 1.0f, 0.0f, 1.0f, // bottom left

                    // Top face (cyan)
                    0.0f, 1.0f, 1.0f, 1.0f, // top left
                    0.0f, 1.0f, 1.0f, 1.0f, // top right
                    0.0f, 1.0f, 1.0f, 1.0f, // bottom right
                    0.0f, 1.0f, 1.0f, 1.0f, // bottom left

                    // Bottom face (magenta)
                    1.0f, 0.0f, 1.0f, 1.0f, // top left
                    1.0f, 0.0f, 1.0f, 1.0f, // top right
                    1.0f, 0.0f, 1.0f, 1.0f, // bottom right
                    1.0f, 0.0f, 1.0f, 1.0f  // bottom left
            };

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(4, GL_FLOAT, 0, colors);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}