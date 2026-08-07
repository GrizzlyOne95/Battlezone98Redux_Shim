void terrain_vertex(
	float4 iPosition : POSITION,
	in float3 iNormal : NORMAL,
	in float2 iUV : TEXCOORD0,
	in float4 iDiffuse : COLOR,
	in float heightOffset : TEXCOORD1,

	out float2 UV : TEXCOORD0,
	out float4 oPosition : POSITION,
	out float3 normal : TEXCOORD2,
	out float3 positionObjSpace : TEXCOORD4,
	out float4 diffuse : COLOR,
	out float depth : TEXCOORD5,

	uniform float4x4 wvpMat
)
{
	iPosition.y = heightOffset;
	positionObjSpace = iPosition.xyz;
	oPosition = mul(wvpMat, iPosition);
	UV = iUV;
	normal = iNormal;
	depth = oPosition.z;
	diffuse = iDiffuse;
}

// -------------------------------------------

void terrain_fragment(
	out float4 oColor : COLOR,
	out float oDepth : DEPTH,

	in float2 iUV : TEXCOORD0,
	in float3 iNormal : TEXCOORD2,
	in float3 positionObjSpace : TEXCOORD4,
	in float depth : TEXCOORD5,
	in float4 diffuse : COLOR,

	uniform sampler2D diffuseMap : register(s0),
	uniform sampler2D detailMap : register(s1),

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
	// per-pixel view normal
	float3 viewPos = mul(worldViewMat, float4(positionObjSpace.xyz, 1)).xyz;
	float3 viewNormal = normalize(mul(worldViewMat, float4(iNormal.xyz, 0)).xyz);

	// per-pixel direction to the eyepoint
	float3 eyeDir = normalize(/* cameraPosInViewSpace = float3(0,0,0) */ - viewPos.xyz);

	// start with ambient light and no specular
	float3 lightResult = sceneAmbient.xyz * materialAmbient.xyz;

	// get the direction from the pixel to the light source
	float3 pixelToLight = lightPosition[0].xyz - (viewPos * lightPosition[0].w);
	float d = length(pixelToLight);
	pixelToLight /= d;

	// if the pixel is facing the light...
	float NdotL = dot(viewNormal, pixelToLight);
	if (NdotL > 0.0)
	{
		// compute distance attentuation
		float attenuation = saturate(1.0 / 
			(lightAttenuation[0].y + d * (lightAttenuation[0].z + d * lightAttenuation[0].w)));

		// compute spotlight attenuation
		// it's much faster to just do the math than have a branch on low-end GPUs
		// non-spotlights have falloff power 0 which yields a constant output
		attenuation *= pow(saturate(
			(dot(pixelToLight, normalize(-lightDirection[0].xyz)) - spotLightParams[0].y) /
			(spotLightParams[0].x - spotLightParams[0].y)), spotLightParams[0].z);

		// accumulate diffuse lighting
		lightResult.xyz += materialDiffuse.xyz * lightDiffuse[0].xyz * attenuation * NdotL;
	}

	// diffuse texture
	float4 diffuseTex = tex2D(diffuseMap, iUV);
	oColor.xyz = lightResult.xyz * diffuseTex.xyz * diffuse.xyz;

	// detail texture
	float3 detailTex = tex2D(detailMap, frac(iUV * 8)).xyz * 2;
	float3 fullbrightDetail = float3(1, 1, 1);
	float detailDistance = saturate(depth * 0.025);
	float3 detailColor = lerp(detailTex, fullbrightDetail, detailDistance);
	oColor.xyz = lerp(oColor.xyz, oColor.xyz * detailColor, diffuseTex.a);

	// fog
	float fogValue = saturate((depth - fogParams.y) * fogParams.w);
	oColor.xyz = lerp(oColor.xyz, fogColour, fogValue);

	// output alpha
	oColor.a = diffuse.a;

	// logarithmic depth
	const float C = 0.1;
	const float far = 1000000000.0;
	const float offset = 1.0;
	oDepth = (log(C * depth + offset) / log(C * far + offset));
}