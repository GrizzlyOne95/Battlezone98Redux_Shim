/*
 * Entry: 004fb9c5
 * Name: ReadSpriteTableFile
 * Namespace: Global
 * Signature: int ReadSpriteTableFile(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl ReadSpriteTableFile(void)

{
  ushort *puVar1;
  int iVar2;
  uint uVar3;
  TEXTURE *pTVar4;
  int iVar5;
  ushort *puVar6;
  char *pcVar7;
  ushort *puVar8;
  SPRITE *pSVar9;
  SPRITE *pSVar10;
  bool bVar11;
  undefined8 uVar12;
  undefined4 local_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined1 local_a0 [136];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_a0;
  spriteZ = 0.0;
  uVar12 = 0;
  ClampZ();
  memset(nameTable,0,0x10000,uVar12);
  memset(spriteTable,0,0x10000);
  spriteTable[0].width = (int)badSprite.width;
  spriteTable[0].texPtr = &badSprite;
  spriteTable[0].u = 0;
  spriteTable[0].v = 0;
  spriteTable[0].height = badSprite.height;
  spriteTable[0].flags = 0;
  spriteTableSize = 1;
  pcVar7 = "spritea.stb";
  if ((useD3D & 4U) == 0) {
    pcVar7 = "sprite8.stb";
  }
  local_11c = *(undefined4 *)pcVar7;
  uStack_118 = *(undefined4 *)(pcVar7 + 4);
  uStack_114 = *(undefined4 *)(pcVar7 + 8);
  puVar1 = UseItem((char *)&local_11c);
  if (puVar1 == (ushort *)0x0) {
    DEBUG_systemWarning("Sprite table %s not found\n");
    iVar2 = 0;
  }
  else {
    uVar3 = GetItemSize((char *)&local_11c);
    if (puVar1 < puVar1 + (uVar3 / 0x34) * 0x1a) {
      puVar6 = puVar1 + 0x15;
      do {
        if (0x7ff < spriteTableSize) {
          spriteTableSize = 0x800;
          DEBUG_systemWarning("Sprite table overflow\n");
          break;
        }
        bVar11 = useD3D == 0;
        iVar2 = 8;
        puVar8 = puVar6 + -0x15;
        pcVar7 = nameTable[spriteTableSize];
        for (; iVar2 != 0; iVar2 = iVar2 + -1) {
          *(undefined4 *)pcVar7 = *(undefined4 *)puVar8;
          puVar8 = puVar8 + 2;
          pcVar7 = pcVar7 + 4;
        }
        if ((bVar11) && ((*(uint *)(puVar6 + 3) & 0xf) != 0)) {
          sprintf(local_18,"%.8s_%c.MAP",puVar6 + -5);
        }
        else {
          sprintf(local_18,"%.8s.MAP");
        }
        pTVar4 = UseItem(local_18);
        iVar2 = spriteTableSize;
        if (pTVar4 == (TEXTURE *)0x0) {
          DEBUG_systemWarning("Sprite texture file \"%s\" not found\n");
          iVar2 = spriteTableSize;
          pSVar9 = spriteTable;
          pSVar10 = spriteTable + spriteTableSize;
          for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
            pSVar10->u = pSVar9->u;
            pSVar9 = (SPRITE *)&pSVar9->v;
            pSVar10 = (SPRITE *)&pSVar10->v;
          }
          spriteFile[iVar2][0] = '\0';
        }
        else {
          spriteTable[spriteTableSize].texPtr = pTVar4;
          spriteTable[iVar2].u = (uint)puVar6[-1];
          spriteTable[iVar2].v = (uint)*puVar6;
          spriteTable[iVar2].width = (uint)puVar6[1];
          spriteTable[iVar2].height = (uint)puVar6[2];
          spriteTable[iVar2].flags = *(int *)(puVar6 + 3);
          strncpy(spriteFile[iVar2],(char *)(puVar6 + -5),0x10);
        }
        spriteTableSize = spriteTableSize + 1;
        puVar8 = puVar6 + 5;
        puVar6 = puVar6 + 0x1a;
      } while (puVar8 < puVar1 + (uVar3 / 0x34) * 0x1a);
    }
    UnlockItem((char *)&local_11c);
    iVar2 = 1;
  }
  return iVar2;
}
