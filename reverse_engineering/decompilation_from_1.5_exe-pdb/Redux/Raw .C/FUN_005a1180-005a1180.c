
void __fastcall FUN_005a1180(int *param_1)

{
  undefined4 *puVar1;
  undefined1 local_58 [24];
  int local_40;
  int *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_3c = param_1;
  FUN_0062de40(param_1[0x37],0x200);
  FUN_0043d580(local_3c[0x37]);
  FUN_00492640(local_3c[0x37],local_3c + 0x45,0);
  puVar1 = (undefined4 *)FUN_0081fd40(local_58,local_3c[0x36] + 8,local_3c[0x37] + 0x20);
  local_38 = *puVar1;
  local_34 = puVar1[1];
  local_30 = puVar1[2];
  local_2c = puVar1[3];
  local_28 = puVar1[4];
  local_24 = puVar1[5];
  local_20 = local_38;
  local_1c = local_34;
  local_18 = local_30;
  local_14 = local_2c;
  local_10 = local_28;
  local_c = local_24;
  for (local_40 = 0; local_40 < 10; local_40 = local_40 + 1) {
    FUN_004927d0(&local_38,local_3c + 0x45,0);
  }
  (**(code **)(*local_3c + 0x10))();
  FUN_0083e885();
  return;
}

