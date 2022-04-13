#version 400 core

in vec2	TextCoord;
flat in ivec4 boneIDs;
in vec4	Weights;

uniform	sampler2D	texture_diffuse0;
uniform vec3		baseColor;
uniform int			selectedBone;

out vec4 FragColor;

void main()
{
	for (int i = 0; i < 4; i++)
	{
		if (boneIDs[i] == selectedBone)
		{
			if (Weights[i] >= 0.7)
				FragColor = vec4(1.0f, 0.0f, 0.0f, 0.0f) * Weights[i];
			else if (Weights[i] >= 0.4 && Weights[i] < 0.7)
				FragColor = vec4(1.0f, 1.0f, 0.0f, 0.0f) * Weights[i];
			else if (Weights[i] >= 0.1)
				FragColor = vec4(0.0f, 1.0f, 0.0f, 0.0f) * Weights[i];
			FragColor.w = 1.0f;
			return ;
		}
	}
	FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
