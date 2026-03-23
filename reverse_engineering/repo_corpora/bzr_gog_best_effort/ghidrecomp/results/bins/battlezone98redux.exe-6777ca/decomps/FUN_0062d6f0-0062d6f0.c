
void FUN_0062d6f0(int param_1)

{
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_3c [16];
  undefined1 local_2c [12];
  undefined4 local_20;
  undefined *local_1c;
  int local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = FUN_0062d630(param_1,0);
  local_20 = 0xffffffff;
  *(undefined4 *)(&DAT_02b3f034 + DAT_00920c88 * 0x20) =
       *(undefined4 *)(&DAT_02b3ee50 + local_18 * 4);
  *(int *)(&DAT_02b3ee50 + local_18 * 4) = DAT_00920c88;
  *(int *)(&DAT_02b3f018 + DAT_00920c88 * 0x20) = param_1;
  pfVar1 = (float *)FUN_004560b0(local_2c,param_1 + 0x20);
  local_14 = *pfVar1;
  local_10 = pfVar1[1];
  local_c = pfVar1[2];
  if ((local_14 == 0.0) && (local_c == 0.0)) {
    *(undefined4 *)(&DAT_02b3f020 + DAT_00920c88 * 0x20) = 0;
    *(undefined4 *)(&DAT_02b3f01c + DAT_00920c88 * 0x20) = 0;
  }
  else {
    fVar4 = (float10)FUN_0046e0a0(local_14,local_c);
    *(float *)(&DAT_02b3f01c + DAT_00920c88 * 0x20) = (float)fVar4;
    fVar4 = (float10)FUN_0046e0a0(local_14,local_c);
    *(float *)(&DAT_02b3f020 + DAT_00920c88 * 0x20) = (float)fVar4;
  }
  puVar2 = (undefined4 *)FUN_0062c960(local_3c,param_1);
  iVar3 = DAT_00920c88 * 0x20;
  *(undefined4 *)(&DAT_02b3f024 + iVar3) = *puVar2;
  *(undefined4 *)(&DAT_02b3f028 + iVar3) = puVar2[1];
  *(undefined4 *)(&DAT_02b3f02c + iVar3) = puVar2[2];
  *(undefined4 *)(&DAT_02b3f030 + iVar3) = puVar2[3];
  local_1c = &DAT_02b3f018 + DAT_00920c88 * 0x20;
  DAT_00920c88 = DAT_00920c88 + 1;
  FUN_0083e885();
  return;
}

