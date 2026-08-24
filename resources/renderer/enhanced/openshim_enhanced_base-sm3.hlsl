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
					in float4 uv,
					in float2 invMapSize)
{
	uv /= uv.w;
	uv.z = min(uv.z, 1.0);
#if PCF_SIZE > 1
	float2 pixel = uv.xy / invMapSize - float2(float(PCF_SIZE-1)*0.5, float(PCF_SIZE-1)*0.5);
	float2 c = floor(pixel);
	float2 f = frac(pixel);

	float kernel[PCF_SIZE*PCF_SIZE];
	for (int y = 0; y < PCF_SIZE; ++y)
	{
		for (int x = 0; x < PCF_SIZE; ++x)
		{
			int i = y * PCF_SIZE + x;
			kernel[i] = step(uv.z, tex2D(map, (c + float2(x, y)) * invMapSize).x);
		}
	}

	float4 sum = float4(0.0, 0.0, 0.0, 0.0);
	for (int y = 0; y < PCF_SIZE-1; ++y)
	{
		for (int x = 0; x < PCF_SIZE-1; ++x)
		{
			int i = y * PCF_SIZE + x;
			sum += float4(kernel[i], kernel[i+1], kernel[i+PCF_SIZE], kernel[i+PCF_SIZE+1]);
		}
	}

	return lerp(lerp(sum.x, sum.y, f.x), lerp(sum.z, sum.w, f.x), f.y) / float((PCF_SIZE-1)*(PCF_SIZE-1));
#else
	return step(uv.z, tex2D(map, uv.xy).x);
#endif
}
#endif

#if defined(NORMALMAP_ENABLED) && !defined(VERTEX_TANGENTS)
// compute cotangent frame from normal, position, and texcoord
// http://www.thetenthplanet.de/archives/1180
float3x3 cotangent_frame(float3 N, float3 p, float2 uv)
{
	// get edge vectors of the pixel triangle
	float3 dp1 = ddx(p);
	float3 dp2 = ddy(p);
	float2 duv1 = ddx(uv);
	float2 duv2 = ddy(uv);

	// solve the linear system
	float3 dp2perp = cross(N, dp2);
	float3 dp1perp = cross(dp1, N);
	float3 T = dp2perp * duv1.x + dp1perp * duv2.x;
	float3 B = dp2perp * duv1.y + dp1perp * duv2.y;

	// construct a scale-invariant frame
	float invmax = rsqrt(max(dot(T, T), dot(B, B)) + 1e-30);
	T *= invmax;
	B *= invmax;
	return float3x3(T, B, N);
}
#endif

float3 safe_normalize(float3 v)
{
	float lenSq = dot(v, v);
	return (lenSq > 1e-8) ? v * rsqrt(lenSq) : float3(0.0, 0.0, 0.0);
}

#if defined(ENHANCED_MODE)
float3 sharpen_normal_map(float3 normalTex)
{
	float2 sharpenedXY = normalTex.xy * 1.85;
	float sharpenedZ = max(normalTex.z, 0.20);
	return safe_normalize(float3(sharpenedXY, sharpenedZ));
}
#endif

void ComputeSpotlightTerms(
	float3 pixelToLight,
	float3 lightDir,
	float4 spotParams,
	out float diffuseSpotAttenuation,
	out float specularSpotAttenuation)
{
	float spotRange = max(spotParams.x - spotParams.y, 1e-6);
	float cone = dot(pixelToLight, safe_normalize(-lightDir));
	float spotMask = saturate((cone - spotParams.y) / spotRange);
	float spotEnabled = (spotParams.z > 1e-4) ? 1.0 : 0.0;
	float spotPower = max(spotParams.z, 1.0);
	diffuseSpotAttenuation = lerp(1.0, pow(max(spotMask, 1e-4), spotPower), spotEnabled);
	specularSpotAttenuation = lerp(1.0, pow(max(spotMask, 1e-4), max(spotPower * 1.5, 1.0)), spotEnabled);
}

void base_vertex(
	uniform float4x4 wvpMat,
	uniform float4x4 worldViewMat,

#if defined(SHADOWRECEIVER) 
	uniform float4x4 texWorldViewProj1,
#if defined(PSSM_ENABLED)
	uniform float4x4 texWorldViewProj2,
	uniform float4x4 texWorldViewProj3,
#endif
#endif

#if defined(VERTEX_LIGHTING)
	uniform float4 lightPosition[MAX_LIGHTS],
	uniform float4 lightDiffuse[MAX_LIGHTS],
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	uniform float4 lightSpecular[MAX_LIGHTS],
	uniform float materialShininess,
#endif
#endif

	in float4 iPosition : POSITION,
	in float2 iTexCoord : TEXCOORD0,
	in float3 iNormal : NORMAL,
#if !defined(VERTEX_LIGHTING) && defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
	in float3 iTangent : TANGENT,
#endif

#if defined (VERTEX_LIGHTING)
	out float3 vLightResult : COLOR0,
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	out float3 vSpecularResult : COLOR1,
#endif
#endif

	out float2 vTexCoord : TEXCOORD0,

#if !defined(VERTEX_LIGHTING)
	out float3 vViewNormal : TEXCOORD1,
#if defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
	out float3 vViewTangent : TEXCOORD2,
#endif
	out float3 vViewPosition : TEXCOORD3,
#endif

	out float vDepth : TEXCOORD4,
#if defined(SHADOWRECEIVER) 
	out float4 vLightSpacePos1 : TEXCOORD5,
#if defined(PSSM_ENABLED)
	out float4 vLightSpacePos2 : TEXCOORD6,
	out float4 vLightSpacePos3 : TEXCOORD7,
#endif
#endif

	out float4 oPosition : POSITION
)
{
	oPosition = mul(wvpMat, iPosition);

	vTexCoord = iTexCoord;

#if defined(VERTEX_LIGHTING)
	float3 vViewPosition, vViewNormal;
#endif
	vViewPosition = mul(worldViewMat, float4(iPosition.xyz, 1.0)).xyz;
	vViewNormal = mul(worldViewMat, float4(iNormal.xyz, 0.0)).xyz;
#if !defined(VERTEX_LIGHTING) && defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
	vViewTangent = mul(worldViewMat, float4(iTangent.xyz, 0.0)).xyz;
#endif

	vDepth = oPosition.z;

#if defined(SHADOWRECEIVER) 
	// calculate vertex position in light space
	vLightSpacePos1 = mul(texWorldViewProj1, iPosition);
#if defined(PSSM_ENABLED)
	vLightSpacePos2 = mul(texWorldViewProj2, iPosition);
	vLightSpacePos3 = mul(texWorldViewProj3, iPosition);
#endif
#endif

#if defined(VERTEX_LIGHTING)
	// assume light 0 is the sun directional light
	// get the direction from the pixel to the light source
	float3 vertexNormal = safe_normalize(vViewNormal);
	float3 pixelToLight = safe_normalize(lightPosition[0].xyz - (vViewPosition * lightPosition[0].w));
	
	// accumulate diffuse lighting
	float attenuation = max(dot(vertexNormal, pixelToLight.xyz), 0.0);
#if defined(OG_RETRO_MODE)
	attenuation = saturate(attenuation * 0.55 + 0.20);
#endif
	vLightResult = lightDiffuse[0].xyz * attenuation;

#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	// per-pixel view reflection
	float3 viewReflect = reflect(safe_normalize(vViewPosition), vertexNormal);

	// accumulate specular lighting
	attenuation *= pow(max(dot(viewReflect, pixelToLight), 0.0), materialShininess);
	vSpecularResult = lightSpecular[0].xyz * attenuation;
#endif
#endif
}

// -------------------------------------------

void base_fragment(
	uniform sampler2D diffuseMap : register(s0),
#if defined(NORMALMAP_ENABLED) 
	uniform sampler2D normalMap : register(s1),
#endif
#if defined(SPECULARMAP_ENABLED)
	uniform sampler2D specularMap : register(s2),
#endif
#if defined(EMISSIVEMAP_ENABLED)
	uniform sampler2D emissiveMap : register(s3),
#if defined(ENHANCED_MODE)
	uniform float4 materialEmissive,
#endif
#endif
#if defined(SHADOWRECEIVER) 
	uniform sampler2D shadowMap1 : register(s4),
#if defined(PSSM_ENABLED)
	uniform sampler2D shadowMap2 : register(s5),
	uniform sampler2D shadowMap3 : register(s6),
#endif

	uniform float4 invShadowMapSize1,
#if defined(PSSM_ENABLED)
	uniform float4 invShadowMapSize2,
	uniform float4 invShadowMapSize3,
	uniform float4 pssmSplitPoints,
#endif
#endif

	uniform float4 sceneAmbient,
	uniform float4 diffuseColor,

#if !defined(VERTEX_LIGHTING)
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	uniform float materialShininess,
#endif
	uniform float4 lightDiffuse[MAX_LIGHTS],
	uniform float4 lightPosition[MAX_LIGHTS],
	uniform float4 lightSpecular[MAX_LIGHTS],
	uniform float4 lightAttenuation[MAX_LIGHTS],
	uniform float4 spotLightParams[MAX_LIGHTS],
	uniform float4 lightDirection[MAX_LIGHTS],
	uniform float lightCount,
#endif

	uniform float4 fogColour,
	uniform float4 fogParams,
	uniform float transparency,

#if defined (VERTEX_LIGHTING)
	in float3 vLightResult : COLOR0,
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	in float3 vSpecularResult : COLOR1,
#endif
#endif
	in float2 vTexCoord : TEXCOORD0,
#if !defined(VERTEX_LIGHTING)
	in float3 vViewNormal : TEXCOORD1,
#if defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
	in float3 vViewTangent : TEXCOORD2,
#endif
	in float3 vViewPosition : TEXCOORD3,
#endif
	in float vDepth : TEXCOORD4,
#if defined(SHADOWRECEIVER) 
	in float4 vLightSpacePos1 : TEXCOORD5,
#if defined(PSSM_ENABLED)
	in float4 vLightSpacePos2 : TEXCOORD6,
	in float4 vLightSpacePos3 : TEXCOORD7,
#endif
#endif

	out float4 oColor : COLOR
#if defined(LOGDEPTH_ENABLE)	
	, out float oDepth : DEPTH
#endif
)
{
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
	float3 lightResult = vLightResult;
#if defined(SHADOWRECEIVER)
	lightResult *= shadow;
#endif
#if defined(OG_RETRO_MODE)
	lightResult += max(sceneAmbient.xyz * 1.10, float3(0.22, 0.22, 0.22));
#else
	lightResult += sceneAmbient.xyz;
#endif
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	float3 specularResult = float3(0.0, 0.0, 0.0);
#endif
#else
	float3 lightResult = vLightResult;
#if defined(SHADOWRECEIVER)
	lightResult *= shadow;
#endif
#if defined(OG_RETRO_MODE)
	lightResult += max(sceneAmbient.xyz * 1.10, float3(0.22, 0.22, 0.22));
#else
	lightResult += sceneAmbient.xyz;
#endif

#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	float3 specularResult = vSpecularResult;
#endif
#endif
	
#else

	// per-pixel view position
	float3 viewPos = vViewPosition;

#if defined(NORMALMAP_ENABLED) 
	// tangent basis
#if defined(VERTEX_TANGENTS)
	float3 baseNormal = safe_normalize(vViewNormal);
	float3 baseTangent = safe_normalize(vViewTangent);
	float3 binormal = safe_normalize(cross(baseTangent, baseNormal));
	float3x3 tbn = float3x3(baseTangent, binormal, baseNormal);
#else
	float3x3 tbn = cotangent_frame(safe_normalize(vViewNormal), vViewPosition.xyz, vTexCoord);
#endif

	// per-pixel view normal
	float3 normalTex = tex2D(normalMap, vTexCoord).xyz * 2.0 - 1.0;
#if defined(ENHANCED_MODE)
	// fade the sharpening out with distance so it cannot shimmer far away
	normalTex = lerp(sharpen_normal_map(normalTex), normalTex, saturate(vDepth * 0.005));
#endif
	float3 viewNormal = safe_normalize(mul(normalTex.xyz, tbn));
#else
	float3 viewNormal = safe_normalize(vViewNormal);
#endif

#if defined(SPECULARMAP_ENABLED)
	float3 specularTex = tex2D(specularMap, vTexCoord).xyz;
	float specularMask = saturate(dot(specularTex, float3(0.299, 0.587, 0.114)));
	float3 specularTint = lerp(float3(0.04, 0.04, 0.04), specularTex, specularMask);
#endif

	float3 eyeDir = safe_normalize(-viewPos);

	// start with ambient light and no specular
#if defined(OG_RETRO_MODE)
	float3 lightResult = max(sceneAmbient.xyz * 1.10, float3(0.22, 0.22, 0.22));
#else
	float3 lightResult = sceneAmbient.xyz;
#endif
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
	float3 specularResult = float3(0,0,0);
#endif

#if defined(RETRO_UNLIT_MODE)
	if (lightCount > 0.0)
	{
		const int i = 0;
		float3 pixelToLight = lightPosition[i].xyz - (viewPos * lightPosition[i].w);
		float d = max(length(pixelToLight), 1e-6);
		pixelToLight *= rcp(d);

#if defined(SHADOWRECEIVER)
		float attenuation = shadow;
#else
		float attenuation = 1.0;
#endif

		float diffuseTerm = max(dot(viewNormal, pixelToLight), 0.0);
#if defined(OG_RETRO_MODE)
		diffuseTerm = saturate(diffuseTerm * 0.55 + 0.20);
#endif
		lightResult.xyz += lightDiffuse[i].xyz * (attenuation * diffuseTerm);
	}
#else
#if MAX_LIGHTS > 1
	// for each possible light source...
	[unroll] for (int i = 0; i < MAX_LIGHTS; ++i)
	{
		if (i >= int(lightCount))
			break;
#else
	{
		const int i = 0;
#endif

		// get the direction from the pixel to the light source
		float3 pixelToLight = lightPosition[i].xyz - (viewPos * lightPosition[i].w);
		float d = max(length(pixelToLight), 1e-6);
		pixelToLight *= rcp(d);

		float distanceAttenuation = saturate(1.0 /
			(lightAttenuation[i].y + d * (lightAttenuation[i].z + d * lightAttenuation[i].w)));
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
		diffuseTerm = saturate(diffuseTerm * 0.55 + 0.20);
#endif
		attenuation *= diffuseTerm;
		lightResult.xyz += lightDiffuse[i].xyz * attenuation;

#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
		// accumulate specular lighting with a tighter lobe and tinted F0.
		if (diffuseTerm > 0.0)
		{
			float3 halfVector = safe_normalize(pixelToLight + eyeDir);
			float ndotv = max(dot(viewNormal, eyeDir), 0.0);
			float ndoth = max(dot(viewNormal, halfVector), 0.0);
#if defined(SPECULARMAP_ENABLED)
			float specularPower = lerp(
				max(materialShininess * 0.9 + 6.0, 8.0),
				max(materialShininess * 2.25 + 24.0, 24.0),
				specularMask);
			float3 specularColor = lerp(specularTint * 0.65, specularTint, pow(1.0 - ndotv, 5.0));
#else
			float specularPower = max(materialShininess * 1.5 + 12.0, 16.0);
			float3 specularColor = lerp(float3(0.025, 0.025, 0.025), float3(0.04, 0.04, 0.04), pow(1.0 - ndotv, 5.0));
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

#if defined(ENHANCED_MODE)
	// subtle fresnel sky fill lifts silhouettes out of flat ambient
	float rimTerm = pow(1.0 - max(dot(viewNormal, eyeDir), 0.0), 4.0);
	lightResult.xyz += sceneAmbient.xyz * rimTerm * 0.35;
#endif
#endif

	// diffuse texture
	float4 diffuseTex = tex2D(diffuseMap, vTexCoord);
	oColor.xyz = lightResult.xyz * diffuseTex.xyz * diffuseColor.xyz;

#if defined(SPECULARMAP_ENABLED)
	oColor.xyz += specularResult.xyz;
#elif defined(SPECULAR_ENABLED)
	oColor.xyz += specularResult.xyz;
#endif

#if defined(EMISSIVEMAP_ENABLED)
	// emissive texture
	float3 emissiveTex = tex2D(emissiveMap, vTexCoord).xyz;
#if defined(ENHANCED_MODE)
	// Runtime material variants drive this continuously for optional running-light
	// pulsing. Empty craft use a zero emissive value and remain fully dark.
	float emissiveIntensity = saturate(max(materialEmissive.x, max(materialEmissive.y, materialEmissive.z)));
	oColor.xyz += emissiveTex.xyz * emissiveIntensity;
#else
	oColor.xyz += emissiveTex.xyz;
#endif
#endif

	// fog
	float fogValue = saturate((vDepth - fogParams.y) * fogParams.w);
	oColor.xyz = lerp(oColor.xyz, fogColour.xyz, fogValue);

	// output alpha
	//oColor.a = diffuseTex.a;
	oColor.a = saturate(transparency);

#if defined(LOGDEPTH_ENABLE)
	// logarithmic depth
	const float C = 0.1;
	const float far = 1e+09;
	const float offset = 1.0;
	oDepth = log(C * vDepth + offset) / log(C * far + offset);
#endif
}
