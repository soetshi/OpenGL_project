#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include "quaternion.h"

extern Quaternion cameraRotation;
extern GLfloat cameraX;
extern GLfloat cameraY;
extern GLfloat cameraZ;
extern GLfloat zoomSpeed;
extern GLfloat zoom;
extern bool isDragging;
extern double lastMouseX;
extern double lastMouseY;
extern const GLfloat rotationSpeed;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void applyCameraTransformations();

#endif
