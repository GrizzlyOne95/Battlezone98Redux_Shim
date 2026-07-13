
void __thiscall FUN_005cf230(int param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 local_80 [12];
  undefined1 local_74 [12];
  float local_68;
  int local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54 [6];
  float local_3c;
  float local_38;
  float local_34;
  double local_2c;
  double local_24;
  double local_1c;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = local_54;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = *param_2;
    param_2 = param_2 + 1;
    puVar1 = puVar1 + 1;
  }
  local_2c = (double)(local_3c * *(float *)(*(int *)(param_1 + 0xc) + 0x88)) + local_2c;
  local_24 = (double)(local_38 * *(float *)(*(int *)(param_1 + 0xc) + 0x88)) + local_24;
  local_1c = (double)(local_34 * *(float *)(*(int *)(param_1 + 0xc) + 0x88)) + local_1c;
  local_64 = param_1;
  FUN_00584fe0(local_54,param_3);
  puVar1 = (undefined4 *)FUN_004560b0(local_80,*(int *)(local_64 + 0x14) + 0x20);
  local_60 = *puVar1;
  local_5c = puVar1[1];
  local_58 = puVar1[2];
  puVar1 = (undefined4 *)
           FUN_004462d0(local_74,*(undefined4 *)(*(int *)(local_64 + 0xc) + 0x54),local_60,local_5c,
                        local_58);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  *(undefined4 *)(local_64 + 0x30) = local_14;
  *(undefined4 *)(local_64 + 0x34) = local_10;
  *(undefined4 *)(local_64 + 0x38) = local_c;
  *(undefined4 *)(local_64 + 0x20) = *(undefined4 *)(*(int *)(local_64 + 0xc) + 0x54);
  if (*(float *)(local_64 + 0x20) <= 0.0) {
    local_68 = 1e+30;
  }
  else {
    local_68 = 1.0 / *(float *)(local_64 + 0x20);
  }
  *(float *)(local_64 + 0x24) = local_68;
  *(undefined4 *)(local_64 + 0xe0) = 0;
  FUN_005cf100();
  FUN_0083e885();
  return;
}

