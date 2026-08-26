void terrain_vertex(
	uniform float4x4 wvpMat,
	uniform float4 diffuseColor,

	in float4 iPosition : POSITION,
	in float4 iColor : COLOR0,
	in uint2 iBlendIndices : BLENDINDICES,
	in float heightOffset : TEXCOORD1,

	out float4 vColor : COLOR0,
	out float2 vTexCoord : TEXCOORD0,
	out float vDepth : TEXCOORD1,

	out float4 oPosition : POSITION
)
{
	iPosition.y = heightOffset;

	oPosition = mul(wvpMat, iPosition);
	vColor = iColor * diffuseColor;
	vTexCoord = float2(iBlendIndices) / 160.0;
	vDepth = oPosition.z;
}

// -------------------------------------------

void terrain_fragment(
	uniform sampler2D diffuseMap : register(s0),

	uniform float4 fogColour,
	uniform float4 fogParams,

	in float4 vColor : COLOR,
	in float2 vTexCoord : TEXCOORD0,
	in float vDepth : TEXCOORD1,

	out float4 oColor : COLOR
#ifdef LOGDEPTH_ENABLE	
	, out float oDepth : DEPTH
#endif
)
{
	// diffuse texture
	float3 diffuseTex = tex2D(diffuseMap, vTexCoord).xyz;
	oColor.xyz = diffuseTex.xyz;

	// fog
	float fogValue = saturate((vDepth - fogParams.y) * fogParams.w);
	oColor.xyz = lerp(oColor.xyz, fogColour.xyz, fogValue);

	// output alpha
	oColor.a = vColor.a;

#ifdef LOGDEPTH_ENABLE
	// logarithmic depth
	const float C = 0.1;
	const float far = 1e+09;
	const float offset = 1.0;
	oDepth = log(C * vDepth + offset) / log(C * far + offset);
#endif
}