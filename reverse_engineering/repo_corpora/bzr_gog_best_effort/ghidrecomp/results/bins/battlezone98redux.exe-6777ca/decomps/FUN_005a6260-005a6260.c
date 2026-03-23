
void __thiscall FUN_005a6260(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 local_48 [12];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_30 = param_1;
  if (0 < *(int *)(*(int *)(param_1 + 8) + 0x30)) {
    FUN_00820180(&local_2c,*(int *)(param_1 + 0xc) + 0xa0,1,*(int *)(param_1 + 0xc) + 0x20);
    puVar1 = (undefined4 *)
             FUN_006897e0(local_48,param_2,(double)local_2c,(double)local_28,(double)local_24);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    local_38 = *(undefined4 *)(*(int *)(local_30 + 0xc) + 0xac);
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    FUN_0049bf10();
    local_3c = FUN_0083f040();
    local_34 = DAT_00920ef4;
    DAT_00920ef4 = local_18;
    FUN_0068e600();
    DAT_00920ef4 = local_34;
  }
  FUN_0083e885();
  return;
}

