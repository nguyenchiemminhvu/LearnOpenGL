#version 330 core

uniform float sinTime;
uniform float cosTime;

uniform vec3 objectColor;
uniform vec3 lightColor;

varying vec3 vPos;
varying vec3 vNormal;

void main()
{
	vec4 FinalColor = vec4(0.0);

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;



	FinalColor = vec4(ambient, 1.0);
	gl_FragColor = FinalColor;
}