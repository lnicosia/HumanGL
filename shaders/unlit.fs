#version 400 core

in vec2	TextCoord;

struct			Material
{
	sampler2D	diffuse;
	sampler2D	specular;
	float		shininess;
};

uniform Material material;

out vec4 FragColor;

void	main()
{
	FragColor = texture(material.diffuse, TextCoord);
}