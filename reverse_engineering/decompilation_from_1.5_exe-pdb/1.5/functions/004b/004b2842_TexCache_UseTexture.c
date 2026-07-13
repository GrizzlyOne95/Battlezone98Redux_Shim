/*
 * Entry: 004b2842
 * Name: TexCache_UseTexture
 * Namespace: Global
 * Signature: TEXTURE * TexCache_UseTexture(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

TEXTURE * __cdecl TexCache_UseTexture(char *param_1)

{
  char cVar1;
  ushort uVar2;
  ulong uVar3;
  float fVar4;
  undefined4 *puVar5;
  char *pcVar6;
  _texcache *p_Var7;
  _texcache *extraout_EAX;
  long lVar8;
  TEXTURE *pTVar9;
  VQTEXTURE *pVVar10;
  VQCODEBOOK *pVVar11;
  int iVar12;
  _texcache *unaff_EDI;
  undefined4 *puVar13;
  undefined1 local_1c [4];
  char local_18 [4];
  undefined1 auStack_14 [12];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  nTexAccesses = nTexAccesses + 1;
  pcVar6 = param_1;
  do {
    cVar1 = *pcVar6;
    pcVar6[(int)(local_18 + -(int)param_1)] = cVar1;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  pcVar6 = strchr(local_18,0x2e);
  if (pcVar6 != (char *)0x0) {
    *pcVar6 = '\0';
  }
  puVar5 = (undefined4 *)(local_1c + 3);
  do {
    puVar13 = puVar5;
    puVar5 = (undefined4 *)((int)puVar13 + 1);
  } while (*(char *)((int)puVar13 + 1) != '\0');
  *(undefined4 *)((int)puVar13 + 1) = 0x6d71762e;
  *(undefined1 *)((int)puVar13 + 5) = 0;
  p_Var7 = find_texture(local_18);
  if (p_Var7 != (_texcache *)0x0) {
    if (p_Var7->count == 0) {
      remove_from_purge(unaff_EDI);
      p_Var7 = extraout_EAX;
    }
    p_Var7->count = p_Var7->count + 1;
    nTexHits = nTexHits + 1;
    return p_Var7->umap;
  }
  if (AddonFirst == 0) {
    lVar8 = GetItemSize(local_18);
    if (lVar8 == 0) {
      nTexNotComp = nTexNotComp + 1;
      pTVar9 = UseItem(param_1);
      return pTVar9;
    }
  }
  else {
    pTVar9 = UseItem(param_1);
    if (pTVar9 != (TEXTURE *)0x0) {
      nTexNotComp = nTexNotComp + 1;
      return pTVar9;
    }
    lVar8 = GetItemSize(local_18);
    if (lVar8 == 0) {
      DEBUG_systemWarning("Error:texture %s not found for !");
      return (TEXTURE *)0x0;
    }
  }
  pVVar10 = UseItem(local_18);
  local_1c = (undefined1  [4])pVVar10->codebook;
  pVVar11 = UseItem((char *)local_1c);
  if (pVVar11 == (VQCODEBOOK *)0x0) {
    DEBUG_systemWarning("Error: Codebook %s not found for texture %s!");
LAB_004b2942:
    UnlockItem(local_18);
  }
  else {
    uVar2 = pVVar10->wide;
    uVar3 = pVVar10->high;
    num_purges_temp = 0;
    do {
      pTVar9 = malloc((uint)pVVar10->wide * pVVar10->high + 8);
      if (pTVar9 != (TEXTURE *)0x0) {
        fVar4 = (float)(int)num_purges_temp;
        if ((int)num_purges_temp < 0) {
          fVar4 = fVar4 + 4.2949673e+09;
        }
        nTexPurgesPerAlloc = nTexPurgesPerAlloc * 0.9 + fVar4 * 0.1;
        iVar12 = VQ_DecompressTexture(pVVar10,pVVar11,pTVar9,uVar2 * uVar3 + 0x18);
        if (iVar12 == 0) {
          pcVar6 = "Error: Could not decompress texture %s";
        }
        else {
          p_Var7 = add_texture_to_texcache(local_18);
          if (p_Var7 != (_texcache *)0x0) {
            p_Var7->umap = pTVar9;
            p_Var7->count = 1;
            UnlockItem((char *)local_1c);
            UnlockItem(local_18);
            nTexMisses = nTexMisses + 1;
            return pTVar9;
          }
          pcVar6 = "Error: unable to add texture %s to cache";
        }
        DEBUG_systemWarning(pcVar6);
        UnlockItem((char *)local_1c);
        goto LAB_004b2942;
      }
      iVar12 = purge_head_item();
    } while (iVar12 != 0);
    DEBUG_systemWarning("Error: Texture cache overflow!");
    dump_tcache_contents();
    UnlockItem((char *)local_1c);
    UnlockItem(local_18);
  }
  return (TEXTURE *)0x0;
}
