
#include <glad/glad.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>



int main()
{
    std::cout<<"*** Init GLFW ***"<<std::endl;
    const int glfw_init_value = glfwInit();
    if( glfw_init_value != GLFW_TRUE ) {
        std::cerr<<"Failed to Init GLFW"<<std::endl;
        abort();
    }


    std::cout<<"*** Create window ***"<<std::endl;
    const int window_width  = 500;
    const int window_height = 500;
    const std::string title = "My Window";

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, title.c_str(), /*monitor*/ nullptr, /*share*/ nullptr);
    if( window==nullptr ) {
        std::cerr<<"Failed to create GLFW Window"<<std::endl;
        abort();
    }

    glfwMakeContextCurrent(window);

    std::cout<<"*** Init GLAD ***"<<std::endl;
    const int glad_init_value = gladLoadGL();
    if( glad_init_value == 0 ) {
        std::cerr<<"Failed to Init GLAD"<<std::endl;
        abort();
    }


    std::cout<<"OpenGL information: VENDOR      : "<<glGetString(GL_VENDOR)<<std::endl;
    std::cout<<"                    RENDERDER   : "<<glGetString(GL_RENDERER)<<std::endl;
    std::cout<<"                    VERSION     : "<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<"                    GLSL VERSION: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;


    // tag::shaders[]

    // ************************************************* //
    //             1 - Setup Shaders                     //
    // ************************************************* //

    std::cout<<"*** Setup Shader ***"<<std::endl;

    // ******************************** //
    // 1.1 Define vertex and fragment shader
    // ******************************** //
    //   Here GLSL code is hard-coded inline as strings
    const char* vertex_shader_txt = "                                      \n \
            #version 330 core                                              \n \
            layout (location = 0) in vec4 position;                        \n \
            void main()                                                    \n \
            {                                                              \n \
                gl_Position = position;                                    \n \
            }";
    const char* fragment_shader_txt = "                                    \n \
            #version 330 core                                              \n \
            out vec4 FragColor;                                            \n \
            void main()                                                    \n \
            {                                                              \n \
                FragColor = vec4(1.0, 0.0, 0.0, 1.0);                      \n \
            }";



    // ******************************** //
    // 1.2 Create shader program
    // ******************************** //

    // (Warning: the following code doesn't perform error checking)

    //  A. Compile each shader separately
    // ******************************************* //

    // Create identifiant for vertex and fragment shaders
    const GLuint vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    // Set source from the shader
    glShaderSource(vertex_shader, 1, &vertex_shader_txt, nullptr);
    // Compile the current shader (here vertex shader)
    glCompileShader(vertex_shader);

    // Set source from the shader
    glShaderSource(fragment_shader, 1, &fragment_shader_txt, nullptr);
    // Compile the current shader (here fragment shader)
    glCompileShader(fragment_shader);

    //  B. Link shaders into shader program
    // ******************************************* //

    // Create identifiant for shader program
    const GLuint shader = glCreateProgram();

    // Attach vertex and fragment shader before linking
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    // Perform the link of the two shaders into a program
    glLinkProgram(shader);

    // Compiled shaders can be safely deleted
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // end::shaders[]


    // tag::send_gpu_data[]

    // ************************************************* //
    //           2 - Sending data to GPU                 //
    // ************************************************* //

    std::cout<<"*** Setup Data ***"<<std::endl;

    // 2.1 Setup contiguous array of floating point value
    // ******************************************* //
    //     Here the coordinates of the vertices position
    const std::vector<GLfloat> position = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // 2.2 Create VBO - Send data to GPU
    // ******************************************* //

    GLuint vbo = 0;
    // Create an empty VBO identifiant
    glGenBuffers(1, &vbo);
    // Activate the VBO designated by the variable "vbo"
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Send data to GPU: Fill the currently designated VBO with the buffer of data passed as parameter
    glBufferData(GL_ARRAY_BUFFER, position.size()*sizeof(GLfloat), &position[0], GL_STATIC_DRAW );
    // Good practice to set the current VBO to 0 (=disable VBO) after its use
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // 2.3 Create VAO - Relation between VBO organization and input variables of shaders
    // ******************************************* //
    // In this case, we have only one VBO containing triplets of floats, and used as the "layout 0" in the shader
    GLuint vao = 0;
    // Create an empty VAO identifiant
    glGenVertexArrays(1,&vao);
    // Activate the VAO designated by the variable "vao"
    glBindVertexArray(vao);
    // Indicate the VBO to parameterize
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Activate the use of the variable at index layout=0 in the shader
    glEnableVertexAttribArray( 0 );
    // Define the memory model of the current VBO: here contiguous triplet of floating values (x y z) at index layout=0 in the shader
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
    // As a good practice, disable VBO and VAO after their use
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // end::send_gpu_data[]




    // ******************************** //
    // Main loop
    // ******************************** //

    std::cout<<"*** Start GLFW loop ***"<<std::endl;
    while( !glfwWindowShouldClose(window) ) {

        // tag::displaying_data[]

        // ************************************************* //
        //           3 - Displaying Data                     //
        // ************************************************* //

        glUseProgram(shader);             // Activate shader program
        glBindVertexArray(vao);           // Activate attributes for the drawing
        glDrawArrays(GL_TRIANGLES, 0, 3); // Draw 3 vertices
        glBindVertexArray(0);
        glUseProgram(0);

        // end::displaying_data[]



        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    std::cout<<"*** Terminate GLFW loop ***"<<std::endl;


    glfwTerminate();

    return 0;
}



