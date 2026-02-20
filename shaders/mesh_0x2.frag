#version 330 core
in vec2 vUV;
in vec4 vNormal;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    vec4 tex = texture(uTexture, vUV);
    FragColor = vec4(tex.rgb, tex.a);
}