
void FUN_0083c87c(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  FUN_0083c667(param_1,param_2);
  iVar1 = *param_2;
  if ((iVar1 == 1) || (iVar1 == 3)) {
    iVar1 = -1;
  }
  else if (iVar1 == 10) {
    iVar1 = param_2[2];
  }
  else {
    iVar1 = FUN_0083c488(param_1,param_2,1);
  }
  FUN_0083c626(param_1,param_2 + 4,iVar1);
  FUN_0083cadc(param_1,param_2[5]);
  param_2[5] = -1;
  return;
}

