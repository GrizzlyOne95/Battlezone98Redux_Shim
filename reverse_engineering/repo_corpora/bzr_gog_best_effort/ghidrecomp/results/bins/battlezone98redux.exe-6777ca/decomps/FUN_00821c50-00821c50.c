
void FUN_00821c50(int param_1,float *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_d4 [64];
  undefined4 local_94 [16];
  undefined4 local_54 [16];
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (float)*(double *)(param_1 + 0x48) - *param_2;
  local_10 = (float)*(double *)(param_1 + 0x50) - param_2[1];
  local_c = (float)*(double *)(param_1 + 0x58) - param_2[2];
  puVar1 = (undefined4 *)FUN_0081fa10(local_d4,param_2,&local_14);
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
  uVar2 = FUN_00439e60(local_94);
  FUN_00689090(uVar2);
  FUN_0083e885();
  return;
}

