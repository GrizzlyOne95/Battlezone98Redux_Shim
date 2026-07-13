/*
 * Entry: 004ef486
 * Name: Stretch_Translucent2_Bitmap
 * Namespace: Global
 * Signature: void Stretch_Translucent2_Bitmap(BITMAP_BLIT_STRUCT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void __cdecl Stretch_Translucent2_Bitmap(BITMAP_BLIT_STRUCT *param_1)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  ushort uVar8;
  uint uVar9;
  uint *puVar10;
  uint uVar11;
  uchar *puVar12;
  bool bVar13;
  uint local_202c [2048];
  int local_2c [2];
  uint *local_24;
  uint local_20;
  char *local_1c;
  uint local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar3 = param_1->Scale_y;
  local_2c[0] = (iVar3 >> 0x10) * param_1->Src_Pitch;
  local_2c[1] = param_1->Src_Pitch + local_2c[0];
  local_8 = 0;
  if (0 < param_1->off_y0) {
    local_8 = param_1->off_y0 * iVar3;
  }
  local_18 = 0;
  local_20 = iVar3 * 0x10000;
  if (0 < param_1->off_x0) {
    local_18 = param_1->Scale_x * param_1->off_x0;
  }
  local_1c = param_1->Src +
             ((local_8 >> 0x10) + param_1->src_y0) * param_1->Src_Pitch + param_1->src_x0;
  local_24 = (uint *)param_1->Dst;
  iVar3 = param_1->Width;
  local_c = iVar3;
  iVar4 = param_1->Dst_Pitch;
  local_10 = param_1->Height;
  local_14 = iVar4;
  uVar9 = param_1->Scale_x;
  uVar11 = uVar9 * 0x10000;
  uVar5 = local_18 << 0x10;
  local_18 = local_18 >> 0x10;
  iVar6 = -iVar3;
  do {
    bVar13 = CARRY4(uVar5,uVar11);
    uVar5 = uVar5 + uVar11;
    local_18 = local_18 + (uVar9 >> 0x10) + (uint)bVar13;
    local_202c[iVar3 + iVar6] = local_18;
    bVar13 = iVar6 < -1;
    iVar6 = iVar6 + 1;
  } while (bVar13);
  if (iVar3 < 9) {
    puVar12 = (uchar *)((int)local_24 + iVar3);
    uVar9 = local_8 << 0x10;
    local_c = -iVar3;
    do {
      iVar6 = -iVar3;
      do {
        puVar12[iVar6] =
             Translucency_Table[0]
             [CONCAT22((short)(local_202c[iVar3 + iVar6] >> 0x10),
                       CONCAT11(puVar12[iVar6],local_1c[local_202c[iVar3 + iVar6]]))];
        iVar7 = iVar6 + 1;
        bVar13 = iVar6 < -1;
        iVar6 = iVar7;
      } while (bVar13);
      puVar12 = puVar12 + iVar4;
      bVar13 = CARRY4(uVar9,local_20);
      uVar9 = uVar9 + local_20;
      local_1c = local_1c + local_2c[iVar7 * 2 + (uint)bVar13];
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  else {
    uVar9 = local_8 << 0x10;
    local_14 = iVar4 - iVar3;
    do {
      puVar10 = local_202c;
      uVar5 = -(int)local_24 & 3;
      iVar6 = iVar3 - uVar5;
      for (; uVar5 != 0; uVar5 = uVar5 - 1) {
        uVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        *(uchar *)local_24 =
             Translucency_Table[0]
             [CONCAT22((short)(uVar11 >> 0x10),CONCAT11((uchar)*local_24,local_1c[uVar11]))];
        local_24 = (uint *)((int)local_24 + 1);
      }
      do {
        iVar6 = iVar6 + -4;
        uVar8 = CONCAT11(Translucency_Table[0]
                         [CONCAT22((short)(puVar10[1] >> 0x10),
                                   CONCAT11(*(uchar *)((int)local_24 + 1),local_1c[puVar10[1]]))],
                         Translucency_Table[0]
                         [CONCAT22((short)(*puVar10 >> 0x10),
                                   CONCAT11((uchar)*local_24,local_1c[*puVar10]))]);
        puVar1 = puVar10 + 2;
        puVar2 = puVar10 + 3;
        puVar10 = puVar10 + 4;
        *local_24 = (uint)uVar8 |
                    CONCAT22(uVar8,CONCAT11(Translucency_Table[0]
                                            [CONCAT22((short)(*puVar2 >> 0x10),
                                                      CONCAT11(*(uchar *)((int)local_24 + 3),
                                                               local_1c[*puVar2]))],
                                            Translucency_Table[0]
                                            [CONCAT22((short)(*puVar1 >> 0x10),
                                                      CONCAT11(*(uchar *)((int)local_24 + 2),
                                                               local_1c[*puVar1]))])) << 0x10;
        local_24 = local_24 + 1;
      } while (3 < iVar6);
      for (; iVar6 != 0; iVar6 = iVar6 + -1) {
        uVar5 = *puVar10;
        puVar10 = puVar10 + 1;
        *(uchar *)local_24 =
             Translucency_Table[0]
             [CONCAT22((short)(uVar5 >> 0x10),CONCAT11((uchar)*local_24,local_1c[uVar5]))];
        local_24 = (uint *)((int)local_24 + 1);
      }
      local_24 = (uint *)((int)local_24 + (iVar4 - iVar3));
      bVar13 = CARRY4(uVar9,local_20);
      uVar9 = uVar9 + local_20;
      local_1c = local_1c + local_2c[bVar13];
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  return;
}
