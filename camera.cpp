#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "Quaternion.h"

Quaternion cameraRotation;
GLfloat cameraX = 0.0f;
GLfloat cameraY = 0.0f;
GLfloat cameraZ = -500.0f;
GLfloat zoomSpeed = 0.1f;

GLfloat zoom = 1.0f;
bool isDragging = false;
double lastMouseX = 0.0;
double lastMouseY = 0.0;
const GLfloat rotationSpeed = 0.001;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const GLfloat cameraSpeed = 10.0f;

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_UP:
                cameraZ += cameraSpeed;
                break;
            case GLFW_KEY_DOWN:
                cameraZ -= cameraSpeed;
                break;
            case GLFW_KEY_RIGHT:
                cameraX -= cameraSpeed;
                break;
            case GLFW_KEY_LEFT:
                cameraX += cameraSpeed;
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
    if (isDragging)
    {
        double deltaX = xpos - lastMouseX;
        double deltaY = ypos - lastMouseY;

        Quaternion rotationX(Quaternion::fromAxisAngle({1.0, 0.0, 0.0}, deltaY * rotationSpeed));
        Quaternion rotationY(Quaternion::fromAxisAngle({0.0, 1.0, 0.0}, deltaX * rotationSpeed));

        cameraRotation = rotationX * rotationY * cameraRotation;

        lastMouseX = xpos;
        lastMouseY = ypos;
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    zoom -= yoffset * zoomSpeed;
    if (zoom < 0.1f)
        zoom = 0.1f;
    if (zoom > 3.0f)
        zoom = 3.0f;
}

void applyCameraTransformations() {
    // Convert the quaternion to a rotation matrix
    std::array<std::array<double, 3>, 3> matrix = cameraRotation.QuaternionToMatrix();

    // Convert your matrix to a format that OpenGL can use (1D array)
    GLfloat gl_matrix[16] = {
            (GLfloat)matrix[0][0], (GLfloat)matrix[0][1], (GLfloat)matrix[0][2], 0.0f,
            (GLfloat)matrix[1][0], (GLfloat)matrix[1][1], (GLfloat)matrix[1][2], 0.0f,
            (GLfloat)matrix[2][0], (GLfloat)matrix[2][1], (GLfloat)matrix[2][2], 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };

    // Apply the rotation
    glMultMatrixf(gl_matrix);
}
