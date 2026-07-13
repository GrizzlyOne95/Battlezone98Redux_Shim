
void FUN_005ce280(float *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar2 = &DAT_008fe1e0;
  puVar3 = local_48;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  local_20 = (double)*param_1;
  local_18 = (double)param_1[1];
  local_10 = (double)param_1[2];
  FUN_005ce210(local_48,param_2);
  FUN_0083e885();
  return;
}

