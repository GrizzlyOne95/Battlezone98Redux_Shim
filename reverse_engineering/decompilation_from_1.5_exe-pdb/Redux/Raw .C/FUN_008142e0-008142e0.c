
void FUN_008142e0(int *param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_1;
  *param_2 = iVar1;
  param_2[1] = iVar1 >> 0x1f;
  return;
}

