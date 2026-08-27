#version 120

uniform mat4 wvpMat;
uniform vec4 diffuseColor;

attribute vec4 vertex;
attribute float uv1;
attribute vec4 colour;
attribute vec4 blendIndices;

varying vec4 vColor;
varying vec2 vTexCoord;
varying float vDepth;

void main()
{
	vec4 iPosition = vertex;
	vec2 iTexCoord = blendIndices.xy / 160.0;
	vec4 iColor = colour.bgra * diffuseColor;
	float heightOffset = uv1;
	iPosition.y = heightOffset;

	gl_Position = wvpMat * iPosition;
	vColor = iColor;
	vTexCoord = iTexCoord;
	vDepth = gl_Position.z;
}
