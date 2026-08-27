#version 120

// Force OG retro mode to ignore modern map contributions even if a program
// variant accidentally leaves those feature defines enabled.
#if defined(OG_RETRO_MODE)
#undef NORMALMAP_ENABLED
#undef SPECULARMAP_ENABLED
#undef SPECULAR_ENABLED
#undef EMISSIVEMAP_ENABLED
#endif

#if defined(SHADOWRECEIVER)
float PCF_Filter(in sampler2D map,
					in vec4 uv,
					in vec2 invMapSize)
{
	uv /= uv.w;
	uv.z = min(uv.z, 1.0);
#if PCF_SIZE > 1
	vec2 pixel = uv.xy / invMapSize - vec2(float(PCF_SIZE-1)*0.5, float(PCF_SIZE-1)*0.5);
	vec2 c = floor(pixel);
	vec2 f = fract(pixel);

	float kernel[PCF_SIZE*PCF_SIZE];
	for (int y = 0; y < PCF_SIZE; ++y)
	{
		for (int x = 0; x < PCF_SIZE; ++x)
		{
			int i = y * PCF_SIZE + x;
			kernel[i] = step(uv.z, texture2D(map, (c + vec2(x, y)) * invMapSize).x);
		}
	}

	vec4 sum = vec4(0.0, 0.0, 0.0, 0.0);
	for (int y = 0; y < PCF_SIZE-1; ++y)
	{
		for (int x = 0; x < PCF_SIZE-1; ++x)
		{
			int i = y * PCF_SIZE + x;
			sum += vec4(kernel[i], kernel[i+1], kernel[i+PCF_SIZE], kernel[i+PCF_SIZE+1]);
		}
	}

	return mix(mix(sum.x, sum.y, f.x), mix(sum.z, sum.w, f.x), f.y) / float((PCF_SIZE-1)*(PCF_SIZE-1));
#else
	return step(uv.z, texture2D(map, uv.xy).x);
#endif
}
#endif

#if defined(NORMALMAP_ENABLED) && !defined(VERTEX_TANGENTS)
// compute cotangent frame from normal, position, and texcoord
// http://www.thetenthplanet.de/archives/1180
mat3 cotangent_frame(in vec3 N, in vec3 p, in vec2 uv)
 {
	// get edge vectors of the pixel triangle
	vec3 dp1 = dFdx(p);
	vec3 dp2 = dFdy(p);
	vec2 duv1 = dFdx(uv);
	vec2 duv2 = dFdy(uv);

	// solve the linear system
	vec3 dp2perp = cross(N, dp2);
	vec3 dp1perp = cross(dp1, N);
	vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
	vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

	// construct a scale-invariant frame
	float invmax = inversesqrt(max(dot(T, T), dot(B, B)) + 1e-30);
	T *= invmax;
	B *= invmax;
	return mat3(
		T.x, B.x, N.x,
		T.y, B.y, N.y,
		T.z, B.z, N.z
	);
}
#endif

uniform sampler2D diffuseMap;
#if defined(DETAILMAP_ENABLED)
uniform sampler2D detailMap;
#endif
#if defined(NORMALMAP_ENABLED)
uniform sampler2D normalMap;
#endif
#if defined(SPECULARMAP_ENABLED)
uniform sampler2D specularMap;
#endif
#if defined(EMISSIVEMAP_ENABLED)
uniform sampler2D emissiveMap;
#endif
#if defined(SHADOWRECEIVER)
uniform sampler2D shadowMap1;
#if defined(PSSM_ENABLED)
uniform sampler2D shadowMap2;
uniform sampler2D shadowMap3;
#endif
uniform vec4 invShadowMapSize1;
#if defined(PSSM_ENABLED)
uniform vec4 invShadowMapSize2;
uniform vec4 invShadowMapSize3;
uniform vec4 pssmSplitPoints;
#endif
#endif

vec3 safe_normalize(in vec3 v)
{
	float lenSq = dot(v, v);
	return (lenSq > 1e-8) ? v * inversesqrt(lenSq) : vec3(0.0, 0.0, 0.0);
}

#if defined(ENHANCED_MODE)
vec3 sharpen_normal_map(in vec3 normalTex)
{
	vec2 sharpenedXY = normalTex.xy * 1.85;
	float sharpenedZ = max(normalTex.z, 0.20);
	return safe_normalize(vec3(sharpenedXY, sharpenedZ));
}
#endif

void ComputeSpotlightTerms(
	in vec3 pixelToLight,
	in vec3 lightDir,
	in vec4 spotParams,
	out float diffuseSpotAttenuation,
	out float specularSpotAttenuation)
{
	float spotRange = max(spotParams.x - spotParams.y, 1e-6);
	float cone = dot(pixelToLight, safe_normalize(-lightDir));
	float spotMask = clamp((cone - spotParams.y) / spotRange, 0.0, 1.0);
	float spotEnabled = spotParams.z > 1e-4 ? 1.0 : 0.0;
	float spotPower = max(spotParams.z, 1.0);
	diffuseSpotAttenuation = mix(1.0, pow(max(spotMask, 1e-4), spotPower), spotEnabled);
	specularSpotAttenuation = mix(1.0, pow(max(spotMask, 1e-4), max(spotPower * 1.5, 1.0)), spotEnabled);
}

uniform vec4 sceneAmbient;
#if !defined(VERTEX_LIGHTING)
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
uniform float materialShininess;
#endif
uniform vec4 lightDiffuse[MAX_LIGHTS];
uniform vec4 lightPosition[MAX_LIGHTS];
uniform vec4 lightSpecular[MAX_LIGHTS];
uniform vec4 lightAttenuation[MAX_LIGHTS];
uniform vec4 spotLightParams[MAX_LIGHTS];
uniform vec4 lightDirection[MAX_LIGHTS];
uniform float lightCount;
#endif

uniform vec4 fogColour;
uniform vec4 fogParams;

varying vec4 vColor;
#if defined (VERTEX_LIGHTING)
varying vec3 vLightResult;
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
varying vec3 vSpecularResult;
#endif
#endif
varying vec2 vTexCoord;
#if !defined(VERTEX_LIGHTING)
varying vec3 vViewPosition;
varying vec3 vViewNormal;
#if defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
varying vec3 vViewTangent;
#endif
#endif

varying float vDepth;
#if defined(SHADOWRECEIVER)
varying vec4 vLightSpacePos1;
#if defined(PSSM_ENABLED)
varying vec4 vLightSpacePos2;
varying vec4 vLightSpacePos3;
#endif
#endif

void main()
{
	vec4 oColor;

#if defined(SHADOWRECEIVER)
	// shadow texture
	float shadow;
#if defined(PSSM_ENABLED)
	if (vDepth <= pssmSplitPoints.y)
	{
#endif
		shadow = PCF_Filter(shadowMap1, vLightSpacePos1, invShadowMapSize1.xy);
#if defined(PSSM_ENABLED)
	}
	else if (vDepth <= pssmSplitPoints.z)
	{
		shadow = PCF_Filter(shadowMap2, vLightSpacePos2, invShadowMapSize2.xy);
	}
	else
	{
		shadow = PCF_Filter(shadowMap3, vLightSpacePos3, invShadowMapSize3.xy);
	}
#endif
#if defined(ENHANCED_MODE)
	// deeper shadow floor gives enhanced mode more contact grounding
	shadow = shadow * 0.78 + 0.22;
#else
	shadow = shadow * 0.7 + 0.3;
#endif
#if defined(OG_RETRO_MODE)
	shadow = shadow * 0.5 + 0.5;
#endif
#endif

#if defined(VERTEX_LIGHTING)

	// combine ambient and shadowed light result
#if defined(RETRO_UNLIT_MODE)
	vec3 lightResult = vLightResult;
#if defined(SHADOWRECEIVER)
	lightResult *= shadow;
#endif
#if defined(OG_RETRO_MODE)
	lightResult += max(sceneAmbient.xyz * 1.10, vec3(0.22, 0.22, 0.22));
#else
	lightResult += sceneAmbient.xyz;
#endif
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	vec3 specularResult = vec3(0.0, 0.0, 0.0);
#endif
#else
	vec3 lightResult = vLightResult;
#if defined(SHADOWRECEIVER)
	lightResult *= shadow;
#endif
#if defined(OG_RETRO_MODE)
	lightResult += max(sceneAmbient.xyz * 1.10, vec3(0.22, 0.22, 0.22));
#else
	lightResult += sceneAmbient.xyz;
#endif

#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	vec3 specularResult = vSpecularResult;
#endif
#endif
	
#else

	// per-pixel view position
	vec3 viewPos = vViewPosition;

#if defined(NORMALMAP_ENABLED)
	// tangent basis
#if defined(VERTEX_TANGENTS)
	vec3 baseNormal = safe_normalize(vViewNormal);
	vec3 baseTangent = safe_normalize(vViewTangent);
	vec3 binormal = safe_normalize(cross(baseTangent, baseNormal));
	mat3 tbn = mat3(
		baseTangent.x, binormal.x, baseNormal.x,
		baseTangent.y, binormal.y, baseNormal.y,
		baseTangent.z, binormal.z, baseNormal.z
	);
#else
	mat3 tbn = cotangent_frame(safe_normalize(vViewNormal), vViewPosition, vTexCoord);
#endif

	// per-pixel view normal
	vec3 normalTex = texture2D(normalMap, vTexCoord).xyz * 2.0 - 1.0;
#if defined(ENHANCED_MODE)
	// fade the sharpening out with distance so it cannot shimmer far away
	normalTex = mix(sharpen_normal_map(normalTex), normalTex, clamp(vDepth * 0.005, 0.0, 1.0));
#endif
	vec3 viewNormal = safe_normalize(normalTex * tbn);
#else
	vec3 viewNormal = safe_normalize(vViewNormal);
#endif

#if defined(SPECULARMAP_ENABLED)
	vec3 specularTex = texture2D(specularMap, vTexCoord).xyz;
	float specularMask = clamp(dot(specularTex, vec3(0.299, 0.587, 0.114)), 0.0, 1.0);
	vec3 specularTint = mix(vec3(0.04, 0.04, 0.04), specularTex, specularMask);
#endif

	// start with ambient light and no specular
#if defined(OG_RETRO_MODE)
	vec3 lightResult = max(sceneAmbient.xyz * 1.10, vec3(0.22, 0.22, 0.22));
#else
	vec3 lightResult = sceneAmbient.xyz;
#endif
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	vec3 specularResult = vec3(0.0, 0.0, 0.0);
#endif

#if defined(RETRO_UNLIT_MODE)
	if (lightCount > 0.0)
	{
		const int i = 0;
		vec3 pixelToLight = lightPosition[i].xyz - (viewPos * lightPosition[i].w);
		float d = max(length(pixelToLight), 1e-6);
		pixelToLight /= d;

#if defined(SHADOWRECEIVER)
		float attenuation = shadow;
#else
		float attenuation = 1.0;
#endif

		float diffuseTerm = max(dot(viewNormal, pixelToLight), 0.0);
#if defined(OG_RETRO_MODE)
		diffuseTerm = clamp(diffuseTerm * 0.55 + 0.20, 0.0, 1.0);
#endif
		lightResult.xyz += lightDiffuse[i].xyz * (attenuation * diffuseTerm);
	}
#else
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	vec3 eyeDir = safe_normalize(-viewPos.xyz);
#endif

#if MAX_LIGHTS > 1
	// for each possible light source...
	for (int i = 0; i < MAX_LIGHTS; ++i)
	{
		if (i >= int(lightCount))
			break;
#else
	{
		const int i = 0;
#endif

		// get the direction from the pixel to the light source
		vec3 pixelToLight = (lightPosition[i].xyz - (viewPos * lightPosition[i].w));
		float d = max(length(pixelToLight), 1e-6);
		pixelToLight /= d;
		
		float distanceAttenuation = clamp(1.0 /
			(lightAttenuation[i].y + (d * (lightAttenuation[i].z + (d * lightAttenuation[i].w)))),
			0.0, 1.0);
		float diffuseSpotAttenuation = 1.0;
		float specularSpotAttenuation = 1.0;
		ComputeSpotlightTerms(
			pixelToLight,
			lightDirection[i].xyz,
			spotLightParams[i],
			diffuseSpotAttenuation,
			specularSpotAttenuation);

		float attenuation = distanceAttenuation * diffuseSpotAttenuation;
		float specularAttenuation = distanceAttenuation * specularSpotAttenuation;
	
#if defined(SHADOWRECEIVER)
		// apply shadow attenuation
		attenuation *= shadow;
		specularAttenuation *= shadow;
#endif

		// accumulate diffuse lighting
		float diffuseTerm = max(dot(viewNormal, pixelToLight), 0.0);
#if defined(OG_RETRO_MODE)
		diffuseTerm = clamp(diffuseTerm * 0.55 + 0.20, 0.0, 1.0);
#endif
		attenuation *= diffuseTerm;
		lightResult.xyz += lightDiffuse[i].xyz * attenuation;

#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
		// accumulate specular lighting with a tighter lobe and tinted F0.
		if (diffuseTerm > 0.0)
		{
			vec3 halfVector = safe_normalize(pixelToLight + eyeDir);
			float ndotv = max(dot(viewNormal, eyeDir), 0.0);
			float ndoth = max(dot(viewNormal, halfVector), 0.0);
#if defined(SPECULARMAP_ENABLED)
			float specularPower = mix(
				max(materialShininess * 0.9 + 6.0, 8.0),
				max(materialShininess * 2.25 + 24.0, 24.0),
				specularMask);
			vec3 specularColor = mix(specularTint * 0.65, specularTint, pow(1.0 - ndotv, 5.0));
#else
			float specularPower = max(materialShininess * 1.5 + 12.0, 16.0);
			vec3 specularColor = mix(vec3(0.025, 0.025, 0.025), vec3(0.04, 0.04, 0.04), pow(1.0 - ndotv, 5.0));
#endif
			float specularLobe = pow(ndoth, specularPower);
#if defined(ENHANCED_MODE)
			// Blinn-Phong energy normalization (unity at the stock power of
			// 24) so tighter lobes read brighter instead of vanishing.
			specularLobe *= min((specularPower + 8.0) * 0.03125, 3.0);
#endif
			specularResult.xyz += lightSpecular[i].xyz * specularAttenuation * diffuseTerm * specularLobe * specularColor;
		}
#endif

#if defined(SHADOWRECEIVER)
		// clear shadow attenuation
		shadow = 1.0;
#endif
	}

#endif
#endif

	// diffuse texture 
	vec4 diffuseTex = texture2D(diffuseMap, vTexCoord);
	oColor.xyz = lightResult.xyz * vColor.xyz * diffuseTex.xyz;
   
#if defined(SPECULARMAP_ENABLED)
	oColor.xyz += specularResult.xyz;
#elif defined(SPECULAR_ENABLED)
	oColor.xyz += specularResult.xyz;
#endif

#if defined(EMISSIVEMAP_ENABLED)
	// emissive texture
	vec3 emissiveTex = texture2D(emissiveMap, vTexCoord).xyz;
	oColor.xyz += emissiveTex.xyz;
#endif
   
#if defined(DETAILMAP_ENABLED)
	// detail texture
	vec3 detailTex = texture2D(detailMap, fract(vTexCoord * 8.0)).xyz * 2.0;
	vec3 fullbrightDetail = vec3(1.0, 1.0, 1.0);
#if defined(ENHANCED_MODE)
	// keep the base detail octave alive further out, and layer a tighter
	// second octave close to the camera for crisper ground under the craft
	float detailDistance = clamp(vDepth * 0.015, 0.0, 1.0);
	vec3 detailColor = mix(detailTex, fullbrightDetail, detailDistance);
	vec3 detailTexNear = texture2D(detailMap, fract(vTexCoord * 32.0)).xyz * 2.0;
	float detailNearFade = clamp(vDepth * 0.08, 0.0, 1.0);
	detailColor *= mix(mix(detailTexNear, fullbrightDetail, 0.5), fullbrightDetail, detailNearFade);
#else
	float detailDistance = clamp(vDepth * 0.025, 0.0, 1.0);
	vec3 detailColor = mix(detailTex, fullbrightDetail, detailDistance);
#endif
#if defined(OG_RETRO_MODE)
	oColor.xyz = mix(oColor.xyz, oColor.xyz * detailColor, diffuseTex.w * 0.35);
#else
	oColor.xyz = mix(oColor.xyz, oColor.xyz * detailColor, diffuseTex.w);
#endif
#endif

	// fog
	float fogValue = clamp((vDepth - fogParams.y) * fogParams.w, 0.0, 1.0);
	oColor.xyz = mix(oColor.xyz, fogColour.xyz, fogValue);

	// output alpha
	oColor.a = vColor.a;

	gl_FragData[0] = oColor;

#if defined(LOGDEPTH_ENABLE)
	// logarithmic depth
	const float C = 0.1;
	const float far = 1e+09;
	const float offset = 1.0;
	gl_FragDepth = log(C * vDepth + offset) / log(C * far + offset);
#endif
}
