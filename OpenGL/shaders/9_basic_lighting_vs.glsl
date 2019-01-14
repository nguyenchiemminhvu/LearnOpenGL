#version 330 core

attribute vec3 aPos;
attribute vec3 aNormal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

varying vec3 vPos;
varying vec3 vNormal;

void main()
{
	gl_Position = Projection * View * Model * vec4(aPos, 1.0);

	vPos = vec3(Model * vec4(aPos, 1.0));
	vNormal = aNormal;
}