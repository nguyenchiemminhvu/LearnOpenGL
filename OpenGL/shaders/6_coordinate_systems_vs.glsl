#version 330 core

attribute vec3 aPos;
attribute vec2 aUV;

varying vec2 vUV;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = Projection * View * Model * vec4(aPos, 1.0);
	vUV = aUV;
}