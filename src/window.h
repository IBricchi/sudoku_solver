#pragma once

#include <GLFW/glfw3.h>

#include <memory>
#include <string>

class Window;

using WindowPtr = std::unique_ptr<Window>; 

class Window{
public:
    Window(std::string&& title, int w, int h);
    
    bool should_close();
    void render_loop();
private:
    GLFWwindow* gl_window;
    std::string title;
    int w, h;
};
