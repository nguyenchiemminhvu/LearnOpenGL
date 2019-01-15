#version 330 core

struct Material
{
	sampler2D diffuse;
	vec3 specular;

	float shininess;
};

uniform Material object;

uniform float sinTime;
uniform float cosTime;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 eyePos;

varying vec3 vPos;
varying vec3 vNormal;
varying vec2 vUV;

void main()
{
	vec4 FinalColor = vec4(0.0);

	vec3 ambient;
	float ambientStrength = 0.1;
	ambient = ambientStrength * lightColor * texture2D(object.diffuse, vUV).rgb;

	vec3 diffuse;
	vec3 lightDir = normalize(vPos - lightPos);
	float diff = max(dot(-lightDir, vNormal), 0.0);
	diffuse = diff * lightColor * texture2D(object.diffuse, vUV).rgb;

	vec3 specular;
	vec3 fragToEye = normalize(eyePos - vPos);
	vec3 reflectDir = reflect(lightDir, vNormal);
	float spec = pow(max(dot(reflectDir, fragToEye), 0.0), 128.0);
	specular = spec * lightColor * object.specular;

	FinalColor = vec4(ambient + diffuse + specular, 1.0);
	gl_FragColor = FinalColor;
}