
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004c6a10(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_1c0 [64];
  undefined1 local_180 [64];
  undefined1 local_140 [12];
  undefined8 local_134;
  undefined8 local_12c;
  float local_124;
  undefined8 local_120;
  int local_118;
  undefined4 local_114 [4];
  undefined4 local_104;
  undefined4 local_100;
  double local_ec;
  double local_e4;
  double local_dc;
  undefined4 local_d4 [16];
  undefined4 local_94 [16];
  uint local_54 [4];
  undefined4 local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar6 = (float10)FUN_00822d60();
  local_124 = (float)fVar6;
  *(float *)(local_118 + 0x60) =
       (float)_DAT_009198dc * 0.5 * local_124 + *(float *)(local_118 + 0x60);
  if (*(float *)(local_118 + 0x60) <= 0.5235988 && *(float *)(local_118 + 0x60) != 0.5235988) {
    *(undefined4 *)(local_118 + 0x60) = 0x3f060a92;
  }
  if (1.5707963 < *(float *)(local_118 + 0x60)) {
    *(undefined4 *)(local_118 + 0x60) = 0x3fc90fda;
  }
  *(float *)(local_118 + 100) = (float)_DAT_009198e4 * 0.5 * local_124 + *(float *)(local_118 + 100)
  ;
  if (*(float *)(local_118 + 100) <= 3.1415927) {
    if (*(float *)(local_118 + 100) <= -3.1415927 && *(float *)(local_118 + 100) != -3.1415927) {
      *(float *)(local_118 + 100) = *(float *)(local_118 + 100) + 6.2831855;
      *(float *)(local_118 + 0x6c) = *(float *)(local_118 + 0x6c) + 6.2831855;
    }
  }
  else {
    *(float *)(local_118 + 100) = *(float *)(local_118 + 100) - 6.2831855;
    *(float *)(local_118 + 0x6c) = *(float *)(local_118 + 0x6c) - 6.2831855;
  }
  fVar6 = (float10)FUN_004c1050(*(undefined4 *)(local_118 + 0x68),*(undefined4 *)(local_118 + 0x60),
                                local_124 * 5.0);
  *(float *)(local_118 + 0x68) = (float)fVar6;
  fVar6 = (float10)FUN_004c1050(*(undefined4 *)(local_118 + 0x6c),*(undefined4 *)(local_118 + 100),
                                local_124 * 5.0);
  *(float *)(local_118 + 0x6c) = (float)fVar6;
  puVar1 = &DAT_008fe1e0;
  puVar5 = local_114;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar5 = puVar5 + 1;
  }
  local_dc = -250.0;
  puVar3 = &DAT_008fe1e0;
  puVar4 = local_54;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  local_134 = FUN_008205a0(*(undefined4 *)(local_118 + 0x68));
  local_44 = (undefined4)((ulonglong)local_134 >> 0x20);
  local_40 = (uint)local_134;
  local_38 = local_40 ^ 0x80000000;
  local_34 = local_44;
  local_120 = local_134;
  puVar1 = (undefined4 *)FUN_0081fe60(local_180,local_114,local_54);
  puVar5 = local_d4;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar5 = puVar5 + 1;
  }
  puVar1 = local_d4;
  puVar5 = local_114;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar5 = puVar5 + 1;
  }
  puVar3 = &DAT_008fe1e0;
  puVar4 = local_54;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  local_12c = FUN_008205a0(*(undefined4 *)(local_118 + 0x6c));
  local_54[0] = (uint)((ulonglong)local_12c >> 0x20);
  local_54[2] = (uint)local_12c;
  local_3c = local_54[2] ^ 0x80000000;
  local_34 = local_54[0];
  local_120 = local_12c;
  puVar1 = (undefined4 *)FUN_0081fe60(local_1c0,local_114,local_54);
  puVar5 = local_94;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar5 = puVar5 + 1;
  }
  puVar1 = local_94;
  puVar5 = local_114;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar5 = puVar5 + 1;
  }
  local_ec = (double)*(float *)(local_118 + 0x48) + local_ec;
  local_e4 = (double)*(float *)(local_118 + 0x4c) + local_e4;
  local_dc = (double)*(float *)(local_118 + 0x50) + local_dc;
  puVar1 = (undefined4 *)FUN_00440000(local_140,local_114[3],local_104,local_100);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  *(undefined4 *)(local_118 + 0x54) = *puVar1;
  *(undefined4 *)(local_118 + 0x58) = local_10;
  *(undefined4 *)(local_118 + 0x5c) = local_c;
  puVar1 = local_114;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *puVar1;
    puVar1 = puVar1 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

