
void __fastcall FUN_00596ba0(int *param_1)

{
  uint uVar1;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  local_8 = param_1;
  for (local_c = param_1[0x18]; local_c < local_8[0x1a]; local_c = local_c + 1) {
    for (local_10 = local_8[0x17]; local_10 < local_8[0x19]; local_10 = local_10 + 1) {
      local_1c = (float)local_10 * DAT_02cc50e0;
      local_24 = local_1c + DAT_02cc50e0;
      local_18 = (float)local_c * DAT_02cc50e0;
      local_20 = local_18 + DAT_02cc50e0;
      uVar1 = FUN_0077d640(local_10,local_c);
      local_14 = (&DAT_02cd9580)[uVar1 & 0xff];
      (**(code **)(*local_8 + 0x24))(local_1c,local_18,&local_34,&local_28);
      (**(code **)(*local_8 + 0x24))(local_24,local_20,&local_2c,&local_30);
      FUN_0068afb0(DAT_00917580,local_34,local_30,local_2c,local_28,local_14,0);
    }
  }
  return;
}

