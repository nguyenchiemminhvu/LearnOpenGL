#version 330 core

uniform float sinTime;
uniform float cosTime;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	gl_FragColor = vec4(objectColor * lightColor, 1.0);
}