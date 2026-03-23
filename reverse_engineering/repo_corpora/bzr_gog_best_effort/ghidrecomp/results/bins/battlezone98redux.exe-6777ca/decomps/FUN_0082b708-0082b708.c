
bool FUN_0082b708(int *param_1)

{
  int iVar1;
  
  iVar1 = (*param_1 - (int)param_1) + -0xc;
  if (iVar1 != 0) {
    FUN_0082cd08(param_1[2],param_1 + 3,iVar1);
    *param_1 = (int)(param_1 + 3);
    param_1[1] = param_1[1] + 1;
  }
  return iVar1 != 0;
}

