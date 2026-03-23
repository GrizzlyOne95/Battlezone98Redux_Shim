
void FUN_00782c20(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  uint uVar5;
  ushort *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 local_28;
  int local_20;
  int local_1c;
  int local_18;
  undefined4 *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  uVar1 = DAT_00920ef4;
  FUN_00687180(*(undefined4 *)(param_1 + 0x10));
  FUN_00780ff0(param_1,&local_10,&local_1c,&local_18,&local_20);
  local_10 = local_10 >> 1;
  local_18 = local_18 + 1 >> 1;
  local_20 = local_20 + 1 >> 1;
  iVar7 = (local_18 - local_10) + 1;
  local_1c = local_1c >> 1;
  for (local_8 = local_1c; local_8 <= local_20; local_8 = local_8 + 1) {
    for (local_c = local_10; local_c <= local_18; local_c = local_c + 1) {
      FUN_007825e0(local_c << 1,local_8 << 1);
    }
  }
  FUN_00785920();
  for (local_8 = local_1c; local_8 < local_20; local_8 = local_8 + 1) {
    for (local_c = local_10; local_c < local_18; local_c = local_c + 1) {
      iVar8 = ((local_8 - local_1c) * iVar7 + local_c) - local_10;
      iVar9 = iVar8 + 1;
      iVar2 = iVar9 + iVar7;
      local_14 = (undefined4 *)(iVar8 * 0xc + DAT_02cecf70);
      puVar3 = (undefined4 *)(iVar9 * 0xc + DAT_02cecf70);
      puVar10 = (undefined4 *)((iVar2 + -1) * 0xc + DAT_02cecf70);
      pbVar4 = (byte *)FUN_0050ce30(local_c * 2 + 1,local_8 * 2 + 1,iVar2 * 0xc + DAT_02cecf70);
      uVar5 = ((uint)*pbVar4 * 0x1f) / 0xff;
      puVar6 = (ushort *)FUN_004c0fe0(local_c << 1,local_8 << 1);
      if ((int)(*puVar6 & 0xf000) >> 0xc == DAT_008f05c8) {
        local_28 = *(undefined4 *)(&DAT_02cd9460 + uVar5 * 4);
      }
      else {
        local_28 = *(undefined4 *)(&DAT_02cd9500 + uVar5 * 4);
      }
      FUN_006871c0(*local_14,local_14[1],local_14[2],*puVar3,puVar3[1],puVar3[2],local_28);
      FUN_006871c0(*local_14,local_14[1],local_14[2],*puVar10,puVar10[1],puVar10[2],local_28);
    }
  }
  DAT_00920ef4 = uVar1;
  FUN_006856e0();
  return;
}

