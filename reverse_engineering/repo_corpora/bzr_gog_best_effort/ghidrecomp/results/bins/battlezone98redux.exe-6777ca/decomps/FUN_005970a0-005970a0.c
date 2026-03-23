
void __fastcall FUN_005970a0(int *param_1)

{
  uint uVar1;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  DAT_02cd9580 = DAT_00917584;
  DAT_02cd9584 = DAT_00917588;
  DAT_02cd9588 = DAT_00917578;
  DAT_02cd958c = DAT_00917558;
  DAT_02cd9590 = DAT_009175b0;
  DAT_02cd9594 = DAT_00917560;
  DAT_02cd9598 = DAT_0091757c;
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    for (local_10 = 0; local_10 < 6; local_10 = local_10 + 1) {
      (&DAT_02cd9580)[(local_c + 1) * 6 + 1 + local_10] =
           (&DAT_02cd9580)[local_c * 6 + 1 + local_10] + 1;
    }
  }
  local_8 = param_1;
  for (local_14 = param_1[0x18]; local_14 < local_8[0x1a]; local_14 = local_14 + 1) {
    for (local_18 = local_8[0x17]; local_18 < local_8[0x19]; local_18 = local_18 + 1) {
      local_20 = (float)local_18 * DAT_02cc50e0;
      local_28 = local_20 + DAT_02cc50e0;
      local_1c = (float)local_14 * DAT_02cc50e0;
      local_24 = local_1c + DAT_02cc50e0;
      uVar1 = FUN_0046adb0(local_18,local_14);
      local_2c = (&DAT_02cd9580)[uVar1 & 0xff];
      (**(code **)(*local_8 + 0x24))(local_20,local_1c,&local_3c,&local_30);
      (**(code **)(*local_8 + 0x24))(local_28,local_24,&local_34,&local_38);
      FUN_0068afb0(DAT_00917580,local_3c,local_38,local_34,local_30,local_2c,0);
    }
  }
  return;
}

