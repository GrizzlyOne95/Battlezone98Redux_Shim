
void __fastcall FUN_005b1e10(int param_1)

{
  undefined4 *puVar1;
  float *pfVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_1ac [64];
  undefined1 local_16c [64];
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  int local_11c;
  int local_118;
  undefined4 local_114 [16];
  undefined4 local_d4 [16];
  undefined4 local_94 [16];
  undefined4 local_54 [16];
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_118 = param_1;
  puVar1 = (undefined4 *)FUN_0081fe60(local_16c,*(int *)(param_1 + 0x10) + 0x20,param_1 + 0x28);
  puVar4 = local_54;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar1 = local_54;
  puVar4 = local_94;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar1 = (undefined4 *)FUN_008203f0(local_1ac,local_94);
  puVar4 = local_114;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar1 = local_114;
  puVar4 = local_d4;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar4 = puVar4 + 1;
  }
  local_128 = *(float *)(*(int *)(local_118 + 8) + 0x80);
  local_11c = FUN_00462610();
  if (local_11c != 0) {
    pfVar2 = (float *)(**(code **)(*(int *)(local_11c + 0x18) + 0xc))();
    local_14 = *pfVar2;
    local_10 = pfVar2[1];
    local_c = pfVar2[2];
    FUN_00820180(&local_14,&local_14,1,local_d4);
    if ((0.0 <= local_c) && (local_c <= local_128)) {
      iVar3 = FUN_00462400();
      local_120 = *(float *)(iVar3 + 0xc) * 0.75;
      local_120 = local_120 * local_120;
      local_124 = local_14 * local_14 + local_10 * local_10;
      local_12c = local_c * local_c + local_124;
    }
  }
  FUN_0083e885();
  return;
}

