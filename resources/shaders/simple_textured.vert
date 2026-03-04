#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 aNormal;

out vec2 vUV;
out vec4 vNormal;

void main()
{
    vUV = aUV;
    vNormal = model * vec4(aNormal, 1.0f);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}