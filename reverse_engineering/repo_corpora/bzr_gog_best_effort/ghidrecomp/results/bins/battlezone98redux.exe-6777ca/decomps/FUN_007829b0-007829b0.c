
void FUN_007829b0(int param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  int local_20;
  int local_1c;
  int local_18;
  undefined4 *local_14;
  int local_10;
  int local_c;
  undefined2 local_8;
  byte local_6;
  
  uVar2 = DAT_00920ef4;
  FUN_00687180(*(undefined4 *)(param_1 + 0x10));
  FUN_00780ff0(param_1,&local_18,&local_20,&local_1c,&local_2c);
  iVar3 = (local_1c - local_18) + 1;
  for (local_c = local_20; local_c <= local_2c; local_c = local_c + 1) {
    for (local_10 = local_18; local_10 <= local_1c; local_10 = local_10 + 1) {
      FUN_007825e0(local_10,local_c);
    }
  }
  FUN_00785920();
  for (local_c = local_20; local_c < local_2c; local_c = local_c + 1) {
    for (local_10 = local_18; local_10 < local_1c; local_10 = local_10 + 1) {
      iVar4 = ((local_c - local_20) * iVar3 + local_10) - local_18;
      iVar5 = iVar4 + 1;
      iVar7 = iVar5 + iVar3;
      local_14 = (undefined4 *)(iVar4 * 0xc + DAT_02cecf70);
      local_24 = (undefined4 *)(iVar5 * 0xc + DAT_02cecf70);
      local_28 = (undefined4 *)((iVar7 + -1) * 0xc + DAT_02cecf70);
      iVar4 = FUN_00780dc0(local_10,local_c,iVar7 * 0xc + DAT_02cecf70);
      uVar1 = *(undefined2 *)(&DAT_02cd9140 + iVar4 * 3);
      local_6 = (&DAT_02cd9142)[iVar4 * 3];
      local_8._0_1_ = (byte)uVar1;
      local_8._1_1_ = (byte)((ushort)uVar1 >> 8);
      uVar6 = (uint)(byte)local_8 << 0x10 | 0xff000000 | (uint)local_8._1_1_ << 8 | (uint)local_6;
      local_8 = uVar1;
      FUN_006871c0(*local_14,local_14[1],local_14[2],*local_24,local_24[1],local_24[2],uVar6);
      FUN_006871c0(*local_14,local_14[1],local_14[2],*local_28,local_28[1],local_28[2],uVar6);
    }
  }
  FUN_006856e0();
  DAT_00920ef4 = uVar2;
  return;
}

