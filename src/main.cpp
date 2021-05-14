#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <tuple>
#include <sstream>

#include "shader.h"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main(){
    GLFWwindow* window;

    // initialize opengl
    if(!glfwInit()){
        return -1;
    }

    // setup error callback
    glfwSetErrorCallback(error_callback);

    // initialize window
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(!window){
        return -1;
    }

    // make window current context
    glfwMakeContextCurrent(window);

    // setup glad
    gladLoadGL();

    // buffer data
    float positions[] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    // setup opengl buffer
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

    auto[vertexShader, fragmentShader] = Shader::load_simple_format("src/basic.glsl");
    vertexShader->compile();
    fragmentShader->compile();

    unsigned int shader = glCreateProgram();
    vertexShader->attach(shader);
    fragmentShader->attach(shader);    
    
    glLinkProgram(shader);
    glValidateProgram(shader);
    glUseProgram(shader);

    // run loop until closed
    while(!glfwWindowShouldClose(window)){
        
        // render here
        glClear(GL_COLOR_BUFFER_BIT);

        // draw buffer
        glDrawArrays(GL_TRIANGLES, 0, 3);    

        // swap front and back buffers
        glfwSwapBuffers(window);

        // poll for process and events
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    // terminate windows
    glfwTerminate();
}