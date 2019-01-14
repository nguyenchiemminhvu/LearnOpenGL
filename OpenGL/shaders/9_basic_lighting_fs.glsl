#version 330 core

uniform float sinTime;
uniform float cosTime;

uniform vec3 objectColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

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

	FinalColor = vec4(ambient + diffuse, 1.0);
	gl_FragColor = FinalColor;
}