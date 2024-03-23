#version 460 core

in vec3 position;

layout(location = 0)uniform mat4 perspective;
layout(location = 1)uniform mat4 view;
//TODO CHANGE TO A UBO OR SBO LATER <- uniform hardware limit is less than 256
layout(location = 2)uniform mat4 transform[128];

void main(){

    gl_Position = perspective * view * transform[gl_DrawID] * vec4(position,1.0);
}