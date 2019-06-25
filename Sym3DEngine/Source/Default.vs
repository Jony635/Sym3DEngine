#version 150

attribute mat4 projectionMatrix;
attribute mat4 modelViewMatrix;
attribute vec3 vertexPosition;

void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(vertexPosition, 1.0);
}