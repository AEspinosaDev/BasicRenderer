#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm.hpp>


#define ASSERT(x) if (!(x))  __debugbreak();
#define GLcall(x) GLclearError();\
 x;\
ASSERT(GLlogCall(#x, __FILE__, __LINE__))


    extern const std::string shaderPath = "Resources/Shaders/";

    extern const std::string texturePath = "Resources/Textures/";

    extern const std::string modelPath = "Resources/Models/";


    void GLclearError()
    {
        while (glGetError() != GL_NO_ERROR);

    }

    bool GLlogCall(const char* function, const char* file, int line)
    {
        while (GLenum error = glGetError()) {
            std::cout << "[OpenGL Error] (" << error << ")" << function << " " << file << ":" << line << std::endl;
            return false;
        }
        return true;

    }


