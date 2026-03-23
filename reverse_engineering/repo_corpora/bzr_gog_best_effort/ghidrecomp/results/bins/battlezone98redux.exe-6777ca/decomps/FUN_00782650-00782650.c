
void FUN_00782650(int param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  uint local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  int local_10;
  int local_c;
  undefined2 local_8;
  byte local_6;
  
  uVar2 = DAT_00920ef4;
  local_20 = 0xffffffff;
  FUN_00780ff0(param_1,&local_24,&local_2c,&local_28,&local_30);
  iVar6 = (local_28 - local_24) + 1;
  for (local_c = local_2c; local_c <= local_30; local_c = local_c + 1) {
    for (local_10 = local_24; local_10 <= local_28; local_10 = local_10 + 1) {
      FUN_007825e0(local_10,local_c);
    }
  }
  FUN_00785920();
  FUN_00687180(*(undefined4 *)(param_1 + 0x10));
  for (local_c = local_2c; local_c < local_30; local_c = local_c + 1) {
    for (local_10 = local_24; local_10 < local_28; local_10 = local_10 + 1) {
      iVar3 = ((local_c - local_2c) * iVar6 + local_10) - local_24;
      iVar5 = iVar3 + 1;
      iVar7 = iVar5 + iVar6;
      local_18 = (undefined4 *)(iVar3 * 0xc + DAT_02cecf70);
      local_14 = (undefined4 *)(iVar5 * 0xc + DAT_02cecf70);
      local_1c = (undefined4 *)(iVar7 * 0xc + DAT_02cecf70);
      iVar5 = (iVar7 + -1) * 0xc + DAT_02cecf70;
      iVar3 = FUN_007820f0(param_1,local_18,local_14,local_1c,iVar5);
      if ((iVar3 == 0) && (iVar3 = FUN_007816d0(local_18,local_14,local_1c,iVar5), iVar3 != 0)) {
        if (DAT_009454a8 == 1) {
          puVar4 = (ushort *)FUN_00492d60(local_10,local_c);
          local_20 = (&DAT_02cd9580)[((*puVar4 & 0xfff) * 0xff) / 0xfff];
        }
        else if (DAT_009454a8 == 2) {
          iVar3 = FUN_00780dc0(local_10,local_c);
          uVar1 = *(undefined2 *)(&DAT_02cd9140 + iVar3 * 3);
          local_6 = (&DAT_02cd9142)[iVar3 * 3];
          local_8._0_1_ = (byte)uVar1;
          local_8._1_1_ = (byte)((ushort)uVar1 >> 8);
          local_20 = (uint)(byte)local_8 << 0x10 | 0xff000000 | (uint)local_8._1_1_ << 8 |
                     (uint)local_6;
          local_8 = uVar1;
        }
        FUN_006871c0(*local_18,local_18[1],local_18[2],*local_14,local_14[1],local_14[2],local_20);
        FUN_006871c0(*local_14,local_14[1],local_14[2],*local_1c,local_1c[1],local_1c[2],local_20);
        FUN_006871c0(*local_1c,local_1c[1],local_1c[2],*local_18,local_18[1],local_18[2],local_20);
      }
    }
  }
  DAT_00920ef4 = uVar2;
  FUN_006856e0();
  return;
}

