
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0067d8f0(double *param_1,int param_2,int *param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_120 [64];
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  uint local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  int local_c4;
  int *local_c0;
  int *local_bc;
  int *local_b8;
  int *local_b4;
  undefined4 local_b0 [16];
  undefined4 local_70 [16];
  undefined4 local_30;
  undefined4 local_2c;
  uint local_28;
  undefined4 local_24;
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_b8 = param_3;
  local_c4 = param_2;
  local_b4 = *(int **)(param_2 + 0x94);
  local_c0 = (int *)(**(code **)(*local_b4 + 0x50))();
  uVar1 = (**(code **)(*local_b8 + 0xc0))();
  (**(code **)(*local_c0 + 0xe8))(&local_d0,uVar1);
  local_bc = (int *)(**(code **)(*local_b4 + 0x50))();
  uVar1 = (**(code **)(*local_b8 + 0xbc))();
  (**(code **)(*local_bc + 0xf8))(&local_e0,uVar1);
  local_30 = local_dc;
  local_2c = local_d8;
  local_28 = local_d4 ^ 0x80000000;
  local_24 = local_e0;
  puVar2 = (undefined4 *)FUN_0081efe0(local_120,&local_30);
  puVar4 = local_70;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_70;
  puVar4 = local_b0;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  local_20 = (double)local_d0 + (double)_DAT_025f8e4c;
  local_18 = (double)local_cc + (double)_DAT_025f8e50;
  local_10 = -((double)local_c8 + (double)_DAT_025f8e54);
  *param_1 = local_20;
  param_1[1] = local_18;
  param_1[2] = local_10;
  FUN_0083e885();
  return;
}

