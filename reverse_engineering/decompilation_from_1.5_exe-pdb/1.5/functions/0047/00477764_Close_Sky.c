/*
 * Entry: 00477764
 * Name: Close_Sky
 * Namespace: Global
 * Signature: void Close_Sky(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Close_Sky(void)

{
  if (Sky_Texture.Color != 0) {
    if (SkyTextureName[0] != '\0') {
      TexCache_UnlockTexture(SkyTextureName);
    }
    SkyTextureName[0] = '\0';
  }
  Sky_Texture.Color = 0;
  SunIndex = 0;
  Close_SkyBackdrop();
  Close_Clouds();
  Close_AnimatedSky();
  Close_Stars();
  return;
}
