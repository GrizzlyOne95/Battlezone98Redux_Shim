/*
 * Entry: 004fbc12
 * Name: UnlockSprites
 * Namespace: Global
 * Signature: int UnlockSprites(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UnlockSprites(void)

{
  int iVar1;
  
  iVar1 = 1;
  if (1 < spriteTableSize) {
    iVar1 = spriteTableSize;
  }
  UnlockItem(spriteFile[iVar1]);
  return 1;
}
