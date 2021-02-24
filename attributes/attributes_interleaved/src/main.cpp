
#include "window_helper.hpp"
#include "opengl_helper.hpp"

#include <iostream>
#include <vector>
#include <array>
#include <cmath>


// ************************************ //
//          Global variables
// ************************************ //
GLuint shader_program = 0;    // Id of the shader used to draw the data (only one shader)
GLuint vao = 0;               // Set of attributes to draw the data (only one attribute)
int counter_drawing_loop = 0; // Counter to handle the animation


// ************************************ //
//          Function headers
// ************************************ //
void load_data();             // Load and send data to the GPU once
void draw_data();             // Drawing calls within the animation loop


/** Main function, call the general functions and setup the animation loop */
int main()
{
    std::cout<<"*** Init GLFW ***"<<std::endl;
    glfw_init();

    std::cout<<"*** Create window ***"<<std::endl;
    auto window = glfw_create_window(500,500,"My Window");
    glfwMakeContextCurrent(window);

    std::cout<<"*** Init GLAD ***"<<std::endl;
    glad_init();


    print_opengl_information();

    std::cout<<"*** Setup Data ***"<<std::endl;
    load_data();

    std::cout<<"*** Compile Shader ***"<<std::endl;
    shader_program = create_shader_program("shaders/vertex_shader.glsl","shaders/fragment_shader.glsl");

    std::cout<<"*** Start GLFW loop ***"<<std::endl;
    while( !glfwWindowShouldClose(window) ) {

        draw_data();

        ++counter_drawing_loop;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    std::cout<<"*** Terminate GLFW loop ***"<<std::endl;

}



/** Create (or load) data and send them to GPU */
void load_data()
{
    // tag::load_data[]

    // ********************************* //
    // Create data
    // ********************************* //

    const std::vector<GLfloat> vertex_data = {
        -0.5f, -0.5f, 0.0f, // position 0
         1.0f, 0.0f, 0.0f,  // color 0 - red
         0.5f, -0.5f, 0.0f, // position 1
         0.0f, 1.0f, 0.0f,  // color 1 - green
         0.0f,  0.5f, 0.0f, // position 2
         0.0f, 0.0f, 1.0f   // color 2 - blue
    };


    // ********************************* //
    // Send data on the GPU
    // ********************************* //

    // Fill VBO for position and color
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_data.size()*sizeof(GLfloat), &vertex_data[0], GL_STATIC_DRAW );
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // ********************************* //
    // Set shader attributes
    // ********************************* //

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // position at layout 0
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 2*3*sizeof(GLfloat), nullptr );

    // color at layout 1
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 2*3*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)) );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // end::load_data[]
}


/** Function called within the animation loop.
    Setup uniform variables and drawing calls  */
void draw_data()
{

    // ******************************** //
    // Clear screen
    // ******************************** //
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    // ******************************** //
    // Draw data
    // ******************************** //
    glUseProgram(shader_program);
    glBindVertexArray(vao);

    // Draw call
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glUseProgram(0);
}


