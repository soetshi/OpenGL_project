#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

class Texture {
public:
    unsigned int getTexture1() {
        return texture1;
    }

    Texture() {
        glGenTextures(1, &texture1);
    }

    ~Texture() {
        glDeleteTextures(1, &texture1);
    }

    void loadTexture(const char* path) {
        glBindTexture(GL_TEXTURE_2D, texture1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glActiveTexture(GL_TEXTURE0);

        int twidth, theight, channels;

        auto* data = stbi_load(path, &twidth, &theight, &channels, STBI_rgb_alpha);

        glBindTexture(GL_TEXTURE_2D, texture1);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, theight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);
    }

private:
    unsigned int texture1;
};