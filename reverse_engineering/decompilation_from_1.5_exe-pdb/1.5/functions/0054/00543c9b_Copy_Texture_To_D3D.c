/*
 * Entry: 00543c9b
 * Name: Copy_Texture_To_D3D
 * Namespace: Global
 * Signature: T_HRESULT Copy_Texture_To_D3D(_D3DLOCKED_RECT * param_1, _D3DSURFACE_DESC * param_2, D3DCACHEENTRY * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __cdecl
Copy_Texture_To_D3D(_D3DLOCKED_RECT *param_1,_D3DSURFACE_DESC *param_2,D3DCACHEENTRY *param_3)

{
  int iVar1;
  ushort *puVar2;
  short sVar3;
  int iVar4;
  short *psVar5;
  ulong *puVar6;
  undefined2 *puVar7;
  ushort uVar8;
  ushort uVar9;
  int *in_EAX;
  ulong *puVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  byte bVar13;
  ushort uVar14;
  int *in_ECX;
  undefined2 *puVar15;
  ushort *puVar16;
  int iVar17;
  undefined4 *in_EDX;
  uint uVar18;
  ushort *puVar19;
  int iVar20;
  int iVar21;
  int local_20;
  int local_18;
  int local_14;
  ushort *local_c;
  int local_8;
  
  iVar4 = *in_ECX;
  psVar5 = (short *)*in_EDX;
  iVar20 = (int)*psVar5;
  local_8 = *(int *)(psVar5 + 2);
  if (psVar5[1] == 0) {
    uVar18 = *(byte *)((int)in_EDX + 7) & 1;
    local_c = (ushort *)(psVar5 + 4);
    if ((*in_EAX == 0x15) || (*in_EAX == 0x16)) {
      puVar10 = (ulong *)in_ECX[1];
      for (; iVar1 = iVar20, puVar6 = puVar10, puVar16 = local_c, 0 < local_8;
          local_8 = local_8 + -1) {
        for (; 0 < iVar1; iVar1 = iVar1 + -1) {
          *puVar6 = D3D_Texture_Format_Remap_Palette[uVar18][*(byte *)puVar16];
          puVar6 = puVar6 + 1;
          puVar16 = (ushort *)((int)puVar16 + 1);
        }
        puVar10 = (ulong *)((int)puVar10 + iVar4);
        local_c = (ushort *)((int)local_c + iVar20);
      }
    }
    else {
      puVar15 = (undefined2 *)in_ECX[1];
      for (; iVar1 = iVar20, puVar7 = puVar15, puVar16 = local_c, 0 < local_8;
          local_8 = local_8 + -1) {
        for (; 0 < iVar1; iVar1 = iVar1 + -1) {
          *puVar7 = (short)D3D_Texture_Format_Remap_Palette[uVar18][*(byte *)puVar16];
          puVar7 = puVar7 + 1;
          puVar16 = (ushort *)((int)puVar16 + 1);
        }
        puVar15 = (undefined2 *)((int)puVar15 + iVar4);
        local_c = (ushort *)((int)local_c + iVar20);
      }
    }
  }
  else {
    sVar3 = psVar5[1];
    if (sVar3 == 1) {
      local_c = (ushort *)(psVar5 + 4);
      iVar1 = (uint)(byte)((UserProfilePtr->graphicDetail).brightness + 1) * 0x100 + 0xd3f080;
      if ((*in_EAX == 0x15) || (*in_EAX == 0x16)) {
        if (0 < local_8) {
          puVar12 = (undefined1 *)(in_ECX[1] + 1);
          do {
            if (0 < iVar20) {
              local_18 = (iVar20 - 1U >> 1) + 1;
              puVar11 = puVar12;
              puVar16 = local_c;
              do {
                puVar11[1] = *(undefined1 *)((*(byte *)((int)puVar16 + 1) & 0xf) * 0x11 + iVar1);
                *puVar11 = *(undefined1 *)((*puVar16 >> 4 & 0xf) * 0x11 + iVar1);
                puVar11[-1] = *(undefined1 *)((*puVar16 & 0xf) * 0x11 + iVar1);
                bVar13 = (byte)(*puVar16 >> 0xc);
                puVar11[2] = bVar13 ^ bVar13 << 4;
                puVar16 = puVar16 + 1;
                puVar11 = puVar11 + 4;
                local_18 = local_18 + -1;
              } while (local_18 != 0);
            }
            puVar12 = puVar12 + iVar4;
            local_8 = local_8 + -1;
            local_c = (ushort *)((int)local_c + iVar20);
          } while (0 < local_8);
        }
      }
      else {
        puVar16 = (ushort *)in_ECX[1];
        for (; 0 < local_8; local_8 = local_8 + -1) {
          if (0 < iVar20) {
            local_14 = (iVar20 - 1U >> 1) + 1;
            puVar19 = puVar16;
            do {
              puVar2 = (ushort *)((int)puVar19 + ((int)local_c - (int)puVar16));
              uVar8 = *puVar19;
              uVar9 = (ushort)(*(byte *)((*(byte *)((int)puVar2 + 1) & 0xf) * 0x11 + iVar1) >> 4) <<
                      8;
              *puVar19 = uVar9 | uVar8 & 0xf0ff;
              uVar14 = (ushort)(*(byte *)((*puVar2 >> 4 & 0xf) * 0x11 + iVar1) >> 4) << 4;
              *puVar19 = uVar14 | uVar9 | uVar8 & 0xf00f;
              uVar8 = (ushort)(*(byte *)((*puVar2 & 0xf) * 0x11 + iVar1) >> 4) |
                      uVar14 | uVar9 | uVar8 & 0xf000;
              *puVar19 = uVar8;
              *puVar19 = (*puVar2 ^ uVar8) & 0xfff ^ *puVar2;
              puVar19 = puVar19 + 1;
              local_14 = local_14 + -1;
            } while (local_14 != 0);
          }
          puVar16 = (ushort *)((int)puVar16 + iVar4);
          local_c = (ushort *)((int)local_c + iVar20);
        }
      }
    }
    else if (sVar3 == 2) {
      local_c = (ushort *)(psVar5 + 4);
      iVar1 = (uint)(byte)((UserProfilePtr->graphicDetail).brightness + 1) * 0x100 + 0xd3f080;
      if ((*in_EAX == 0x15) || (*in_EAX == 0x16)) {
        if (0 < local_8) {
          puVar12 = (undefined1 *)(in_ECX[1] + 1);
          do {
            if (0 < iVar20) {
              local_20 = (iVar20 - 1U >> 1) + 1;
              puVar11 = puVar12;
              puVar16 = local_c;
              do {
                puVar11[1] = *(undefined1 *)
                              ((uint)(*puVar16 >> 0xd) + iVar1 + (uint)(*puVar16 >> 0xb) * 8);
                *puVar11 = *(undefined1 *)((*puVar16 >> 9 & 3) + iVar1 + (*puVar16 >> 5 & 0x3f) * 4)
                ;
                puVar11[-1] = *(undefined1 *)((*puVar16 >> 2 & 7) + iVar1 + (*puVar16 & 0x1f) * 8);
                puVar16 = puVar16 + 1;
                puVar11 = puVar11 + 4;
                local_20 = local_20 + -1;
              } while (local_20 != 0);
            }
            puVar12 = puVar12 + iVar4;
            local_8 = local_8 + -1;
            local_c = (ushort *)((int)local_c + iVar20);
          } while (0 < local_8);
        }
      }
      else {
        iVar17 = in_ECX[1];
        for (; 0 < local_8; local_8 = local_8 + -1) {
          if (0 < iVar20) {
            local_18 = (iVar20 - 1U >> 1) + 1;
            puVar16 = local_c;
            do {
              puVar19 = (ushort *)((iVar17 - (int)local_c) + (int)puVar16);
              uVar8 = *puVar19;
              uVar9 = (ushort)(*(byte *)((uint)(*puVar16 >> 0xd) + iVar1 +
                                        (uint)(*puVar16 >> 0xb) * 8) >> 3) << 0xb;
              *puVar19 = uVar9 | uVar8 & 0x7ff;
              uVar14 = (ushort)(*(byte *)((*puVar16 >> 9 & 3) + iVar1 + (*puVar16 >> 5 & 0x3f) * 4)
                               >> 2) << 5;
              *puVar19 = uVar14 | uVar9 | uVar8 & 0x1f;
              uVar8 = *puVar16;
              puVar16 = puVar16 + 1;
              local_18 = local_18 + -1;
              *puVar19 = (ushort)(*(byte *)((uVar8 >> 2 & 7) + iVar1 + (uVar8 & 0x1f) * 8) >> 3) |
                         uVar14 | uVar9;
            } while (local_18 != 0);
          }
          iVar17 = iVar17 + iVar4;
          local_c = (ushort *)((int)local_c + iVar20);
        }
      }
    }
    else if ((sVar3 == 3) || (sVar3 == 4)) {
      local_c = (ushort *)(psVar5 + 4);
      iVar17 = in_ECX[1];
      iVar1 = (uint)(byte)((UserProfilePtr->graphicDetail).brightness + 1) * 0x100 + 0xd3f080;
      for (; 0 < local_8; local_8 = local_8 + -1) {
        if (0 < iVar20) {
          puVar12 = (undefined1 *)((int)local_c + 3);
          puVar11 = (undefined1 *)(iVar17 + 1);
          iVar21 = (iVar20 - 1U >> 2) + 1;
          do {
            puVar11[1] = *(undefined1 *)((uint)(byte)puVar12[-1] + iVar1);
            *puVar11 = *(undefined1 *)((uint)(byte)puVar11[(int)local_c - iVar17] + iVar1);
            puVar11[-1] = *(undefined1 *)((uint)(byte)puVar12[-3] + iVar1);
            puVar11[2] = *puVar12;
            puVar12 = puVar12 + 4;
            puVar11 = puVar11 + 4;
            iVar21 = iVar21 + -1;
          } while (iVar21 != 0);
        }
        iVar17 = iVar17 + iVar4;
        local_c = (ushort *)((int)local_c + iVar20);
      }
    }
  }
  return 0;
}
