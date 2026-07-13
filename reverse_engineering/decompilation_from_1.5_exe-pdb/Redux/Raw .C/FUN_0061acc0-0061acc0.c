
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0061acc0(void)

{
  undefined4 *puVar1;
  float *pfVar2;
  uint *puVar3;
  undefined4 uVar4;
  int iVar5;
  uint *puVar6;
  undefined4 *puVar7;
  float10 fVar8;
  undefined8 uVar9;
  undefined1 local_168 [128];
  undefined1 local_e8 [16];
  undefined1 local_d8 [16];
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  int *local_b4;
  float local_b0;
  undefined8 local_ac;
  undefined4 local_a4 [10];
  undefined8 local_7c;
  double local_74;
  double local_6c;
  uint local_64 [4];
  undefined4 local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_b4 = (int *)FUN_00439e70();
  fVar8 = (float10)FUN_00822d60();
  local_bc = (float)fVar8;
  if (DAT_009198f2 == '\0') {
    if (DAT_009198f1 == '\0') {
      if (DAT_009198f0 != '\0') {
        fVar8 = (float10)FUN_00822d60();
        local_c0 = (float)fVar8;
        DAT_008eacd4 = DAT_008eacd4 - local_c0 * 0.5 * DAT_008eacd4;
        if (DAT_008eacd4 < 5.0) {
          DAT_008eacd4 = 5.0;
        }
      }
    }
    else {
      fVar8 = (float10)FUN_00822d60();
      local_c8 = (float)fVar8;
      DAT_008eacd4 = local_c8 * 0.5 * DAT_008eacd4 + DAT_008eacd4;
      if (50.0 < DAT_008eacd4) {
        DAT_008eacd4 = 50.0;
      }
    }
  }
  else {
    DAT_008eacd4 = 20.0;
  }
  fVar8 = (float10)FUN_004c1050();
  DAT_008eacd8 = (float)fVar8;
  puVar1 = &DAT_008fe1e0;
  puVar7 = local_a4;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar7 = puVar7 + 1;
  }
  local_b0 = DAT_008eacd8 + (float)local_b4[5];
  if (150.0 < local_b0) {
    local_b0 = 150.0;
  }
  local_6c = (double)-local_b0;
  puVar3 = &DAT_008fe1e0;
  puVar6 = local_64;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar6 = puVar6 + 1;
  }
  local_ac = FUN_008205a0();
  local_54 = (undefined4)((ulonglong)local_ac >> 0x20);
  local_50 = (uint)local_ac;
  local_48 = local_50 ^ 0x80000000;
  local_44 = local_54;
  puVar1 = (undefined4 *)FUN_0081fe60();
  puVar7 = local_a4;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar7 = puVar7 + 1;
  }
  puVar3 = &DAT_008fe1e0;
  puVar6 = local_64;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar6 = puVar6 + 1;
  }
  uVar9 = FUN_008205a0();
  local_64[0] = (uint)((ulonglong)uVar9 >> 0x20);
  local_64[2] = (uint)uVar9;
  local_4c = local_64[2] ^ 0x80000000;
  local_44 = local_64[0];
  local_ac = uVar9;
  puVar1 = (undefined4 *)FUN_0081fe60();
  puVar7 = local_a4;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar7 = puVar7 + 1;
  }
  pfVar2 = (float *)FUN_0061a4d0(local_e8,local_b4);
  local_18 = *pfVar2;
  local_14 = pfVar2[1];
  local_10 = pfVar2[2];
  local_c = pfVar2[3];
  local_b0 = local_c * _DAT_008eacf4 + local_18 * _DAT_008eace8 + local_14 * _DAT_008eacec +
             local_10 * _DAT_008eacf0;
  if (local_b0 < 0.0) {
    local_c = -local_c;
    local_18 = -local_18;
    local_14 = -local_14;
    local_10 = -local_10;
  }
  _DAT_008eace8 = local_18;
  _DAT_008eacec = local_14;
  _DAT_008eacf0 = local_10;
  _DAT_008eacf4 = local_c;
  puVar1 = (undefined4 *)FUN_0081f530(local_d8,&DAT_008eacf8,&DAT_008eace8,local_bc * 5.0);
  DAT_008eacf8 = *puVar1;
  DAT_008eacfc = puVar1[1];
  DAT_008ead00 = puVar1[2];
  DAT_008ead04 = puVar1[3];
  puVar3 = (uint *)FUN_0081efe0(local_168,&DAT_008eacf8);
  puVar6 = local_64;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar6 = puVar6 + 1;
  }
  FUN_00820180(&local_24,local_b4 + 2,1,*local_b4 + 0x20);
  FUN_004fef00(local_64,(double)local_24,(double)(local_20 + 5.0),(double)local_1c);
  puVar1 = (undefined4 *)FUN_0081fe60();
  puVar7 = local_a4;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar7 = puVar7 + 1;
  }
  fVar8 = (float10)FUN_007855e0(local_7c,local_6c);
  local_c4 = (float)fVar8;
  local_b8 = local_c4 + 1.0;
  if (local_74 < (double)local_b8) {
    local_74 = (double)local_b8;
  }
  uVar4 = FUN_00439e60();
  FUN_00689090(uVar4);
  FUN_0083e885();
  return;
}

