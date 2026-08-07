#define FXAA_PC 1
#define FXAA_HLSL_3 1 
#define FXAA_GREEN_AS_LUMA 1 
#define FXAA_QUALITY__PRESET 39

#include "Fxaa3_11.h"

float4 fxaa_ps (
		uniform sampler2D RT : register(s0),
		uniform float4 texSize,
		float2 iTexCoord : TEXCOORD0, 
		float2 pos : TEXCOORD1
	) : COLOR
{
	float screenWidthInPixels = texSize.x;
	float screenHeightInPixels = texSize.y;
	
	float N = 0.50;
	float4 fxaaConsoleRcpFrameOpt = float4(-N/screenWidthInPixels, -N/screenHeightInPixels,  N/screenWidthInPixels, N/screenHeightInPixels);
	float4 fxaaConsoleRcpFrameOpt2 = float4(-2.0/screenWidthInPixels, -2.0/screenHeightInPixels,  2.0/screenWidthInPixels, 2.0/screenHeightInPixels);
	float4 fxaaConsole360RcpFrameOpt2 = float4(8.0/screenWidthInPixels, 8.0/screenHeightInPixels,  -4.0/screenWidthInPixels, -4.0/screenHeightInPixels);
	float fxaaQualitySubpix = 0.75;
	float fxaaQualityEdgeThreshold = 0.063;
	float fxaaQualityEdgeThresholdMin = 0.0625;
	float fxaaConsoleEdgeSharpness = 8.0;
	float fxaaConsoleEdgeThreshold = 0.125;
	float fxaaConsoleEdgeThresholdMin = 0.05;
	float fxaaConsole360ConstDir = float4(1.0, -1.0, 0.25, -0.25);
	
	return FxaaPixelShader( iTexCoord, 
							pos.xyxy, 
							RT, 
							RT, 
							RT, 
							float2(1.0 / screenWidthInPixels, 1.0 / screenHeightInPixels),
							fxaaConsoleRcpFrameOpt,
							fxaaConsoleRcpFrameOpt2,
							fxaaConsole360RcpFrameOpt2,
							fxaaQualitySubpix,
							fxaaQualityEdgeThreshold,
							fxaaQualityEdgeThresholdMin, 
							fxaaConsoleEdgeSharpness,
							fxaaConsoleEdgeThreshold,
							fxaaConsoleEdgeThresholdMin,
							fxaaConsole360ConstDir);
}
