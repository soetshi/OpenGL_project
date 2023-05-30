#include <GLFW/glfw3.h>
#include <iostream>

struct Color3f {
    float r, g, b;
    Color3f() {}
    Color3f(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
};

struct Point2f {
    float x, y;
    Point2f() {}
    Point2f(float _x, float _y) : x(_x), y(_y) {}
};

struct Vertex {
    Point2f position;
    Color3f color;
    Vertex() {}
    Vertex(Point2f _position, Color3f _color) : position(_position), color(_color) {}
};

struct Application {
    int m_width = 1280;
    int m_height = 720;

    inline void setSize(int width, int height) {
        m_width = width;
        m_height = height;
    }

    bool initialize() {
        std::cout << "Pilote : " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "OpenGL : " << glGetString(GL_RENDERER) << std::endl;
        return true;
    }

    void deinitialized() {}

    void render() {
        glEnable(GL_SCISSOR_TEST);

        glViewport(0, 0, m_width, m_height);

        glScissor(0, 0, m_width, m_height);

        glClearColor(0.5f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDisable(GL_SCISSOR_TEST);

        Vertex vertices[3] = {
                Vertex(Point2f(-0.8f, -0.8f), Color3f(0.f, 0.f, 0.f)),
                Vertex(Point2f(0.8f, -0.8f), Color3f(0.5f, 0.5f, 0.5f)),
                Vertex(Point2f(0.f, 0.8f), Color3f(1.f, 1.f, 1.f))
        };

        glBegin(GL_TRIANGLES);

        for (int i = 0; i < 3; ++i) {
            glColor3f(vertices[i].color.r, vertices[i].color.g, vertices[i].color.b);
            glVertex2f(vertices[i].position.x, vertices[i].position.y);
        }

        glEnd();

        glFlush();
    }
};

int main(void)
{
    Application app;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    app.initialize();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        app.setSize(width, height);

        app.render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    app.deinitialized();

    glfwTerminate();
    return 0;
}