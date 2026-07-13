/*
 * Entry: 004ce5e4
 * Name: FlagDisplay::PreLoad
 * Namespace: FlagDisplay
 * Signature: void PreLoad(FlagDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlagDisplay::PreLoad(FlagDisplay *this)

{
  int iVar1;
  bool bVar2;
  TEXTURE *pTVar3;
  TEXTURE *pTVar4;
  long *plVar5;
  int iVar6;
  TEXTURE **ppTVar7;
  
  this->flagIndex = 0;
  bVar2 = Net::IsNetGame();
  if (bVar2) {
    ppTVar7 = this->flagTexture;
    pTVar3 = malloc(0x4008);
    *ppTVar7 = pTVar3;
    pTVar3 = malloc(0x4008);
    this->flagTexture[1] = pTVar3;
    pTVar4 = malloc(0x4008);
    pTVar3 = *ppTVar7;
    this->flagTexture[2] = pTVar4;
    if ((((pTVar3 != (TEXTURE *)0x0) && (this->flagTexture[1] != (TEXTURE *)0x0)) &&
        (pTVar4 != (TEXTURE *)0x0)) && (spriteTableSize < 0x7e8)) {
      iVar6 = 3;
      this->flagIndex = spriteTableSize;
      do {
        (*ppTVar7)->type = 0;
        (*ppTVar7)->width = 0x80;
        (*ppTVar7)->height = 0x80;
        plVar5 = &FLAG_OFFSET[0].y;
        do {
          iVar1 = spriteTableSize;
          spriteTable[spriteTableSize].texPtr = *ppTVar7;
          spriteTable[iVar1].u = ((tagPOINT *)(plVar5 + -1))->x;
          spriteTable[iVar1].v = *plVar5;
          spriteTable[iVar1].width = 0x40;
          spriteTable[iVar1].height = 0x20;
          spriteTable[iVar1].flags = 0;
          spriteTableSize = spriteTableSize + 1;
          plVar5 = plVar5 + 2;
        } while ((int)plVar5 < 0x5e4b2c);
        ppTVar7 = ppTVar7 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  }
  this->makeTexture = false;
  return;
}
