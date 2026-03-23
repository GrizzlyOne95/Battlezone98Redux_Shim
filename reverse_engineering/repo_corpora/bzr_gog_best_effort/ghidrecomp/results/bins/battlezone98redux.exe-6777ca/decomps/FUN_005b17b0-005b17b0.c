
void FUN_005b17b0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_19c [64];
  undefined1 local_15c [64];
  int local_11c;
  undefined4 local_118;
  int local_114;
  int local_110;
  int local_10c;
  undefined4 local_108 [16];
  undefined4 local_c8 [16];
  undefined4 local_88 [16];
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_004c9ab0(param_1,param_2);
  local_114 = *(int *)(*(int *)(local_10c + 8) + 0x270);
  local_118 = *(undefined4 *)(*(int *)(local_10c + 8) + 0x274);
  puVar1 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = *param_1;
    param_1 = param_1 + 1;
    puVar1 = puVar1 + 1;
  }
  puVar1 = (undefined4 *)FUN_0081ebb0(local_15c,6.2831855 / (float)local_114);
  puVar3 = local_88;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = local_88;
  puVar3 = local_108;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  for (local_110 = 0; local_110 < local_114; local_110 = local_110 + 1) {
    local_11c = FUN_00586ff0(local_48,param_2);
    *(undefined4 *)(local_11c + 0x80) = 0;
    puVar1 = (undefined4 *)FUN_0081fe60(local_19c,local_108,local_48);
    puVar3 = local_c8;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_c8;
    puVar3 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  *(undefined4 *)(local_10c + 0x38) = *(undefined4 *)(*(int *)(local_10c + 8) + 0x278);
  *(float *)(local_10c + 0x3c) =
       (*(float *)(local_10c + 0x38) * *(float *)(*(int *)(local_10c + 8) + 0x38)) /
       (float)*(int *)(*(int *)(local_10c + 8) + 0x34);
  if (0.0 < *(float *)(*(int *)(local_10c + 8) + 0x278)) {
    FUN_004c0bb0(*(undefined4 *)(local_10c + 0x38));
  }
  FUN_0083e885();
  return;
}

