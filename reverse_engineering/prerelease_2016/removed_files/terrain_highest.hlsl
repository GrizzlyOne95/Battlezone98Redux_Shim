#define PCF
#define KERNEL_STEP_COUNT 3

float PCF_Filter(sampler2D map,
                     float4 uv,
                     float2 invShadowMapSize0)
{
	float sum = 0;
    float2 stepUV = invShadowMapSize0 * 0.2;
    for( float x = -KERNEL_STEP_COUNT; x <= KERNEL_STEP_COUNT; ++x )
	{
		for( float y = -KERNEL_STEP_COUNT; y <= KERNEL_STEP_COUNT; ++y )
        {
            float2 offset = float2( x, y ) * stepUV;
            sum += step(uv.z, tex2D(map, uv.xy + offset).x);
        }
	}
		
    float numSamples = KERNEL_STEP_COUNT * 2 + 1;
    return sum / (numSamples*numSamples);
}

#ifndef VERTEX_TANGENTS
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
	float invmax = rsqrt(max(dot(T, T), dot(B, B)));
	return float3x3(T * invmax, B * invmax, N);
}
#endif

void terrain_vertex(
	float4 iPosition : POSITION,
	in float3 iNormal : NORMAL,
	in float2 iUV : TEXCOORD0,
#ifdef VERTEX_TANGENTS
	in float3 iTangent : TANGENT,
#endif
	in float4 iDiffuse : COLOR,
	in float heightOffset : TEXCOORD1,

	out float2 UV : TEXCOORD0,
	out float4 oPosition : POSITION,
	out float3 normal : TEXCOORD2,
	out float3 tangent : TEXCOORD3,
	out float3 positionObjSpace : TEXCOORD4,
	out float4 diffuse : COLOR,
	out float depth : TEXCOORD5,
	out float4 oShadowUV1 : TEXCOORD6,

	uniform float4x4 wvpMat,
	uniform float4x4 worldMatrix,
	uniform float4x4 texViewProj1
)
{
	iPosition.y = heightOffset;
	positionObjSpace = iPosition.xyz;
	oPosition = mul(wvpMat, iPosition);
	UV = iUV;
	normal = iNormal;
#ifdef VERTEX_TANGENTS
	tangent = iTangent;
#endif
	depth = oPosition.z;
	diffuse = iDiffuse;
	
	float4 worldPos = mul(worldMatrix, iPosition);
	oShadowUV1 = mul(texViewProj1, worldPos);
}

void terrain_fragment(
	out float4 oColor : COLOR,
	out float oDepth : DEPTH,

	in float2 iUV : TEXCOORD0,
	in float3 iNormal : TEXCOORD2,
#ifdef VERTEX_TANGENTS
	in float3 iTangent : TEXCOORD3,
#endif
	in float3 positionObjSpace : TEXCOORD4,
	in float depth : TEXCOORD5,
	in float4 shadowUV1 : TEXCOORD6,
	in float4 diffuse : COLOR,

	uniform sampler2D diffuseMap : register(s0),
	uniform sampler2D detailMap : register(s1),
	uniform sampler2D normalMap : register(s2),
	uniform sampler2D specularMap : register(s3),
	uniform sampler2D emissiveMap : register(s4),
	uniform sampler2D shadowMap1 : register(s5),

	uniform float4 invShadowMapSize0,

	uniform float4 sceneAmbient,
	uniform float4 materialAmbient,
	uniform float4 materialDiffuse,
	uniform float materialShininess,
	uniform float4 materialSpecular,

	uniform float4 lightDiffuse[MAX_LIGHTS],
	uniform float4 lightPosition[MAX_LIGHTS],
	uniform float4 lightSpecular[MAX_LIGHTS],
	uniform float4 lightAttenuation[MAX_LIGHTS],
	uniform float4 spotLightParams[MAX_LIGHTS],
	uniform float4 lightDirection[MAX_LIGHTS],

	uniform float4x4 worldViewMat,

	uniform float4 fogColour,
	uniform float4 fogParams
)
{
	// tangent basis
#ifdef VERTEX_TANGENTS
	float3 binormal = cross(iTangent, iNormal);
	float3x3 tbn = float3x3(iTangent, binormal, iNormal);
#else
	float3x3 tbn = cotangent_frame(iNormal, positionObjSpace.xyz, iUV);
#endif

	// per-pixel model normal
	float3 normalTex = tex2D(normalMap, iUV).xyz * 2.0 - 1.0;
	float3 normal = normalize(mul(normalTex, tbn));

	// per-pixel view normal
	float3 viewPos = mul(worldViewMat, float4(positionObjSpace.xyz, 1)).xyz;
	float3 viewNormal = normalize(mul(worldViewMat, float4(normal.xyz, 0)).xyz);

	// per-pixel direction to the eyepoint
	float3 eyeDir = normalize(/* cameraPosInViewSpace = float3(0,0,0) */ -viewPos.xyz);

	// start with ambient light and no specular
	float3 lightResult = sceneAmbient.xyz * materialAmbient.xyz;
	float3 specularResult = float3(0,0,0);

	// shadow texture
	shadowUV1 /= shadowUV1.w;
#ifdef PCF
	float shadow = 0.6 + 0.4 * PCF_Filter(shadowMap1, shadowUV1, invShadowMapSize0.xy);
#else
	float shadow = 0.6 + 0.4 * step(shadowUV1.z, tex2D(shadowMap1, shadowUV1.xy).x);
#endif

	// for each possible light source...
	for (int i=0; i<MAX_LIGHTS; ++i)
	{
		// get the direction from the pixel to the light source
		float3 pixelToLight = lightPosition[i].xyz - (viewPos * lightPosition[i].w);
		float d = length(pixelToLight);
		pixelToLight /= d;

		// if the pixel is facing the light...
		float NdotL = dot(viewNormal, pixelToLight);
		if (NdotL > 0.0)
		{
			// compute distance attentuation
			float attenuation = saturate(1.0 / 
				(lightAttenuation[i].y + d * (lightAttenuation[i].z + d * lightAttenuation[i].w)));

			// compute spotlight attenuation
			// it's much faster to just do the math than have a branch on low-end GPUs
			// non-spotlights have falloff power 0 which yields a constant output
			attenuation *= pow(saturate(
				(dot(pixelToLight, normalize(-lightDirection[i].xyz)) - spotLightParams[i].y) /
				(spotLightParams[i].x - spotLightParams[i].y)), spotLightParams[i].z);

			// apply shadow attenuation
			attenuation *= shadow;

			// accumulate diffuse lighting
			lightResult.xyz += materialDiffuse.xyz * lightDiffuse[i].xyz * attenuation * NdotL;

			// half vector
			float3 halfVec = normalize (pixelToLight + eyeDir);

			// accumulate specular lighting
			specularResult.xyz += materialSpecular.xyz * lightSpecular[i].xyz * attenuation * pow(max(dot(viewNormal, halfVec), 0.0), materialShininess);
		}

		// clear shadow attenuation
		shadow = 1.0;
	}

	// diffuse texture
	float4 diffuseTex = tex2D(diffuseMap, iUV);
	oColor.xyz = lightResult.xyz * diffuseTex.xyz * diffuse.xyz;

	// specular texture
	float3 specularTex = tex2D(specularMap, iUV).xyz;
	oColor.xyz += specularResult.xyz * specularTex.xyz;

	// emissive texture
	float3 emissiveTex = tex2D(emissiveMap, iUV).xyz;
	oColor.xyz += emissiveTex.xyz;

	// detail texture
	float3 detailTex = tex2D(detailMap, frac(iUV * 8)).xyz * 2;
	float3 fullbrightDetail = float3(1, 1, 1);
	float detailDistance = saturate(depth * 0.025);
	float3 detailColor = lerp(detailTex, fullbrightDetail, detailDistance);
	oColor.xyz = lerp(oColor.xyz, oColor.xyz * detailColor, diffuseTex.a);

	// fog
	float fogValue = saturate((depth - fogParams.y) * fogParams.w);
	oColor.xyz = lerp(oColor.xyz, fogColour.xyz, fogValue);

	// output alpha
	oColor.a = diffuse.a;

	// logarithmic depth
	const float C = 0.1;
	const float far = 1000000000.0;
	const float offset = 1.0;
	oDepth = (log(C * depth + offset) / log(C * far + offset));
}