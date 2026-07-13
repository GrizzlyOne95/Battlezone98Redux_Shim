/*
 * Entry: 0047675b
 * Name: GetSkyTexture
 * Namespace: Global
 * Signature: TEXTURE * GetSkyTexture(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TEXTURE * __cdecl GetSkyTexture(void)

{
  return (TEXTURE *)Sky_Texture.Color;
}
