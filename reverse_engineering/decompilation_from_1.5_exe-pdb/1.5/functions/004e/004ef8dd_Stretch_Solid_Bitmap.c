/*
 * Entry: 004ef8dd
 * Name: Stretch_Solid_Bitmap
 * Namespace: Global
 * Signature: void Stretch_Solid_Bitmap(BITMAP_BLIT_STRUCT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void __cdecl Stretch_Solid_Bitmap(BITMAP_BLIT_STRUCT *param_1)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint *puVar10;
  uint uVar11;
  undefined1 *puVar12;
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
  
  iVar4 = param_1->Scale_y;
  local_2c[0] = (iVar4 >> 0x10) * param_1->Src_Pitch;
  local_2c[1] = param_1->Src_Pitch + local_2c[0];
  local_8 = 0;
  if (0 < param_1->off_y0) {
    local_8 = param_1->off_y0 * iVar4;
  }
  local_18 = 0;
  local_20 = iVar4 * 0x10000;
  if (0 < param_1->off_x0) {
    local_18 = param_1->Scale_x * param_1->off_x0;
  }
  local_1c = param_1->Src +
             ((local_8 >> 0x10) + param_1->src_y0) * param_1->Src_Pitch + param_1->src_x0;
  local_24 = (uint *)param_1->Dst;
  iVar4 = param_1->Width;
  local_c = iVar4;
  iVar5 = param_1->Dst_Pitch;
  local_10 = param_1->Height;
  local_14 = iVar5;
  uVar9 = param_1->Scale_x;
  uVar11 = uVar9 * 0x10000;
  uVar6 = local_18 << 0x10;
  local_18 = local_18 >> 0x10;
  iVar7 = -iVar4;
  do {
    bVar13 = CARRY4(uVar6,uVar11);
    uVar6 = uVar6 + uVar11;
    local_18 = local_18 + (uVar9 >> 0x10) + (uint)bVar13;
    local_202c[iVar4 + iVar7] = local_18;
    bVar13 = iVar7 < -1;
    iVar7 = iVar7 + 1;
  } while (bVar13);
  if (iVar4 < 9) {
    puVar12 = (undefined1 *)((int)local_24 + iVar4);
    uVar9 = local_8 << 0x10;
    local_c = -iVar4;
    do {
      iVar7 = -iVar4;
      do {
        puVar12[iVar7] = local_1c[local_202c[iVar4 + iVar7]];
        iVar8 = iVar7 + 1;
        bVar13 = iVar7 < -1;
        iVar7 = iVar8;
      } while (bVar13);
      puVar12 = puVar12 + iVar5;
      bVar13 = CARRY4(uVar9,local_20);
      uVar9 = uVar9 + local_20;
      local_1c = local_1c + local_2c[iVar8 * 2 + (uint)bVar13];
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  else {
    uVar9 = local_8 << 0x10;
    local_14 = iVar5 - iVar4;
    do {
      puVar10 = local_202c;
      uVar6 = -(int)local_24 & 3;
      iVar7 = iVar4 - uVar6;
      for (; uVar6 != 0; uVar6 = uVar6 - 1) {
        uVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        *(char *)local_24 = local_1c[uVar11];
        local_24 = (uint *)((int)local_24 + 1);
      }
      do {
        iVar7 = iVar7 + -4;
        uVar6 = *puVar10;
        puVar1 = puVar10 + 1;
        puVar2 = puVar10 + 2;
        puVar3 = puVar10 + 3;
        puVar10 = puVar10 + 4;
        *local_24 = (uint)CONCAT11(local_1c[*puVar1],local_1c[uVar6]) |
                    CONCAT22(CONCAT11(local_1c[*puVar1],local_1c[uVar6]),
                             CONCAT11(local_1c[*puVar3],local_1c[*puVar2])) << 0x10;
        local_24 = local_24 + 1;
      } while (3 < iVar7);
      for (; iVar7 != 0; iVar7 = iVar7 + -1) {
        uVar6 = *puVar10;
        puVar10 = puVar10 + 1;
        *(char *)local_24 = local_1c[uVar6];
        local_24 = (uint *)((int)local_24 + 1);
      }
      local_24 = (uint *)((int)local_24 + (iVar5 - iVar4));
      bVar13 = CARRY4(uVar9,local_20);
      uVar9 = uVar9 + local_20;
      local_1c = local_1c + local_2c[bVar13];
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  return;
}
