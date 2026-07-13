/*
 * Entry: 004ede25
 * Name: Shadow_Cleanup
 * Namespace: Global
 * Signature: void Shadow_Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Shadow_Cleanup(void)

{
  TexCache_UnlockTexture("shadow.map");
  Shadow_Texture = (TEXTURE *)0x0;
  return;
}
