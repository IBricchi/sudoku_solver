#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <spdlog/spdlog.h>

#include "logger.h"
#include "window.h"
#include "shader.h"

int main(){
    Logger::init("SS");

    LOG_INFO("Hello World!");
    LOG_WARN("Hello World!");
    LOG_ERR("Hello World!");
    LOG_CRIT("Hello World!");

    Window window("Hello World", 640, 480);

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
    while(!window.should_close()){
        window.render_loop();
    }

    glDeleteProgram(shader);

    // terminate windows
    glfwTerminate();
}