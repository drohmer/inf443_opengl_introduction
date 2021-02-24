

#include "../external/glad/include/glad/glad.hpp" // glad.h should be included before glfw or any OpenGL related include

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

int main()
{
    glfwInit();

    // Indicate to GLFW to setup context compatible with OpenGL 3.3 core profile
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "My Window", nullptr, nullptr);

    if( window==nullptr ) {
        std::cerr<<"GLFW Failed to create a Window"<<std::endl;
        glfwTerminate();
        exit(1);
    }

    // Enable the window to handle OpenGL Context
    glfwMakeContextCurrent(window);

    // Load OpenGL Functions
    gladLoadGL();

    // Print OpenGL Information
    std::cout << "OpenGL information: VENDOR      : " << glGetString(GL_VENDOR)   <<std::endl;
    std::cout << "                    RENDERDER   : " << glGetString(GL_RENDERER) <<std::endl;
    std::cout << "                    VERSION     : " << glGetString(GL_VERSION)  <<std::endl;
    std::cout << "                    GLSL VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;

    while( !glfwWindowShouldClose(window) ) {
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
