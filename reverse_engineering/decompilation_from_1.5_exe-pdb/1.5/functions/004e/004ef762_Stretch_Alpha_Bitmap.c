/*
 * Entry: 004ef762
 * Name: Stretch_Alpha_Bitmap
 * Namespace: Global
 * Signature: void Stretch_Alpha_Bitmap(BITMAP_BLIT_STRUCT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Stretch_Alpha_Bitmap(BITMAP_BLIT_STRUCT *param_1)

{
  char cVar1;
  undefined3 uVar2;
  undefined3 uVar3;
  long lVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  long *plVar8;
  uint uVar9;
  uchar *puVar10;
  bool bVar11;
  int local_2c [3];
  char *local_20;
  uchar *local_1c;
  uint local_18;
  uint local_14;
  int local_10;
  int local_c;
  long local_8;
  
  iVar6 = param_1->Scale_y;
  local_2c[0] = (iVar6 >> 0x10) * param_1->Src_Pitch;
  local_2c[1] = param_1->Src_Pitch + local_2c[0];
  local_10 = 0;
  if (0 < param_1->off_y0) {
    local_10 = param_1->off_y0 * iVar6;
  }
  local_14 = 0;
  local_18 = iVar6 * 0x10000;
  if (0 < param_1->off_x0) {
    local_14 = param_1->Scale_x * param_1->off_x0;
  }
  local_20 = param_1->Src +
             ((local_10 >> 0x10) + param_1->src_y0) * param_1->Src_Pitch + param_1->src_x0;
  local_1c = (uchar *)param_1->Dst;
  local_2c[2] = param_1->Width;
  local_c = param_1->Dst_Pitch;
  local_8 = param_1->Height;
  uVar7 = param_1->Scale_x;
  uVar9 = uVar7 * 0x10000;
  uVar5 = local_14 << 0x10;
  local_14 = local_14 >> 0x10;
  iVar6 = -local_2c[2];
  do {
    Deltax[local_2c[2] + iVar6] = local_14;
    bVar11 = CARRY4(uVar5,uVar9);
    uVar5 = uVar5 + uVar9;
    local_14 = local_14 + (uVar7 >> 0x10) + (uint)bVar11;
    bVar11 = iVar6 < -1;
    iVar6 = iVar6 + 1;
  } while (bVar11);
  uVar7 = local_10 << 0x10;
  local_c = local_c - local_2c[2];
  do {
    lVar4 = local_8;
    plVar8 = Deltax;
    uVar9 = (uint)local_2c[2] >> 1;
    uVar5 = uVar9;
    if ((local_2c[2] & 1U) == 0) {
LAB_004ef84d:
      do {
        while( true ) {
          while( true ) {
            uVar2 = CONCAT21((short)((uint)*plVar8 >> 0x10),local_20[*plVar8]);
            cVar1 = local_20[plVar8[1]];
            uVar3 = CONCAT21((short)((uint)plVar8[1] >> 0x10),cVar1);
            if (local_20[*plVar8] != -1) break;
            if (cVar1 == -1) {
              puVar10 = local_1c + 2;
              plVar8 = plVar8 + 2;
              uVar9 = uVar5 - 1;
              bVar11 = (int)uVar5 < 1;
              uVar5 = uVar9;
              local_1c = puVar10;
              if (uVar9 == 0 || bVar11) goto LAB_004ef86b;
            }
            else {
              puVar10 = local_1c + 2;
              plVar8 = plVar8 + 2;
              local_1c[1] = Headlight_Mask_Luma[0][CONCAT31(uVar3,local_1c[1])];
              uVar9 = uVar5 - 1;
              bVar11 = (int)uVar5 < 1;
              uVar5 = uVar9;
              local_1c = puVar10;
              if (uVar9 == 0 || bVar11) goto LAB_004ef86b;
            }
          }
          if (cVar1 == -1) break;
          puVar10 = local_1c + 2;
          plVar8 = plVar8 + 2;
          *(ushort *)local_1c =
               CONCAT11(Headlight_Mask_Luma[0][CONCAT31(uVar3,local_1c[1])],
                        Headlight_Mask_Luma[0][CONCAT31(uVar2,*local_1c)]);
          uVar9 = uVar5 - 1;
          bVar11 = (int)uVar5 < 1;
          uVar5 = uVar9;
          local_1c = puVar10;
          if (uVar9 == 0 || bVar11) goto LAB_004ef86b;
        }
        puVar10 = local_1c + 2;
        plVar8 = plVar8 + 2;
        *local_1c = Headlight_Mask_Luma[0][CONCAT31(uVar2,*local_1c)];
        uVar9 = uVar5 - 1;
        bVar11 = 0 < (int)uVar5;
        uVar5 = uVar9;
        local_1c = puVar10;
      } while (uVar9 != 0 && bVar11);
    }
    else {
      puVar10 = local_1c + 1;
      plVar8 = Deltax + 1;
      if (local_20[Deltax[0]] != -1) {
        *local_1c = Headlight_Mask_Luma[0]
                    [CONCAT31(CONCAT21((short)((uint)Deltax[0] >> 0x10),local_20[Deltax[0]]),
                              *local_1c)];
      }
      local_1c = puVar10;
      if ((short)uVar9 != 0) goto LAB_004ef84d;
    }
LAB_004ef86b:
    bVar11 = CARRY4(uVar7,local_18);
    uVar7 = uVar7 + local_18;
    local_1c = puVar10 + local_c;
    local_20 = local_20 + local_2c[uVar9 * 2 + (uint)bVar11];
    local_8 = local_8 + -1;
    if (local_8 == 0 || lVar4 < 1) {
      return;
    }
  } while( true );
}
