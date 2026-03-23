
void FUN_0043b380(int param_1)

{
  undefined4 *puVar1;
  undefined1 local_3c [12];
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (((*(int *)(param_1 + 0x58) != 0) && (*(int *)(param_1 + 0x3c) != 1)) &&
     ((*(uint *)(param_1 + 0x14) & 0x800) == 0)) {
    local_30 = FUN_00439e60();
    local_20 = (float)*(double *)(local_30 + 0x160);
    local_1c = (float)*(double *)(local_30 + 0x168);
    local_18 = (float)*(double *)(local_30 + 0x170);
    puVar1 = (undefined4 *)FUN_0062e120(local_3c,*(undefined4 *)(param_1 + 0x58));
    local_2c = *puVar1;
    local_28 = puVar1[1];
    local_24 = puVar1[2];
    local_14 = local_2c;
    local_10 = local_28;
    local_c = local_24;
    FUN_0043a0c0(local_20,local_1c,local_18,local_2c,local_28,local_24);
  }
  FUN_0083e885();
  return;
}

