/*
 * Entry: 004ef66d
 * Name: Stretch_Transparent_Bitmap
 * Namespace: Global
 * Signature: void Stretch_Transparent_Bitmap(BITMAP_BLIT_STRUCT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Stretch_Transparent_Bitmap(BITMAP_BLIT_STRUCT *param_1)

{
  long lVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  long *plVar6;
  uint uVar7;
  char *pcVar8;
  bool bVar9;
  int local_2c [3];
  char *local_20;
  char *local_1c;
  uint local_18;
  uint local_14;
  int local_10;
  int local_c;
  long local_8;
  
  iVar3 = param_1->Scale_y;
  local_2c[0] = (iVar3 >> 0x10) * param_1->Src_Pitch;
  local_2c[1] = param_1->Src_Pitch + local_2c[0];
  local_10 = 0;
  if (0 < param_1->off_y0) {
    local_10 = param_1->off_y0 * iVar3;
  }
  local_14 = 0;
  local_18 = iVar3 * 0x10000;
  if (0 < param_1->off_x0) {
    local_14 = param_1->Scale_x * param_1->off_x0;
  }
  local_20 = param_1->Src +
             ((local_10 >> 0x10) + param_1->src_y0) * param_1->Src_Pitch + param_1->src_x0;
  local_1c = param_1->Dst;
  local_2c[2] = param_1->Width;
  local_c = param_1->Dst_Pitch;
  local_8 = param_1->Height;
  uVar5 = param_1->Scale_x;
  uVar7 = uVar5 * 0x10000;
  uVar2 = local_14 << 0x10;
  local_14 = local_14 >> 0x10;
  iVar3 = -local_2c[2];
  do {
    Deltax[local_2c[2] + iVar3] = local_14;
    bVar9 = CARRY4(uVar2,uVar7);
    uVar2 = uVar2 + uVar7;
    local_14 = local_14 + (uVar5 >> 0x10) + (uint)bVar9;
    bVar9 = iVar3 < -1;
    iVar3 = iVar3 + 1;
  } while (bVar9);
  uVar5 = local_10 << 0x10;
  local_c = local_c - local_2c[2];
  do {
    lVar1 = local_8;
    plVar6 = Deltax;
    iVar3 = local_2c[2];
    do {
      iVar4 = *plVar6;
      pcVar8 = local_1c + 1;
      plVar6 = plVar6 + 1;
      if (local_20[iVar4] != -1) {
        *local_1c = local_20[iVar4];
      }
      iVar4 = iVar3 + -1;
      bVar9 = 0 < iVar3;
      iVar3 = iVar4;
      local_1c = pcVar8;
    } while (iVar4 != 0 && bVar9);
    bVar9 = CARRY4(uVar5,local_18);
    uVar5 = uVar5 + local_18;
    local_1c = pcVar8 + local_c;
    local_20 = local_20 + local_2c[iVar4 * 2 + (uint)bVar9];
    local_8 = local_8 + -1;
  } while (local_8 != 0 && 0 < lVar1);
  return;
}
