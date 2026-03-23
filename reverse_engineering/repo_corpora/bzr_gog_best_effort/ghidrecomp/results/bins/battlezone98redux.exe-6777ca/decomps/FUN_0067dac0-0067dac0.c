
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0067dac0(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_108 [64];
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  uint local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  int local_ac;
  int *local_a8;
  int *local_a4;
  int *local_a0;
  int *local_9c;
  undefined4 local_98 [16];
  undefined4 local_58 [10];
  double local_30;
  double local_28;
  double local_20;
  undefined4 local_18;
  undefined4 local_14;
  uint local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_ac = param_2;
  local_9c = *(int **)(param_2 + 0x94);
  local_a0 = *(int **)(param_2 + 0xe0);
  local_a4 = (int *)(**(code **)(*local_9c + 0x50))();
  uVar1 = (**(code **)(*local_a0 + 0xc0))();
  (**(code **)(*local_a4 + 0xe8))(&local_b8,uVar1);
  local_a8 = (int *)(**(code **)(*local_9c + 0x50))();
  uVar1 = (**(code **)(*local_a0 + 0xbc))();
  (**(code **)(*local_a8 + 0xf8))(&local_c8,uVar1);
  local_18 = local_c4;
  local_14 = local_c0;
  local_10 = local_bc ^ 0x80000000;
  local_c = local_c8;
  puVar2 = (undefined4 *)FUN_0081efe0(local_108,&local_18);
  puVar4 = local_98;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_98;
  puVar4 = local_58;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  local_30 = (double)local_b8 + (double)_DAT_025f8e4c;
  local_28 = (double)local_b4 + (double)_DAT_025f8e50;
  local_20 = -((double)local_b0 + (double)_DAT_025f8e54);
  puVar2 = local_58;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

