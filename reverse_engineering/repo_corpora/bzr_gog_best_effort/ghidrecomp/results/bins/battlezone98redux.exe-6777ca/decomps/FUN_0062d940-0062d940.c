
void FUN_0062d940(undefined4 param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 uVar10;
  int local_34;
  int local_30;
  
  iVar3 = FUN_0062d660(param_1,param_2);
  uVar10 = 0xffffffff;
  local_34 = FUN_0062d690(param_1,0xffffffff);
  if (local_34 == 0) {
    local_34 = FUN_0062d6f0(param_1);
  }
  local_30 = FUN_0062d690(param_2,uVar10);
  if (local_30 == 0) {
    local_30 = FUN_0062d6f0(param_2);
  }
  *(undefined4 *)(&DAT_02b40948 + DAT_00920c90 * 0x34) = *(undefined4 *)(&DAT_02b3c730 + iVar3 * 4);
  *(int *)(&DAT_02b3c730 + iVar3 * 4) = DAT_00920c90;
  *(undefined4 *)(&DAT_02b40918 + DAT_00920c90 * 0x34) = param_1;
  *(undefined4 *)(&DAT_02b4091c + DAT_00920c90 * 0x34) = param_2;
  fVar1 = *(float *)(local_34 + 0xc);
  fVar2 = *(float *)(local_34 + 0x14);
  fVar8 = *(float *)(local_30 + 0xc);
  fVar9 = *(float *)(local_30 + 0x14);
  fVar5 = fVar1 - fVar8;
  fVar6 = *(float *)(local_34 + 0x10) - *(float *)(local_30 + 0x10);
  fVar7 = fVar2 - fVar9;
  *(float *)(&DAT_02b4093c + DAT_00920c90 * 0x34) = fVar5;
  *(float *)(&DAT_02b40940 + DAT_00920c90 * 0x34) = fVar6;
  *(float *)(&DAT_02b40944 + DAT_00920c90 * 0x34) = fVar7;
  *(float *)(&DAT_02b40930 + DAT_00920c90 * 0x34) = -fVar5;
  *(float *)(&DAT_02b40934 + DAT_00920c90 * 0x34) = -fVar6;
  *(float *)(&DAT_02b40938 + DAT_00920c90 * 0x34) = -fVar7;
  if ((fVar5 == 0.0) && (fVar7 == 0.0)) {
    *(undefined4 *)(&DAT_02b4092c + DAT_00920c90 * 0x34) = 0;
  }
  else {
    fVar4 = (float10)FUN_0046e0a0(fVar5,fVar7);
    *(float *)(&DAT_02b4092c + DAT_00920c90 * 0x34) = (float)fVar4;
  }
  fVar4 = (float10)FUN_00417910(fVar5 * fVar5 + fVar7 * fVar7);
  *(float *)(&DAT_02b40920 + DAT_00920c90 * 0x34) = (float)fVar4;
  fVar4 = (float10)FUN_00417910(fVar5 * fVar5 + fVar6 * fVar6 + fVar7 * fVar7);
  *(float *)(&DAT_02b40924 + DAT_00920c90 * 0x34) = (float)fVar4;
  fVar8 = fVar8 - fVar1;
  fVar9 = fVar9 - fVar2;
  if ((fVar8 == 0.0) && (fVar9 == 0.0)) {
    *(undefined4 *)(&DAT_02b40928 + DAT_00920c90 * 0x34) = 0;
  }
  else {
    fVar4 = (float10)FUN_0046e0a0(fVar8,fVar9);
    *(float *)(&DAT_02b40928 + DAT_00920c90 * 0x34) = (float)fVar4;
  }
  iVar3 = DAT_00920c90 * 0x34;
  DAT_00920c90 = DAT_00920c90 + 1;
  FUN_0083e885(uVar10,&DAT_02b40918 + iVar3);
  return;
}

