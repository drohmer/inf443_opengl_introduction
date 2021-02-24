
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
GLuint vbo_index = 0;         // Buffer storing indices of triangles
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
    // ********************************* //
    // Create data
    // ********************************* //

    // tag::indexing_declaration[]

    // Geometry (vertex position)
    const std::vector<GLfloat> position = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    // Connectivity (triangle index)
    const std::vector<GLuint> index = {
         0, 1, 2,
         0, 2, 3
    };

    // end::indexing_declaration[]


    // Colors
    const std::vector<GLfloat> color = {
         0.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 1.0f, 0.0f,
         0.0f, 1.0f, 0.0f
    };

    // ********************************* //
    // Send data on the GPU
    // ********************************* //

    // tag::indexing_vbo[]

    // Fill VBO for position
    GLuint vbo_position = 0;
    glGenBuffers(1, &vbo_position);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
    glBufferData(GL_ARRAY_BUFFER, position.size()*sizeof(GLfloat), &position[0], GL_STATIC_DRAW );
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Fill VBO for index
    glGenBuffers(1, &vbo_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size()*sizeof(GLuint), &index[0], GL_STATIC_DRAW );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // end::indexing_vbo[]

    // Fill VBO for color
    GLuint vbo_color = 0;
    glGenBuffers(1, &vbo_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
    glBufferData(GL_ARRAY_BUFFER, color.size()*sizeof(GLfloat), &color[0], GL_STATIC_DRAW );
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // ********************************* //
    // Set shader attributes
    // ********************************* //

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    // position at layout 0
    glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    // color at layout 1
    glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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

    // tag::indexing_draw[]

    // Draw call
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);
    glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, nullptr);

    // end::indexing_draw[]

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}


