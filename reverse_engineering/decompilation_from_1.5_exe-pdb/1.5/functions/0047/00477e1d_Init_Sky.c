/*
 * Entry: 00477e1d
 * Name: Init_Sky
 * Namespace: Global
 * Signature: void Init_Sky(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_Sky(void)

{
  Sky_Texture.Color = 0;
  SunIndex = 0;
  SkyHeight = GetINIInt("Sky","SkyHeight",100,missionName);
  SkyType = GetINIInt("Sky","SkyType",0,missionName);
  Sky_Texture_U_Offset = 0.0;
  Sky_Texture_V_Offset = 0.0;
  GetINIString(secStr,"SkyTexture","",SkyTextureName,0x10,missionName);
  if (SkyTextureName[0] != '\0') {
    Sky_Texture.Texture = TexCache_UseTexture(SkyTextureName);
  }
  GetINIString(secStr,"SunTexture","",SunTextureName,0x10,missionName);
  if (SunTextureName[0] != '\0') {
    SunIndex = GetSpriteIndex(SunTextureName);
  }
  Init_SkyBackdrop();
  Init_Clouds();
  Init_AnimatedSky();
  Init_Stars();
  return;
}
