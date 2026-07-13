/*
 * Entry: 004fbc9a
 * Name: ReleaseSprites
 * Namespace: Global
 * Signature: int ReleaseSprites(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ReleaseSprites(void)

{
  UnlockSprites();
  spriteTableSize = 0;
  memset(spriteTable,0,0x10000);
  memset(spriteFile,0,0x8000);
  return 1;
}
