#version 120

uniform mat4 wvpMat;
uniform mat4 worldViewMat;
#if defined(SHADOWRECEIVER)
uniform mat4 texWorldViewProj1;
#if defined(PSSM_ENABLED)
uniform mat4 texWorldViewProj2;
uniform mat4 texWorldViewProj3;
#endif
#endif

#if defined(VERTEX_LIGHTING)
uniform vec4 lightPosition[MAX_LIGHTS];
uniform vec4 lightDiffuse[MAX_LIGHTS];
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
uniform vec4 lightSpecular[MAX_LIGHTS];
uniform float materialShininess;
#endif
#endif

attribute vec4 vertex;
attribute vec4 colour;
attribute float uv1;
attribute vec4 blendIndices;
#if !defined(VERTEX_LIGHTING) && defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
attribute vec3 tangent;
#endif

varying vec4 vColor;
#if defined (VERTEX_LIGHTING)
varying vec3 vLightResult;
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
varying vec3 vSpecularResult;
#endif
#endif
varying vec2 vTexCoord;
#if !defined(VERTEX_LIGHTING)
varying vec3 vViewNormal;
#if defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
varying vec3 vViewTangent;
#endif
varying vec3 vViewPosition;
#endif
varying float vDepth;
#if defined(SHADOWRECEIVER)
varying vec4 vLightSpacePos1;
#if defined(PSSM_ENABLED)
varying vec4 vLightSpacePos2;
varying vec4 vLightSpacePos3;
#endif
#endif

vec3 safe_normalize(in vec3 v)
{
	float lenSq = dot(v, v);
	return (lenSq > 1e-8) ? v * inversesqrt(lenSq) : vec3(0.0, 0.0, 0.0);
}


void main()
{
	vec4 iPosition = vertex;
	vec2 nNormal = (blendIndices.zw - vec2(127.0, 127.0)) / vec2(127.0, 127.0);
	vec3 iNormal = vec3(nNormal.x, sqrt(max(1.0 - dot(nNormal, nNormal), 0.0)), nNormal.y);
	vec2 iTexCoord = (blendIndices.xy + vec2(0.5, 0.5)) / 160.0;
#if defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
	vec3 iTangent = tangent;
#endif
	vec4 iColor = colour.bgra;
	float heightOffset = uv1;
	iPosition.y = heightOffset;

	gl_Position = wvpMat * iPosition;
	vTexCoord = iTexCoord;

#if defined(VERTEX_LIGHTING)
	vec3 vViewPosition, vViewNormal;
#endif
	vViewPosition = vec3(worldViewMat * vec4(iPosition.xyz, 1.0));
	vViewNormal = vec3(worldViewMat * vec4(iNormal.xyz, 0.0));
#if !defined(VERTEX_LIGHTING) && defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
	vViewTangent = vec3(worldViewMat * vec4(iTangent.xyz, 0.0));
#endif

	vDepth = gl_Position.z;
	vColor = iColor;

#if defined(SHADOWRECEIVER)
	// calculate vertex position in light space
	vLightSpacePos1 = texWorldViewProj1 * iPosition;
#if defined(PSSM_ENABLED)
	vLightSpacePos2 = texWorldViewProj2 * iPosition;
	vLightSpacePos3 = texWorldViewProj3 * iPosition;
#endif
#endif

#if defined(VERTEX_LIGHTING)
	// assume light 0 is the sun directional light
	// get the direction from the pixel to the light source
	vec3 vertexNormal = safe_normalize(vViewNormal);
	vec3 pixelToLight = safe_normalize(lightPosition[0].xyz - (vViewPosition * lightPosition[0].w));
	
	// accumulate diffuse lighting
	float attenuation = max(dot(vertexNormal, pixelToLight.xyz), 0.0);
	vLightResult.xyz = lightDiffuse[0].xyz * attenuation;

#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	// per-pixel view reflection
	vec3 viewReflect = reflect(safe_normalize(vViewPosition), vertexNormal);

	// accumulate specular lighting
	attenuation *= pow(max(dot(viewReflect, pixelToLight), 0.0), materialShininess);
	vSpecularResult = lightSpecular[0].xyz * attenuation;
#endif
#endif
}
