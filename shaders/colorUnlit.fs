#version 400 core

in vec2	TextCoord;

uniform	sampler2D	texture_diffuse0;
uniform vec4		baseColor;

out vec4 FragColor;

void main()
{
	FragColor = baseColor;
}
