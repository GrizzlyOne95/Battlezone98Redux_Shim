/*
 * Entry: 004fbc34
 * Name: ReloadSprites
 * Namespace: Global
 * Signature: int ReloadSprites(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ReloadSprites(void)

{
  TEXTURE *pTVar1;
  int iVar2;
  char (*pacVar3) [16];
  int iVar4;
  SPRITE *pSVar5;
  SPRITE *pSVar6;
  SPRITE *local_4;
  
  iVar4 = 1;
  if (1 < spriteTableSize) {
    local_4 = spriteTable;
    pacVar3 = spriteFile;
    do {
      local_4 = local_4 + 1;
      pacVar3 = pacVar3 + 1;
      if (((*pacVar3)[0] == '\0') || (pTVar1 = UseItem(*pacVar3), pTVar1 == (TEXTURE *)0x0)) {
        pSVar5 = spriteTable;
        pSVar6 = local_4;
        for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
          pSVar6->u = pSVar5->u;
          pSVar5 = (SPRITE *)&pSVar5->v;
          pSVar6 = (SPRITE *)&pSVar6->v;
        }
      }
      else {
        spriteTable[spriteTableSize].texPtr = pTVar1;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < spriteTableSize);
  }
  return 1;
}
