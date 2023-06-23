#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <fstream>
#include "stb_image.h"
#include "quaternion.h"
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


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void DrawTexturedCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength, const char* texturePath);
void setupLighting();
void importAndDisplayObj(const std::string& filename);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat rotationZ = 0.0f;
GLfloat cameraX = 0.0f;
GLfloat cameraY = 0.0f;
GLfloat cameraZ = -500.0f;
GLfloat zoomSpeed = 0.1f;

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
        glTranslatef(halfScreenWidth, halfScreenHeight, cameraZ * zoom);
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
    zoom += yoffset * zoomSpeed;
    if (zoom < 0.1f) // Limitez le zoom minimum
        zoom = 0.1f;
}






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



