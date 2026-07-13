/*
 * Entry: 00542bdf
 * Name: D3D_OverlayPalette
 * Namespace: Global
 * Signature: int D3D_OverlayPalette(VIDEO_DEVICE * param_1, RGB * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */

int __cdecl D3D_OverlayPalette(VIDEO_DEVICE *param_1,RGB *param_2)

{
  RGB *pRVar1;
  uchar *puVar2;
  RGB *pRVar3;
  byte bVar4;
  byte bVar5;
  uchar uVar6;
  uchar *puVar7;
  ulong (*pauVar8) [256];
  ushort *puVar9;
  ulong *puVar10;
  ulong *unaff_EDI;
  uint uVar11;
  ulong *puVar12;
  ulong *puVar13;
  undefined4 local_100c;
  int local_c10;
  ulong local_c0c [256];
  ulong local_80c [256];
  int local_40c [256];
  RGB *local_c;
  uchar *local_8;
  
  if (d3dappi.lpBackBuffer == (IDirect3DSurface9 *)0x0) {
    return 0;
  }
  if (param_2 != (RGB *)&WindowsPalette) {
    param_2->r = '\0';
    param_2->g = '\0';
    param_2->b = '\0';
    param_2[0xff].r = '\x01';
    param_2[0xff].g = '\x01';
    param_2[0xff].b = '\x01';
  }
  local_c = D3D_Current_Palette;
  puVar7 = &param_2->b;
  local_8 = (uchar *)0x0;
  do {
    pRVar1 = (RGB *)(puVar7 + -2);
    *(uchar *)((int)&local_100c + (int)local_8) = pRVar1->r;
    pRVar3 = local_c + 1;
    *(uchar *)((int)&local_100c + (int)local_8 + 1) = puVar7[-1];
    bVar4 = *puVar7;
    uVar6 = pRVar1->g;
    local_c->r = pRVar1->r;
    local_c->g = uVar6;
    local_c->b = *puVar7;
    bVar5 = pRVar1->r;
    *(byte *)((int)&local_100c + (int)local_8 + 2) = bVar4;
    *(undefined1 *)((int)&local_100c + (int)local_8 + 3) = 4;
    *(uint *)((int)D3D_Current_RGBA + (int)local_8) =
         ((bVar5 | 0xffffff00) << 8 | (uint)puVar7[-1]) << 8 | (uint)*puVar7;
    local_8 = (uchar *)((int)local_8 + 4);
    puVar7 = puVar7 + 3;
    local_c = pRVar3;
  } while ((int)pRVar3 < 0xc91ae0);
  uVar11 = D3IniFlags & 0x80000;
  puVar10 = local_c0c;
  if (uVar11 == 0) {
    build_Color_Lookup((ulong)puVar10,unaff_EDI);
    puVar12 = local_80c;
    build_Color_Lookup((ulong)puVar12,puVar10);
  }
  else {
    build_Color_Lookup((ulong)puVar10,unaff_EDI);
    puVar12 = local_80c;
    build_Color_Lookup((ulong)puVar12,puVar10);
  }
  build_Color_Lookup((ulong)local_40c,puVar12);
  puVar7 = &param_2->g;
  pauVar8 = D3D_Texture_Format_Remap_Palette;
  local_8 = puVar7;
  puVar10 = D3D_Texture_Format_Remap_Palette[1];
  do {
    puVar2 = puVar7 + 1;
    pRVar1 = (RGB *)(puVar7 + -1);
    bVar4 = *puVar7;
    puVar7 = puVar7 + 3;
    (*pauVar8)[0] = local_40c[*puVar2] + local_c0c[pRVar1->r] + local_80c[bVar4];
    pauVar8 = (ulong (*) [256])((int)pauVar8 + 4);
  } while ((int)pauVar8 < 0xc90fa0);
  puVar12 = &local_100c;
  if (uVar11 == 0) {
    build_Color_Lookup((ulong)puVar12,unaff_EDI);
    puVar13 = local_c0c;
    build_Color_Lookup((ulong)puVar13,puVar12);
    puVar12 = local_80c;
    build_Color_Lookup((ulong)puVar12,puVar13);
  }
  else {
    build_Color_Lookup((ulong)puVar12,unaff_EDI);
    puVar13 = local_c0c;
    build_Color_Lookup((ulong)puVar13,puVar12);
    puVar12 = local_80c;
    build_Color_Lookup((ulong)puVar12,puVar13);
  }
  build_Color_Lookup((ulong)local_40c,puVar12);
  puVar7 = local_8;
  do {
    puVar2 = puVar7 + 1;
    pRVar1 = (RGB *)(puVar7 + -1);
    bVar4 = *puVar7;
    puVar7 = puVar7 + 3;
    *puVar10 = local_40c[*puVar2] + local_c0c[pRVar1->r] + local_80c[bVar4] + local_c10;
    puVar10 = puVar10 + 1;
  } while ((int)puVar10 < 0xc9139c);
  D3D_Texture_Format_Remap_Palette[1][0xff] = 0;
  puVar10 = local_c0c;
  if (uVar11 == 0) {
    build_Color_Lookup((ulong)puVar10,unaff_EDI);
    puVar12 = local_80c;
    build_Color_Lookup((ulong)puVar12,puVar10);
  }
  else {
    build_Color_Lookup((ulong)puVar10,unaff_EDI);
    puVar12 = local_80c;
    build_Color_Lookup((ulong)puVar12,puVar10);
  }
  build_Color_Lookup((ulong)local_40c,puVar12);
  puVar9 = D3D_Remap_Palette;
  puVar7 = local_8;
  do {
    puVar2 = puVar7 + 1;
    pRVar1 = (RGB *)(puVar7 + -1);
    bVar4 = *puVar7;
    puVar7 = puVar7 + 3;
    *puVar9 = (short)local_40c[*puVar2] + (short)local_c0c[pRVar1->r] + (short)local_80c[bVar4];
    puVar9 = puVar9 + 1;
  } while ((int)puVar9 < 0xc91ce0);
  d3dappi.fogColor = D3D_Current_RGBA[Luminance_Table[0][0xdf]];
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetRenderState)
            (d3dappi.lpD3DDevice,D3DRS_FOGCOLOR,d3dappi.fogColor);
  return 1;
}
