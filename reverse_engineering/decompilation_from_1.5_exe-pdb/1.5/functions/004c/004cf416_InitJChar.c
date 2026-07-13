/*
 * Entry: 004cf416
 * Name: InitJChar
 * Namespace: Global
 * Signature: void InitJChar(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitJChar(void)

{
  int iVar1;
  TEXTURE *pTVar2;
  SPRITE *pSVar3;
  SPRITE *pSVar4;
  bool bVar5;
  int iVar6;
  TEXTURE **ppTVar7;
  int iVar8;
  short local_c;
  ushort local_4;
  
  iVar1 = IsJapanese();
  if (iVar1 != 0) {
    charCount = J_Font->char_count;
    charMap = operator_new__(-(uint)((int)((ulonglong)(uint)charCount * 2 >> 0x20) != 0) |
                             (uint)((ulonglong)(uint)charCount * 2));
    memset(charMap,0,charCount * 2);
    bVar5 = (bool)((byte)useD3D >> 1 & 1);
    firstSprite = spriteTableSize;
    freeSprite = spriteTableSize;
    iVar1 = 0x1000;
    if (bVar5 != false) {
      iVar1 = 0x2000;
    }
    ppTVar7 = charTexture;
    use16 = bVar5;
    do {
      pTVar2 = malloc(iVar1 + 8);
      *ppTVar7 = pTVar2;
      local_4 = (ushort)(bVar5 != false);
      pTVar2->type = local_4;
      local_c = (short)(0x40 << (bVar5 != false));
      (*ppTVar7)->width = local_c;
      (*ppTVar7)->height = 0x40;
      pTVar2 = *ppTVar7;
      iVar6 = 0;
      pSVar3 = spriteTable + spriteTableSize;
      spriteTableSize = spriteTableSize + 0x19;
      do {
        iVar8 = 0;
        pSVar4 = pSVar3 + 5;
        do {
          pSVar3->texPtr = pTVar2;
          pSVar3->u = iVar8;
          pSVar3->v = iVar6;
          pSVar3->width = 0xc;
          pSVar3->height = 0xc;
          pSVar3->flags = 0;
          iVar8 = iVar8 + 0xc;
          pSVar3 = pSVar3 + 1;
        } while (iVar8 < 0x3c);
        iVar6 = iVar6 + 0xc;
        pSVar3 = pSVar4;
      } while (iVar6 < 0x3c);
      pTVar2 = pTVar2 + 1;
      if (bVar5 == false) {
        memset(pTVar2,0xff,0x1000);
      }
      else {
        for (iVar6 = 0x800; iVar6 != 0; iVar6 = iVar6 + -1) {
          pTVar2->width = 0xfff;
          pTVar2->type = 0xfff;
          pTVar2 = (TEXTURE *)&pTVar2->height;
        }
      }
      ppTVar7 = ppTVar7 + 1;
    } while ((int)ppTVar7 < 0xb78a00);
    usedSprite = spriteTableSize;
  }
  return;
}
