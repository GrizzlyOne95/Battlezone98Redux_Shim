/*
 * Entry: 0051fe64
 * Name: GetTexelInfo
 * Namespace: Global
 * Signature: TEXTURE * GetTexelInfo(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TEXTURE * __cdecl GetTexelInfo(long param_1,long param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  TEXTURE **ppTVar5;
  int local_c;
  
  if ((D3IniFlags & 0x4000U) == 0) {
    uVar3 = (uint)TileIndex[pre_minM][pre_maxM][pre_var][pre_cap];
    fVar2 = ((float)param_1 + 0.5) - Terrain.Eye_Point.x;
    fVar1 = ((float)param_2 + 0.5) - Terrain.Eye_Point.z;
    if (uVar3 != 0) {
      iVar4 = 0;
      ppTVar5 = TileTexturePtr + uVar3;
      do {
        local_c = SUB84((double)(fVar1 * fVar1 + fVar2 * fVar2 + (float)Float2Int),0);
        if ((local_c <= mipDistance2[iVar4]) && (*ppTVar5 != (TEXTURE *)0x0)) {
          pre_idx = iVar4 + uVar3;
          return *ppTVar5;
        }
        iVar4 = iVar4 + 1;
        ppTVar5 = ppTVar5 + 1;
      } while (iVar4 < 4);
    }
  }
  else {
    pre_idx = (int)TileIndex[pre_minM][pre_maxM][pre_var][pre_cap];
    if ((pre_idx != 0) && (TileTexturePtr[pre_idx] != (TEXTURE *)0x0)) {
      return TileTexturePtr[pre_idx];
    }
  }
  pre_idx = 0;
  return &badTexture;
}
