#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;

uniform mat4 Model2World;
uniform mat4 lightSpaceMatrix;

out vec2 fragment_textcoord;

void main(){

  gl_Position = lightSpaceMatrix * Model2World * vec4(position, 1.0);

}