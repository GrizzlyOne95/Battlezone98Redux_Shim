/*
 * Entry: 004cf662
 * Name: MapJChar
 * Namespace: Global
 * Signature: int MapJChar(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl MapJChar(ushort param_1)

{
  byte bVar1;
  TEXTURE *pTVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  undefined1 *puVar6;
  int iVar7;
  short *psVar8;
  char *pcVar9;
  undefined1 *puVar10;
  short sVar11;
  byte *pbVar12;
  int local_10;
  int local_c;
  byte *local_8;
  
  iVar3 = IsJapanese();
  if ((iVar3 != 0) && (iVar3 = GetJCharIndex(param_1), iVar3 < charCount)) {
    iVar4 = (int)charMap[iVar3];
    if (iVar4 == 0) {
      iVar4 = freeSprite;
      if (freeSprite == usedSprite) {
        iVar4 = freeSprite + -1;
      }
      freeSprite = iVar4 + 1;
      pTVar2 = spriteTable[iVar4].texPtr;
      PrintChar(param_1);
      if (use16 == false) {
        local_8 = (byte *)charBuffer;
        puVar6 = (undefined1 *)
                 ((int)&pTVar2[spriteTable[iVar4].v * 8 + 1].width + spriteTable[iVar4].u);
        local_10 = 0xc;
        do {
          local_c = 0xc;
          puVar10 = puVar6;
          pbVar12 = local_8;
          do {
            bVar1 = *pbVar12;
            pbVar12 = pbVar12 + 1;
            if ((uint)bVar1 == DisplayInterface::colorWhite) {
              *puVar10 = (char)DisplayInterface::colorWhite;
            }
            else {
              *puVar10 = 0xff;
            }
            puVar10 = puVar10 + 1;
            local_c = local_c + -1;
          } while (local_c != 0);
          local_8 = local_8 + 0x10;
          puVar6 = puVar6 + 0x40;
          local_10 = local_10 + -1;
        } while (local_10 != 0);
      }
      else {
        pcVar9 = charBuffer;
        psVar5 = &pTVar2[spriteTable[iVar4].v * 0x10 + 1].width + spriteTable[iVar4].u;
        local_c = 0xc;
        do {
          local_8 = (byte *)0xc;
          psVar8 = psVar5;
          pbVar12 = (byte *)pcVar9;
          do {
            bVar1 = *pbVar12;
            pbVar12 = pbVar12 + 1;
            sVar11 = -1;
            if ((uint)bVar1 != DisplayInterface::colorWhite) {
              sVar11 = 0xfff;
            }
            *psVar8 = sVar11;
            psVar8 = psVar8 + 1;
            local_8 = (byte *)((int)local_8 + -1);
          } while (local_8 != (byte *)0x0);
          pcVar9 = pcVar9 + 0x10;
          psVar5 = psVar5 + 0x40;
          local_c = local_c + -1;
        } while (local_c != 0);
      }
      if ((useD3D != 0) && (iVar7 = D3D_Is_In_VideoMemory(pTVar2), iVar7 != 0)) {
        D3D_Video_Memory_Is_Dirty = 1;
      }
      charMap[iVar3] = (short)iVar4;
    }
    return iVar4;
  }
  return firstSprite;
}
