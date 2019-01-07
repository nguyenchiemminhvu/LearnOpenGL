#version 330 core

varying vec2 vUV;

uniform float sinTime;
uniform float cosTime;

uniform sampler2D tex;

void main()
{
	gl_FragColor = texture2D(tex, vUV);
}