
void __thiscall FUN_00692fe0(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  FUN_00690630(*param_2,param_1);
  param_2[0x2d] = 0;
  FUN_00692e70(param_2);
  param_2[0x2e] = 0;
  for (iVar1 = 0; iVar1 < 0x20; iVar1 = iVar1 + 1) {
    param_2[iVar1 + 0x4f] = 0;
    param_2[iVar1 + 0x2f] = 0;
  }
  param_2[0x2f] = *(int *)(&DAT_02ce9aa4 + *param_2 * 0x1e0);
  param_2[0x90] = 0;
  param_2[0x163] = 0;
  param_2[0x164] = 0;
  param_2[0x165] = 0;
  FUN_006907f0(param_2);
  FUN_00690dc0(param_2);
  FUN_00690e80(param_2);
  FUN_00690830(*param_2);
  return;
}

