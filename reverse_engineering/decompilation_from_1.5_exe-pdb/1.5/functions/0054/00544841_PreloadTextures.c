/*
 * Entry: 00544841
 * Name: PreloadTextures
 * Namespace: Global
 * Signature: int PreloadTextures(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl PreloadTextures(void)

{
  TEXTURE *pTVar1;
  int iVar2;
  long lVar3;
  char *pcVar4;
  short sVar5;
  int iVar6;
  char *unaff_ESI;
  TEXTURE *unaff_EDI;
  undefined4 *puVar7;
  undefined4 *puVar8;
  char *pcVar9;
  int local_28;
  void *local_24;
  int local_20;
  TEXTURE **local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if ((D3IniFlags & 0x4000U) == 0) {
    iVar6 = 1;
    if (1 < TileFileCount) {
      do {
        pTVar1 = TileTexturePtr[iVar6];
        lVar3 = FindTextureIndex(unaff_EDI);
        if (cache[lVar3].texture != pTVar1) {
          Make_Texture_Handle(lVar3,(TEXTURE *)0x0,0,(TEXTURE **)unaff_EDI);
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < TileFileCount);
    }
  }
  else if (4 < TileFileCount) {
    local_1c = (TEXTURE **)0x4;
    puVar7 = &DAT_00caf4ec;
    do {
      pTVar1 = (TEXTURE *)puVar7[-2];
      local_20 = FindTextureIndex(unaff_EDI);
      if (cache[local_20].texture != pTVar1) {
        iVar6 = (int)*(short *)puVar7[-1];
        if (((int)pTVar1->width == iVar6 * 2) &&
           (iVar2 = *(int *)((short *)puVar7[-1] + 2), pTVar1->height == iVar2 * 2)) {
          local_24 = (void *)(int)*(short *)*puVar7;
          if ((iVar6 != (int)local_24 * 2) ||
             (((iVar6 = *(int *)((short *)*puVar7 + 2), iVar2 != iVar6 * 2 ||
               (local_24 != (void *)(*(short *)puVar7[1] * 2))) ||
              (iVar6 != *(int *)((short *)puVar7[1] + 2) * 2)))) goto LAB_005448e2;
          puVar8 = puVar7 + -2;
        }
        else {
LAB_005448e2:
          puVar8 = (undefined4 *)0x0;
        }
        Make_Texture_Handle(local_20,(TEXTURE *)0x0,(int)puVar8,(TEXTURE **)unaff_EDI);
      }
      local_1c = local_1c + 1;
      puVar7 = puVar7 + 4;
    } while ((int)local_1c < TileFileCount);
  }
  if (D3D_Video_Memory_Is_Dirty != 0) {
    D3IniFlags = D3IniFlags & 0xfffd7fff;
  }
  if ((D3IniFlags & 0x28000U) != 0) {
    local_20 = 1;
    if (1 < spriteTableSize) {
      local_1c = &spriteTable[1].texPtr;
      do {
        pTVar1 = *local_1c;
        lVar3 = FindTextureIndex(unaff_EDI);
        if ((cache[lVar3].texture != pTVar1) &&
           (((sVar5 = pTVar1->width >> (2 < pTVar1->type) + (0 < pTVar1->type), sVar5 == 0x80 &&
             (pTVar1->height == 0x80)) || ((sVar5 == 0x100 && (pTVar1->height == 0x100)))))) {
          Make_Texture_Handle(lVar3,(TEXTURE *)0x0,0,(TEXTURE **)unaff_EDI);
        }
        local_20 = local_20 + 1;
        local_1c = local_1c + 8;
      } while (local_20 < spriteTableSize);
    }
    if (D3D_Video_Memory_Is_Dirty != 0) {
      D3IniFlags = D3IniFlags & 0xfffd7fff;
    }
  }
  if ((D3IniFlags & 0x8000U) != 0) {
    GetSkyTexture();
    PreloadOneTexture(unaff_EDI);
    GetBackdropTexture();
    PreloadOneTexture(unaff_EDI);
    iVar6 = 0;
    do {
      GetCloudTexture(iVar6);
      PreloadOneTexture(unaff_EDI);
      iVar6 = iVar6 + 1;
    } while (iVar6 < 8);
    iVar6 = 0;
    do {
      GetStarTexture(iVar6);
      PreloadOneTexture(unaff_EDI);
      iVar6 = iVar6 + 1;
    } while (iVar6 < 0x40);
    pcVar9 = "shadow.map";
    TexCache_UseTexture("shadow.map");
    PreloadOneTexture((TEXTURE *)pcVar9);
    local_24 = zixReadFile("map.lst",&local_28);
    if (local_24 != (void *)0x0) {
      pcVar9 = (char *)(local_28 + (int)local_24);
      while (pcVar4 = GetNextFileName(pcVar9,(char *)0x8,".MAP",(int)unaff_EDI,unaff_ESI),
            pcVar4 != (char *)0x0) {
        if (local_18[0] != '\0') {
          TexCache_UseTexture(local_18);
          PreloadOneTexture(unaff_EDI);
        }
      }
      zixFree(local_24);
    }
    if (D3D_Video_Memory_Is_Dirty != 0) {
      D3IniFlags = D3IniFlags & 0xffff7fff;
    }
  }
  D3D_Video_Memory_Is_Dirty = 0;
  return 1;
}
