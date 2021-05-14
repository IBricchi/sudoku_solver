#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main(){
   gl_Position = position;
}

#shader fragment
#version 330 core

#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 position;
layout(location = 0) out vec4 color;

void main(){
   color = vec4(0.9, 0.08, 0.77,1.0);
}
