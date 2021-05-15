#include "shader.h"
#include "logger.h"

#include <glad/glad.h>

#include <optional>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader():
    type(Type::none),
    data("")
{}

Shader::Shader(Type type):
    type(type),
    data("")
{}

Shader::Shader(std::string&& src, Type type):
    type(type)
{
    data_from_file(src);
}

void Shader::data_from_file(std::string& src){
    std::ifstream shaderFile(src);

    if(!shaderFile){
        LOG_ERR("Unable to open file '{}}'.", src);
        return;
    }
    
    std::stringstream ss;

    std::string line;

    while(getline(shaderFile, line)){
        ss << line << std::endl;
    }

    data = ss.str();
}

std::tuple<ShaderPtr, ShaderPtr> Shader::load_simple_format(std::string&& src){
    ShaderPtr vertexShader = std::make_unique<Shader>(Type::vertex);
    ShaderPtr fragmentShader = std::make_unique<Shader>(Type::fragment);

    std::ifstream shaderFile(src);

    if(!shaderFile){
        LOG_ERR("Unable to open file '{}'.", src);
        return {nullptr, nullptr};
    }

    std::string line;
    std::stringstream ss[static_cast<int>(Type::max)];
    Type current_type = Type::none;
    int line_num = 0;
    bool has_specified = false;
    bool has_warned = false;

    while(getline(shaderFile, line)){
        line_num++;
        if(line.find("#shader") != std::string::npos){
            has_specified = true;
            has_warned = false;
            if(line.find("vertex") != std::string::npos){
                current_type = Type::vertex;
            }
            else if(line.find("fragment") != std::string::npos){
                current_type = Type::fragment;
            }
            else{
                current_type = Type::none;
                LOG_WARN("<File: {}, Line: {}> Unknown shader type specified. Expected vertex or fragment.", src, line);
                has_warned = true;
            }
        }
        else if(!has_specified && !has_warned){
            LOG_WARN("<File: {}, Line: {}> Shader type not specified. Expected vertex or fragment.", src, line);
            has_warned = true;
        }
        else if(current_type != Type::none){
            ss[static_cast<int>(current_type)] << line << std::endl;
        }
    }

    vertexShader->data = ss[0].str();
    fragmentShader->data = ss[1].str();

    return {std::move(vertexShader), std::move(fragmentShader)};
}

Shader::Type Shader::get_type() const{
    return type;
}

unsigned int Shader::get_gl_type() const{
    switch (type)
    {
    case Type::vertex:
        return GL_VERTEX_SHADER;
    case Type::fragment:
        return GL_FRAGMENT_SHADER;
    default:
        return 0;
    }
}

const char* Shader::get_type_name() const{
    switch (type)
    {
    case Type::vertex:
        return "vertex";
    case Type::fragment:
        return "fragment";
    default:
        return "unkown";
    }
}

const char* Shader::get_data() const{
    return data.c_str();
}

void Shader::set_data(std::stringstream& ss){
    data = ss.str();
}

int Shader::compile(){
    gl_id = glCreateShader(this->get_gl_type());
    const char* src = data.c_str();
    glShaderSource(gl_id, 1, &src, nullptr);
    glCompileShader(gl_id);

    int result;
    glGetShaderiv(gl_id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(gl_id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(gl_id, length, &length, message);
        LOG_ERR("Failed to compile {} shader. OpenGL error:\n {}", this->get_type_name(), message);
        glDeleteShader(gl_id);
    }

    return result;
}

void Shader::attach(unsigned int program){
    glAttachShader(program, gl_id);
}

void Shader::drop(){
    glDeleteShader(gl_id);
}

Shader::~Shader(){
    glDeleteShader(gl_id);
}