/*
 * Entry: 005445f5
 * Name: Make_Texture_Handle
 * Namespace: Global
 * Signature: IDirect3DTexture9 * Make_Texture_Handle(int param_1, TEXTURE * param_2, int param_3, TEXTURE * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

IDirect3DTexture9 * __cdecl
Make_Texture_Handle(int param_1,TEXTURE *param_2,int param_3,TEXTURE **param_4)

{
  ushort uVar1;
  uint uVar2;
  ulong uVar3;
  int iVar4;
  long *plVar5;
  D3DCACHEENTRY *pDVar6;
  TEXTURE *pTVar7;
  int iVar8;
  short *unaff_EBX;
  D3DCACHEENTRY *unaff_ESI;
  uint uVar9;
  undefined4 *puVar10;
  TEXTURE **unaff_EDI;
  ulong local_10;
  long local_c;
  int local_8;
  
  uVar3 = Get_Frame_Count();
  uVar2 = *(uint *)(unaff_EBX + 2);
  uVar1 = unaff_EBX[1];
  uVar9 = (int)*unaff_EBX >> (2 < (short)uVar1) + (0 < (short)uVar1);
  if ((((((d3dappi.Caps.TextureCaps & 0x20) == 0) || (uVar9 == uVar2)) &&
       (((d3dappi.Caps.TextureCaps & 0x102) == 0 ||
        (((uVar9 & uVar9 - 1) == 0 && ((uVar2 & uVar2 - 1) == 0)))))) &&
      (uVar9 <= d3dappi.Caps.MaxTextureWidth)) && (uVar2 <= d3dappi.Caps.MaxTextureHeight)) {
    if (D3D_Video_Memory_Is_Dirty == 0) {
      if (textureCount < 0x1ff) {
        pTVar7 = param_2;
        if (uVar1 != 0) {
          pTVar7 = (TEXTURE *)(uint)uVar1;
        }
        if ((((D3IniFlags & 0x400U) != 0) && (param_2 != (TEXTURE *)0x0)) &&
           ((D3IniFlags & 0x800U) == 0)) {
          D3IniFlags = D3IniFlags | 0x1000;
        }
        iVar4 = D3D_Load_Texture((D3DCACHEENTRY *)param_3,unaff_EDI);
        if (iVar4 == 1) {
          if (param_1 < textureCount) {
            memmove(cache + param_1 + 1,cache + param_1,(textureCount - param_1) * 0x18);
          }
          textureCount = textureCount + 1;
          puVar10 = (undefined4 *)&stack0xffffffd4;
          pDVar6 = cache + param_1;
          for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
            pDVar6->texture = (TEXTURE *)*puVar10;
            puVar10 = puVar10 + 1;
            pDVar6 = (D3DCACHEENTRY *)&pDVar6->TransWidthHeight;
          }
          return (IDirect3DTexture9 *)0x0;
        }
        iVar4 = -1;
        local_c = textureCount;
        if (0 < textureCount) {
          local_8 = 0;
          plVar5 = &cache[0].timeStamp;
          local_10 = uVar3;
          do {
            if ((((D3D_CACHE_KEY *)(plVar5 + -1))->Key ==
                 (((((uint)(param_3 != 0) * 2 | uVar1 & 1) * 2 | (uint)pTVar7 & 1) << 0xc |
                  uVar2 & 0xfff) << 0xc | uVar9 & 0xfff)) && (*plVar5 < (int)local_10)) {
              iVar4 = local_8;
              local_10 = *plVar5;
            }
            local_c = local_c + -1;
            local_8 = local_8 + 1;
            plVar5 = plVar5 + 6;
          } while (0 < local_c);
          if ((iVar4 != -1) && ((int)local_10 < (int)(uVar3 - 1))) {
            pDVar6 = cache + iVar4;
            puVar10 = (undefined4 *)&stack0xffffffd4;
            for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
              *puVar10 = pDVar6->texture;
              pDVar6 = (D3DCACHEENTRY *)&pDVar6->TransWidthHeight;
              puVar10 = puVar10 + 1;
            }
            pDVar6 = Replace_Entry((long)unaff_EDI,unaff_ESI);
            if (pDVar6 != (D3DCACHEENTRY *)0x0) {
              D3DTextMisses = D3DTextMisses + 1;
              return pDVar6->lpD3DTex;
            }
          }
        }
        D3IniFlags = D3IniFlags & 0xfffd7fff;
        D3D_Video_Memory_Is_Dirty = 1;
      }
      else {
        D3D_Video_Memory_Is_Dirty = 1;
      }
    }
  }
  else {
    cacheName(unaff_EBX);
    DEBUG_systemWarning("Invalid size %dx%d for %s\n");
  }
  return (IDirect3DTexture9 *)0x0;
}
