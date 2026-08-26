#version 120

uniform sampler2D diffuseMap;

uniform vec3 fogColour;
uniform vec4 fogParams;

varying vec4 vColor;
varying vec2 vTexCoord;
varying float vDepth;

void main()
{
	vec4 diffuseTex = texture2D(diffuseMap, vTexCoord);
	vec4 oColor = diffuseTex * vColor;

	float fogValue = clamp((vDepth - fogParams.y) * fogParams.w, 0.0, 1.0);
	oColor.xyz = mix(oColor.xyz, fogColour, vec3(fogValue));

	gl_FragData[0] = oColor;

#ifdef LOGDEPTH_ENABLE
	const float C = 0.1;
	const float far = 1e+09;
	const float offset = 1.0;
	gl_FragDepth = log(C * vDepth + offset) / log(C * far + offset);
#endif
}
