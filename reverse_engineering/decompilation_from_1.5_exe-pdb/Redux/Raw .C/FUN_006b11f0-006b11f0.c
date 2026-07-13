
int * FUN_006b11f0(int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_006acb90(300000000);
  *param_1 = iVar1 / 1000000;
  param_1[1] = iVar1 % 1000000;
  return param_1;
}

