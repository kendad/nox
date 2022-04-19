#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D color_texture;
uniform sampler2D wood_texture;

uniform vec3 color;

void main()
{    
	FragColor=vec4(color,1.0f);
}