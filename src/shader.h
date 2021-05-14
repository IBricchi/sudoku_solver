#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <vector>

class Shader;

using ShaderPtr = std::unique_ptr<Shader>;

class Shader{
public:
    enum class Type{
        none = -1,
        vertex,
        fragment,
        max
    };

    Shader();
    Shader(Type type);
    Shader(std::string&& src, Type type);

    static std::tuple<ShaderPtr, ShaderPtr> load_simple_format(std::string&& src);
    static std::vector<ShaderPtr> load_formatted(std::string&& src);

    Type get_type() const;
    unsigned int get_gl_type() const;
    const char* get_type_name() const;
    const char* get_data() const;

    void set_data(std::stringstream& ss);

    int compile();
    void attach(unsigned int program);
    void drop();

    ~Shader();

private:
    Type type;
    std::string data;

    int gl_id;
    
    void data_from_file(std::string& src);
};
