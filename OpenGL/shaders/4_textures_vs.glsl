#version 330 core

attribute vec3 aPos;
attribute vec3 aColor;

varying vec4 vColor;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	vColor = vec4(aColor, 1.0);
}