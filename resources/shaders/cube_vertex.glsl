#version 460 core

in vec3 position;

layout(location = 0)uniform mat4 perspective;
layout(location = 1)uniform mat4 view;
layout(location = 2)uniform mat4 transform;

void main(){

    
    gl_Position = perspective * view * transform * vec4(position,1.0);
}