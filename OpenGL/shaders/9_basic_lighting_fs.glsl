#version 330 core

uniform float sinTime;
uniform float cosTime;

uniform vec3 objectColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 eyePos;

varying vec3 vPos;
varying vec3 vNormal;

void main()
{
	vec4 FinalColor = vec4(0.0);

	vec3 ambient;
	float ambientStrength = 0.1;
	ambient = ambientStrength * lightColor;

	vec3 diffuse;
	vec3 lightDir = normalize(vPos - lightPos);
	float diff = max(dot(-lightDir, vNormal), 0.0);
	diffuse = diff * lightColor * objectColor;

	vec3 specular;
	vec3 fragToEye = normalize(eyePos - vPos);
	vec3 reflectDir = reflect(lightDir, vNormal);
	float spec = pow(max(dot(reflectDir, fragToEye), 0.0), 128.0);
	specular = spec * lightColor * objectColor;

	FinalColor = vec4(ambient + diffuse + specular, 1.0);
	gl_FragColor = FinalColor;
}