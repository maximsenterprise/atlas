#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;

uniform mat4 MVP;
out vec4 fragmentColor;

void main(){
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1); 
    // gl_Position.xyz =  vertexPosition_modelspace;
    // gl_Position.w = 1.0;
    fragmentColor = vertexColor;
}

