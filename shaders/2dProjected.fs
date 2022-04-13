#version 400 core

in vec2 TexCoords;

uniform sampler2D image;
uniform vec3 color;

out vec4 FragColor;

void	main()
{
	FragColor = texture(image, TexCoords);
	//FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
