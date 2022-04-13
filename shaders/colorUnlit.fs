#version 400 core

in vec2	TextCoord;

uniform	sampler2D	texture_diffuse0;
uniform vec3		baseColor;

out vec4 FragColor;

void main()
{
	FragColor = vec4(baseColor, 1.0f);
}
