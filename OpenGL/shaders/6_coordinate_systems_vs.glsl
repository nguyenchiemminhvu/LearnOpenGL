#version 330 core

attribute vec3 aPos;
attribute vec2 aUV;

varying vec2 vUV;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	vUV = aUV;
}