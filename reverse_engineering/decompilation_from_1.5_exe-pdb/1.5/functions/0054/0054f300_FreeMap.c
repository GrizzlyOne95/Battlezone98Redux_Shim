/*
 * Entry: 0054f300
 * Name: FreeMap
 * Namespace: Global
 * Signature: void FreeMap(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FreeMap(void)

{
  Graphic_Buffer_Close(&mapTextureGB);
  if (mapTexture != (TEXTURE *)0x0) {
    UnlockRDItem(mapName,1,4);
    mapTexture = (TEXTURE *)0x0;
  }
  return;
}
