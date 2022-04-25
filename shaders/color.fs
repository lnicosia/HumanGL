#version 400 core

in vec2	TextCoord;
in vec3	Normal;
in vec3 FragPos;

struct			Material
{
	sampler2D	diffuse;
	sampler2D	specular;
	float		shininess;
};

struct		DirLight
{
	vec3	dir;

	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
};

struct		PointLight
{
	vec3	pos;

	float	constant;
	float	linear;
	float	quadratic;

	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
};

uniform Material material;

uniform DirLight	dirLight;
#define MAX_POINT_LIGHTS 4
uniform PointLight	pointLights[MAX_POINT_LIGHTS];

uniform vec3	cameraPos;
uniform vec4	baseColor;

out vec4 FragColor;

vec3	computeDirLight(DirLight light, vec3 normal, vec3 cameraDir)
{
	vec3	lightDir = normalize(-light.dir);

	//	Ambient
	vec3	ambient = light.ambient * vec3(texture(material.diffuse, TextCoord));

	//	Diffuse
	float	diff = max(dot(normal, lightDir), 0.0);
	vec3	diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TextCoord));

	//	Specular
	vec3	reflectDir = reflect(-lightDir, normal);
	float	spec = pow(max(dot(cameraDir, reflectDir), 0), material.shininess);
	vec3	specular = light.specular * spec * vec3(texture(material.specular, TextCoord));

	return (ambient + diffuse + specular);
}

vec4	computePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 cameraDir)
{
	vec3	lightDir = normalize(light.pos - FragPos);

	//	Ambient
	vec3	ambient = light.ambient * vec3(texture(material.diffuse, TextCoord));

	//	Diffuse
	float	diff = max(dot(normal, lightDir), 0.0);
	vec4	diffuse = vec4(light.diffuse, 1.0) * diff * baseColor;

	//	Specular
	vec3	reflectDir = reflect(-lightDir, normal);
	float	spec = pow(max(dot(cameraDir, reflectDir), 0), material.shininess);
	vec3	specular = light.specular * spec * vec3(texture(material.specular, TextCoord));

	float	dist = length(light.pos - fragPos);
	float	attenuation = 1.0 /
		(light.constant + light.linear * dist + light.quadratic * dist * dist);

	return (diffuse);
}

void main()
{
	vec3 norm = normalize(Normal);
	vec3 cameraDir = normalize(cameraPos - FragPos);

	//No directional light for now
	//vec3 res = computeDirLight(dirLight, norm, cameraDir);
	vec4 res = vec4(0);
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
		res += computePointLight(pointLights[i], norm, FragPos, cameraDir);

	FragColor = res;
	//FragColor = texture(material.diffuse, TextCoord);

}
