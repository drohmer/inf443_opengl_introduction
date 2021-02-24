
// Include for GLFW headers - library handling the window
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    // Initialize GLFW
    //  This step is required before creating the window
    glfwInit();

    // Create a new Window of size 500x500 with title "My Window"
    // The two last parameters are
    //   - the monitor for full screen mode (or nullptr for windowed mode in this case)
    //   - another pointer to a window in the case where ressources are shared (or nullptr to not share ressources).
    // The function returns a pointer to the newly created window (or nullptr in case of error).
    GLFWwindow* window = glfwCreateWindow(500, 500, "My Window", nullptr, nullptr);

    if( window==nullptr ) {
        std::cerr<<"GLFW Failed to create a Window"<<std::endl;
        glfwTerminate();
        exit(1);
    }

    // User defined loop
    // This loop will be active until the user close the window
    while( !glfwWindowShouldClose(window) ) {
        glfwSwapBuffers(window); // Double buffering (will be used to avoid flickering when animating a scene)
        glfwPollEvents();        // Handle GLFW events (ex. mouse clicks, etc)
    }

    glfwTerminate(); // Close the GLFW Window

    return 0;
}
