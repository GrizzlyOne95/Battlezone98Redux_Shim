/*
 * Entry: 00543b2a
 * Name: Reset_Texture_Struct
 * Namespace: Global
 * Signature: void Reset_Texture_Struct(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Reset_Texture_Struct(void)

{
  textureCount = 0;
  cache[0].texture = (TEXTURE *)0x7fffffff;
  return;
}
