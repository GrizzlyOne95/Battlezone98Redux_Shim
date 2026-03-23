
void FUN_00821d00(int param_1,int param_2,int *param_3,float *param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined4 local_94 [16];
  undefined4 local_54 [16];
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar3 = *param_3;
  fVar5 = (float10)FUN_007855e0((double)*(float *)(*(int *)(param_1 + 8) + param_2 * 8),
                                (double)*(float *)(*(int *)(param_1 + 8) + 4 + param_2 * 8));
  local_14 = *(float *)(*(int *)(param_1 + 8) + param_2 * 8) - *param_4;
  local_10 = ((float)fVar5 + (float)iVar3 * 0.01) - param_4[1];
  local_c = *(float *)(*(int *)(param_1 + 8) + 4 + param_2 * 8) - param_4[2];
  puVar1 = (undefined4 *)FUN_0081fa10();
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
  uVar2 = FUN_00439e60();
  FUN_00689090(uVar2);
  FUN_0083e885();
  return;
}

