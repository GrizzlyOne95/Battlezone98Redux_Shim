/*
 * Entry: 004ede14
 * Name: Shadow_Init
 * Namespace: Global
 * Signature: void Shadow_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Shadow_Init(void)

{
  Shadow_Texture = TexCache_UseTexture("shadow.map");
  return;
}
