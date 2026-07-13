
void __fastcall FUN_00596cf0(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  undefined4 local_18;
  uint local_14;
  int *local_10;
  int local_c;
  int local_8;
  
  for (local_14 = 0; (int)local_14 < 0x100; local_14 = local_14 + 1) {
    (&DAT_02cd9580)[local_14] =
         (local_14 & 0xff) << 0x10 | 0xff000000 |
         ((int)(local_14 * 0xe0) / 0xff + 0x1fU & 0xff) << 8 |
         (int)(local_14 * 0xc0) / 0xff + 0x3fU & 0xff;
  }
  local_10 = param_1;
  for (local_8 = param_1[0x18]; local_8 < local_10[0x1a]; local_8 = local_8 + 1) {
    for (local_c = local_10[0x17]; local_c < local_10[0x19]; local_c = local_c + 1) {
      local_30 = (float)local_c * DAT_02cc50e0;
      local_38 = local_30 + DAT_02cc50e0;
      local_2c = (float)local_8 * DAT_02cc50e0;
      local_34 = local_2c + DAT_02cc50e0;
      local_24 = FUN_0077d640(local_c,local_8);
      local_28 = FUN_0077d640(local_c + 1,local_8);
      local_1c = FUN_0077d640(local_c,local_8 + 1);
      local_20 = FUN_0077d640(local_c + 1,local_8 + 1);
      uVar3 = local_1c - local_24 >> 0x1f;
      uVar4 = local_20 - local_1c >> 0x1f;
      uVar1 = FUN_0043d130((local_20 - local_1c ^ uVar4) - uVar4,
                           (local_1c - local_24 ^ uVar3) - uVar3);
      uVar3 = local_28 - local_20 >> 0x1f;
      uVar4 = local_24 - local_28 >> 0x1f;
      uVar1 = FUN_0043d130((local_24 - local_28 ^ uVar4) - uVar4,
                           (local_28 - local_20 ^ uVar3) - uVar3,uVar1);
      local_18 = FUN_0043d130(uVar1);
      iVar2 = FUN_0046b550(local_18,0xff);
      local_18 = (&DAT_02cd9580)[iVar2];
      (**(code **)(*local_10 + 0x24))(local_30,local_2c,&local_48,&local_3c);
      (**(code **)(*local_10 + 0x24))(local_38,local_34,&local_40,&local_44);
      FUN_0068afb0(DAT_00917580,local_48,local_44,local_40,local_3c,local_18,0);
    }
  }
  return;
}

