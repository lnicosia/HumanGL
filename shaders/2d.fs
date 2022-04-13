#version 400 core

in vec2 TexCoords;
out vec4    FragColor;

uniform sampler2D   image;
uniform vec4    color;

void    main()
{
    //FragColor = color * texture(image, TexCoords).r;
    FragColor = color * texture(image, TexCoords);
}
