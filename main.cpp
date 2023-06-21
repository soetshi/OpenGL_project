#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <fstream>
#include "stb_image.h"
#include "SOIL.h"
#include "dependencies/tinyobjloader/tiny_obj_loader.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


struct Vertex {
    float x, y, z;
};

struct Face {
    std::array<int, 3> vertexIndices;
};
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
//void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
//void DrawSecondCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
//void DrawThirdCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void DrawTexturedCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength, const char* texturePath);
void setupLighting();
void importAndDisplayObj(const std::string& filename);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat rotationZ = 0.0f;
GLfloat cameraX = 0.0f;
GLfloat cameraY = 0.0f;
GLfloat cameraZ = -500.0f;

GLfloat zoom = 1.0f;
bool isDragging = false;
double lastMouseX = 0.0;
double lastMouseY = 0.0;
const GLfloat rotationSpeed = 0.1;


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

    glViewport(0, 0, screenWidth, screenHeight); //
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
    //void LoadOBJ(const std::string& filepath, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);


    const char* texturePath = "C:\\Users\\axelo\\desktop\\Tuto_OpenGL\\OpenGL_project\\Nezchislav.JPG";
    const char* filePath = "C:\\Users\\axelo\\desktop\\Tuto_OpenGL\\OpenGL_project\\Suzanneslav.obj";
    std::string filename = "C:\\Users\\axelo\\desktop\\Tuto_OpenGL\\OpenGL_project\\Suzanneslav.obj";
    importAndDisplayObj(filename);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);


        glPushMatrix();
        glTranslatef(halfScreenWidth, halfScreenHeight, cameraZ);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glTranslatef(-halfScreenWidth - cameraX, -halfScreenHeight - cameraY, 0);


        setupLighting();
        DrawTexturedCube(halfScreenWidth, halfScreenHeight, -500, 200, texturePath);
       // DrawCube(halfScreenWidth, halfScreenHeight, -500, 200);
       // DrawSecondCube(halfScreenWidth + 250, halfScreenHeight, -500, 150); // Adjust the position and size of the second cube
       // DrawThirdCube(halfScreenWidth + 250, halfScreenHeight, -500, 150);

        rotationZ += rotationSpeed;


       // importAndDisplayObj(filePath);

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
    } else if (zoom > 10.0f) {
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

/*void LoadOBJ(const std::string& filepath, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str()))
    {
        throw std::runtime_error(warn + err);
    }

    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            tinyobj::real_t vx = attrib.vertices[3 * index.vertex_index + 0];
            tinyobj::real_t vy = attrib.vertices[3 * index.vertex_index + 1];
            tinyobj::real_t vz = attrib.vertices[3 * index.vertex_index + 2];

            vertices.push_back(vx);
            vertices.push_back(vy);
            vertices.push_back(vz);

            indices.push_back(indices.size());
        }
    }
}*/


// Function to import and display a .obj file object
void importAndDisplayObj(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open OBJ file." << std::endl;
        return;
    }

    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (prefix == "f") {
            Face face;
            char slash;
            for (int i = 0; i < 3; ++i) {
                iss >> face.vertexIndices[i] >> slash;
            }
            faces.push_back(face);
        }

    }

    file.close();

    // Now you can render the vertices and faces as desired
    // For demonstration purposes, print the vertices and faces
    for (const auto& vertex : vertices) {
        std::cout << "Vertex: " << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
    }

    for (const auto& face : faces) {
        std::cout << "Face: " << face.vertexIndices[0] << " " << face.vertexIndices[1] << " " << face.vertexIndices[2] << std::endl;
    }


    std::cout << "Number of vertices: " << vertices.size() << std::endl;
    std::cout << "Number of faces: " << faces.size() << std::endl;
}



void DrawTexturedCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength, const char* texturePath)
{
    //GLfloat halfSideLength = edgeLength * 0.5f / zoom;
    // Load the texture image using stb_image
    int width, height, channels;
    unsigned char* image = stbi_load(texturePath, &width, &height, &channels, STBI_rgb_alpha);
    if (!image)
    {
        std::cerr << "Failed to load texture image." << std::endl;
        return;
    }

    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
            {
                    // Front face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left

                    // Back face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left

                    // Left face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top front
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top back
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom back
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom back
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom front
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top front

                    // Right face
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top front
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top back
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom back
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom back
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom front
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top front

                    // Top face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // front left
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // back left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // back right
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // back right
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // front right
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // front left

                    // Bottom face
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // front left
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // back left
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // back right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // back right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // front right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // front left
            };

    GLfloat textureCoords[] =
            {
                    // Front face
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    1.0f, 0.0f, // bottom right
                    1.0f, 0.0f, // bottom right
                    0.0f, 0.0f, // bottom left
                    0.0f, 1.0f, // top left

                    // Back face
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    1.0f, 0.0f, // bottom right
                    1.0f, 0.0f, // bottom right
                    0.0f, 0.0f, // bottom left
                    0.0f, 1.0f, // top left

                    // Left face
                    0.0f, 1.0f, // top front
                    1.0f, 1.0f, // top back
                    1.0f, 0.0f, // bottom back
                    1.0f, 0.0f, // bottom back
                    0.0f, 0.0f, // bottom front
                    0.0f, 1.0f, // top front

                    // Right face
                    0.0f, 1.0f, // top front
                    1.0f, 1.0f, // top back
                    1.0f, 0.0f, // bottom back
                    1.0f, 0.0f, // bottom back
                    0.0f, 0.0f, // bottom front
                    0.0f, 1.0f, // top front

                    // Top face
                    0.0f, 1.0f, // front left
                    1.0f, 1.0f, // back left
                    1.0f, 0.0f, // back right
                    1.0f, 0.0f, // back right
                    0.0f, 0.0f, // front right
                    0.0f, 1.0f, // front left

                    // Bottom face
                    0.0f, 1.0f, // front left
                    1.0f, 1.0f, // back left
                    1.0f, 0.0f, // back right
                    1.0f, 0.0f, // back right
                    0.0f, 0.0f, // front right
                    0.0f, 1.0f  // front left
            };

    GLfloat normals[] =
            {
                    // Front face
                    0.0f, 0.0f, 1.0f, // top left
                    0.0f, 0.0f, 1.0f, // top right
                    0.0f, 0.0f, 1.0f, // bottom right
                    0.0f, 0.0f, 1.0f, // bottom right
                    0.0f, 0.0f, 1.0f, // bottom left
                    0.0f, 0.0f, 1.0f, // top left

                    // Back face
                    0.0f, 0.0f, -1.0f, // top left
                    0.0f, 0.0f, -1.0f, // top right
                    0.0f, 0.0f, -1.0f, // bottom right
                    0.0f, 0.0f, -1.0f, // bottom right
                    0.0f, 0.0f, -1.0f, // bottom left
                    0.0f, 0.0f, -1.0f, // top left

                    // Left face
                    -1.0f, 0.0f, 0.0f, // top front
                    -1.0f, 0.0f, 0.0f, // top back
                    -1.0f, 0.0f, 0.0f, // bottom back
                    -1.0f, 0.0f, 0.0f, // bottom back
                    -1.0f, 0.0f, 0.0f, // bottom front
                    -1.0f, 0.0f, 0.0f, // top front

                    // Right face
                    1.0f, 0.0f, 0.0f, // top front
                    1.0f, 0.0f, 0.0f, // top back
                    1.0f, 0.0f, 0.0f, // bottom back
                    1.0f, 0.0f, 0.0f, // bottom back
                    1.0f, 0.0f, 0.0f, // bottom front
                    1.0f, 0.0f, 0.0f, // top front

                    // Top face
                    0.0f, 1.0f, 0.0f, // front left
                    0.0f, 1.0f, 0.0f, // back left
                    0.0f, 1.0f, 0.0f, // back right
                    0.0f, 1.0f, 0.0f, // back right
                    0.0f, 1.0f, 0.0f, // front right
                    0.0f, 1.0f, 0.0f, // front left

                    // Bottom face
                    0.0f, -1.0f, 0.0f, // front left
                    0.0f, -1.0f, 0.0f, // back left
                    0.0f, -1.0f, 0.0f, // back right
                    0.0f, -1.0f, 0.0f, // back right
                    0.0f, -1.0f, 0.0f, // front right
                    0.0f, -1.0f, 0.0f  // front left
            };

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set up lighting properties
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Enable texture mapping
    glEnable(GL_TEXTURE_2D);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(image);

    // Enable depth testing and configure depth buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Clear the depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Draw the cube
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, textureCoords);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);

    // Disable depth testing
    glDisable(GL_DEPTH_TEST);

    // Disable lighting
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

}

void setupLighting()
{
    // Set up lighting properties
    GLfloat lightAmbient[] = { 0.2f, 0.0f, 0.0f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    // Set light position
    GLfloat lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };  // Light comes from the top-left direction

    // Set material properties
    GLfloat materialAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat materialDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat materialShininess = 1.0f;

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set light properties
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Set material properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
}

void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{


    GLfloat halfSideLength = edgeLength * 0.5f;

    GLfloat vertices[] =
            {
                    // Front face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left

                    // Back face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left

                    // Left face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top front
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top back
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom back
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom back
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom front
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top front

                    // Right face
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top front
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top back
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom back
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom back
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom front
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top front

                    // Top face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // front left
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // back left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // back right
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // back right
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // front right
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // front left

                    // Bottom face
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // front left
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // back left
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // back right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // back right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // front right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // front left
            };

    GLfloat colors[] =
            {
                    // Front face (red)
                    1.0f, 0.0f, 0.0f, 1.0f, // top left
                    1.0f, 0.0f, 0.0f, 1.0f, // top right
                    1.0f, 0.0f, 0.0f, 1.0f, // bottom right
                    1.0f, 0.0f, 0.0f, 1.0f, // bottom right
                    1.0f, 0.0f, 0.0f, 1.0f, // bottom left
                    1.0f, 0.0f, 0.0f, 1.0f, // top left

                    // Back face (green)
                    0.0f, 1.0f, 0.0f, 1.0f, // top left
                    0.0f, 1.0f, 0.0f, 1.0f, // top right
                    0.0f, 1.0f, 0.0f, 1.0f, // bottom right
                    0.0f, 1.0f, 0.0f, 1.0f, // bottom right
                    0.0f, 1.0f, 0.0f, 1.0f, // bottom left
                    0.0f, 1.0f, 0.0f, 1.0f, // top left

                    // Left face (blue)
                    0.0f, 0.0f, 1.0f, 1.0f, // top front
                    0.0f, 0.0f, 1.0f, 1.0f, // top back
                    0.0f, 0.0f, 1.0f, 1.0f, // bottom back
                    0.0f, 0.0f, 1.0f, 1.0f, // bottom back
                    0.0f, 0.0f, 1.0f, 1.0f, // bottom front
                    0.0f, 0.0f, 1.0f, 1.0f, // top front

                    // Right face (yellow)
                    1.0f, 1.0f, 0.0f, 1.0f, // top front
                    1.0f, 1.0f, 0.0f, 1.0f, // top back
                    1.0f, 1.0f, 0.0f, 1.0f, // bottom back
                    1.0f, 1.0f, 0.0f, 1.0f, // bottom back
                    1.0f, 1.0f, 0.0f, 1.0f, // bottom front
                    1.0f, 1.0f, 0.0f, 1.0f, // top front

                    // Top face (cyan)
                    0.0f, 1.0f, 1.0f, 1.0f, // front left
                    0.0f, 1.0f, 1.0f, 1.0f, // back left
                    0.0f, 1.0f, 1.0f, 1.0f, // back right
                    0.0f, 1.0f, 1.0f, 1.0f, // back right
                    0.0f, 1.0f, 1.0f, 1.0f, // front right
                    0.0f, 1.0f, 1.0f, 1.0f, // front left

                    // Bottom face (magenta)
                    1.0f, 0.0f, 1.0f, 1.0f, // front left
                    1.0f, 0.0f, 1.0f, 1.0f, // back left
                    1.0f, 0.0f, 1.0f, 1.0f, // back right
                    1.0f, 0.0f, 1.0f, 1.0f, // back right
                    1.0f, 0.0f, 1.0f, 1.0f, // front right
                    1.0f, 0.0f, 1.0f, 1.0f  // front left
            };

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(4, GL_FLOAT, 0, colors);
    glEnable(GL_BLEND);

    glEnable(GL_DEPTH_TEST); // Enable depth testing

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glFrontFace(GL_CCW);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glDisable(GL_DEPTH_TEST); // Disable depth testing

}




void DrawSecondCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f / zoom;
    static GLfloat rotation = 0.0f;
    rotation += 0.5f;

    glPushMatrix();
    glRotatef(rotationZ, 0, 0, 1);
    glTranslatef(centerPosX, centerPosY, centerPosZ);
    glRotatef(rotation, 1, 1, 1);
    glTranslatef(-centerPosX, -centerPosY, -centerPosZ);

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
    glPopMatrix();
}

void DrawThirdCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    GLfloat halfSideLength = edgeLength * 0.5f / zoom;
    static GLfloat rotation = 0.0f;
    rotation += 0.1f;

    glPushMatrix();
    glTranslatef(centerPosX, centerPosY, centerPosZ);
    glRotatef(rotation, 1, 1, 1);
    glTranslatef(-centerPosX, -centerPosY, -centerPosZ);

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
    glPopMatrix();
}