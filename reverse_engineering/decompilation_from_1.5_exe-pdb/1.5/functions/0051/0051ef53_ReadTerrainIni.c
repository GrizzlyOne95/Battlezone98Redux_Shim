/*
 * Entry: 0051ef53
 * Name: ReadTerrainIni
 * Namespace: Global
 * Signature: void ReadTerrainIni(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ReadTerrainIni(void)

{
  float fVar1;
  UINT UVar2;
  int iVar3;
  INT nDefault;
  int extraout_EAX;
  long extraout_EAX_00;
  float10 extraout_ST0;
  float10 fVar4;
  float10 extraout_ST0_00;
  float10 extraout_ST1;
  float10 fVar5;
  LPCSTR lpFileName;
  
  waveEnable = GetPrivateProfileIntA("NormalView","Waves",0,&cfgFileName);
  UVar2 = GetPrivateProfileIntA("NormalView","VisibilityScale",100,&cfgFileName);
  fVar1 = (float)(int)UVar2;
  if ((int)UVar2 < 0) {
    fVar1 = fVar1 + 4.2949673e+09;
  }
  visibilityScale = fVar1 * 0.01;
  iVar3 = Net_IsInternetGame();
  if ((iVar3 != 0) && (1.5 < visibilityScale)) {
    visibilityScale = 1.5;
  }
  lpFileName = &cfgFileName;
  _ftol2_sse();
  UVar2 = GetPrivateProfileIntA("SateliteView","VisibilityRange",nDefault,lpFileName);
  SateliteView.Visibility_Range = (float)(int)UVar2;
  if ((int)UVar2 < 0) {
    SateliteView.Visibility_Range = SateliteView.Visibility_Range + 4.2949673e+09;
  }
  TerrainSeparateDraw =
       GetPrivateProfileIntA("Debug","SeparateDraw",TerrainSeparateDraw,&cfgFileName);
  faceMask = GetPrivateProfileIntA("Debug","FaceMask",faceMask,&cfgFileName);
  useDisplayInterface = GetPrivateProfileIntA("Debug","HUD",useDisplayInterface,&cfgFileName);
  NormalView.Fog_Start = GetINIInt("NormalView","FogStart",100,missionName);
  NormalView.Fog_End = GetINIInt("NormalView","FogEnd",0xfa,missionName);
  iVar3 = GetINIInt("NormalView","FogBreak",0x32,missionName);
  NormalView.Fog_Break = (float)iVar3 * 0.01;
  iVar3 = GetINIInt("NormalView","VisibilityRange",0xfa,missionName);
  NormalView.Visibility_Range = (float)iVar3;
  iVar3 = GetINIInt("NormalView","FlatRange",0xfa,missionName);
  NormalView.Flat_Range = (float)iVar3;
  iVar3 = GetINIInt("NormalView","Intensity",0x1e,missionName);
  NormalView.Intensity = (float)iVar3 * 0.01;
  iVar3 = GetINIInt("NormalView","Ambient",0,missionName);
  NormalView.Ambient = (float)iVar3 * 0.01;
  iVar3 = GetINIInt("NormalView","ShadowLuma",0x4b,missionName);
  ShadowLuma = (float)iVar3 * 0.01;
  iVar3 = GetINIInt("NormalView","TerrainShadowLuma",0x32,missionName);
  TerrainShadowLuma = (float)iVar3 * 0.01;
  iVar3 = GetINIInt("NormalView","carAmbient",0x37,missionName);
  carAmbient = (float)iVar3 * 0.01;
  FogDirection = GetINIInt("NormalView","FogDirection",1,missionName);
  EmptyZoneElevation = GetINIInt("Size","Height",0,missionName);
  iVar3 = GetINIInt("NormalView","GroundFogTop",0,missionName);
  groundFogTop = iVar3 * 10;
  iVar3 = GetINIInt("NormalView","GroundFogBottom",0,missionName);
  groundFogBottom = iVar3 * 10;
  groundFogStart = GetINIInt("NormalView","GroundFogStart",0x3c,missionName);
  NormalView.Visibility_Range = NormalView.Visibility_Range * visibilityScale;
  _ftol2_sse();
  NormalView.Flat_Range = (float)((float10)NormalView.Flat_Range * extraout_ST1);
  fVar4 = (float10)1640.0;
  fVar5 = extraout_ST0;
  if (fVar4 < extraout_ST0) {
    NormalView.Visibility_Range = (float)fVar4;
    fVar5 = fVar4;
  }
  if (fVar4 < (float10)SateliteView.Visibility_Range) {
    SateliteView.Visibility_Range = (float)fVar4;
  }
  if (carAmbient * 255.0 < (float)inShadow) {
    carAmbient = (float)inShadow * 0.003921569;
  }
  if ((ShadowLuma < 0.0 != (ShadowLuma == 0.0)) || (1.0 < ShadowLuma)) {
    ShadowLuma = carAmbient;
  }
  SateliteView.Intensity = NormalView.Intensity;
  SateliteView.Ambient = NormalView.Ambient;
  fVar4 = extraout_ST1;
  NormalView.Fog_End = extraout_EAX;
  if (((float10)NormalView.Fog_Start < fVar5 - (float10)14.0) &&
     (fVar5 - (float10)14.15 < (float10)extraout_EAX)) {
    _ftol2_sse();
    fVar4 = extraout_ST0_00;
    NormalView.Fog_End = extraout_EAX_00;
  }
  if (NormalView.Fog_Break < 0.01) {
    NormalView.Fog_Break = 0.01;
  }
  if (0.99 < NormalView.Fog_Break) {
    NormalView.Fog_Break = 0.99;
  }
  if ((0 < groundFogTop - groundFogBottom) && (0 < NormalView.Fog_End - NormalView.Fog_Start)) {
    groundFogScale =
         (float)((fVar4 * (float10)(NormalView.Fog_End - NormalView.Fog_Start) * (float10)10.0) /
                (float10)(groundFogTop - groundFogBottom));
  }
  if ((useD3D != 0) && (((byte)D3IniFlags & 1) != 0)) {
    LODInfo.mergeBSP = 0;
    TerrainSeparateDraw = 1;
  }
  return;
}
