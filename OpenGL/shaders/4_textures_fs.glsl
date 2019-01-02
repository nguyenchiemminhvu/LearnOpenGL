#version 330 core

varying vec4 vColor;

uniform float sinTime;
uniform float cosTime;

void main()
{
	gl_FragColor = vec4(vColor.r * cosTime, 
						vColor.g * sinTime, 
						vColor.b * cosTime, 
						vColor.a);
}