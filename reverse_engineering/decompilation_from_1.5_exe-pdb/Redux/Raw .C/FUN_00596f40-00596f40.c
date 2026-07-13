
void __fastcall FUN_00596f40(int *param_1)

{
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  float local_28;
  float local_24;
  int local_20;
  float local_1c;
  float local_18;
  int local_14;
  int local_10;
  int *local_c;
  undefined1 local_5;
  
  local_c = param_1;
  for (local_10 = param_1[0x18]; local_10 < local_c[0x1a]; local_10 = local_10 + 1) {
    for (local_14 = local_c[0x17]; local_14 < local_c[0x19]; local_14 = local_14 + 1) {
      local_1c = (float)local_14 * DAT_02cc50e0;
      local_28 = local_1c + DAT_02cc50e0;
      local_18 = (float)local_10 * DAT_02cc50e0;
      local_24 = local_18 + DAT_02cc50e0;
      local_5 = FUN_0046acc0(local_14,local_10);
      local_20 = FUN_00591670(local_5);
      local_2c = local_c[local_20 + 0x3d];
      (**(code **)(*local_c + 0x24))(local_1c,local_18,&local_3c,&local_30);
      (**(code **)(*local_c + 0x24))(local_28,local_24,&local_34,&local_38);
      FUN_0068afb0(DAT_00917580,local_3c,local_38,local_34,local_30,local_2c,0);
    }
  }
  return;
}

