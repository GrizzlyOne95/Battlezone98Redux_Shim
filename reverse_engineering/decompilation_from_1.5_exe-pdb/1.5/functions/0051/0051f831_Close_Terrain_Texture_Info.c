/*
 * Entry: 0051f831
 * Name: Close_Terrain_Texture_Info
 * Namespace: Global
 * Signature: void Close_Terrain_Texture_Info(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Close_Terrain_Texture_Info(void)

{
  char (*pacVar1) [16];
  int iVar2;
  
  iVar2 = 0;
  if (0 < TileFileCount) {
    pacVar1 = TileFileName;
    do {
      if ((*pacVar1)[0] != '\0') {
        UnlockItem(*pacVar1);
      }
      iVar2 = iVar2 + 1;
      pacVar1 = pacVar1 + 1;
    } while (iVar2 < TileFileCount);
  }
  memset(TileFileName,0,0x1000);
  memset(TileIndex,0,0x200);
  TileFileCount = 0;
  Close_AnimatedScrounge();
  return;
}
