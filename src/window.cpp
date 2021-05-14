#include "window.h"

#include <glad/glad.h>

#include <iostream>

static bool glfw_init = false;
static bool glad_init = false;

static void error_callback(int error, const char* description)
{
    std::cerr << "[GLFW] Error: " << description << std::endl;
}

static bool glfw_initialize(){
    if(!glfwInit()){
        std::cerr << "[GLFW] Error: Unable to intialize glfw." << std::endl;
        return false;
    }
    
    // setup error callback
    glfwSetErrorCallback(error_callback);

    return true;
}

Window::Window(std::string&& title, int w, int h):
    title(title), w(w), h(h)
{
    if(!glfw_init){
        if(!glfw_initialize()){
            gl_window = nullptr;
            return;
        }
        glfw_init = true;
    }
    
    // initialize window
    gl_window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
    if(!gl_window){
        std::cerr << "[GLFW] Error: Unable to create widnow." << std::endl;
        return;
    }

    // make window current context
    glfwMakeContextCurrent(gl_window);

    // intialize glad
    if(!glad_init){
        if(!gladLoadGL()){
            std::cerr << "[Window] Error: Unable to initialize glad." << std::endl;
            return;
        }
        glad_init = true;
    }
}

bool Window::should_close(){
    return glfwWindowShouldClose(gl_window);
}

void Window::render_loop(){
    // render here
    glClear(GL_COLOR_BUFFER_BIT);

    // draw buffer
    glDrawArrays(GL_TRIANGLES, 0, 3);    

    // swap front and back buffers
    glfwSwapBuffers(gl_window);

    // poll for process and events
    glfwPollEvents();
}