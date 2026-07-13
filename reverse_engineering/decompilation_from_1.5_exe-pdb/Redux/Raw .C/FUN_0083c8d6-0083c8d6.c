
void FUN_0083c8d6(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  FUN_0083c667(param_1,param_2);
  if (*param_2 == 2) {
LAB_0083c91a:
    iVar1 = -1;
  }
  else {
    if (3 < *param_2) {
      if (*param_2 < 6) goto LAB_0083c91a;
      if (*param_2 == 10) {
        FUN_0083c43c(param_1,param_2);
        iVar1 = param_2[2];
        goto LAB_0083c91d;
      }
    }
    iVar1 = FUN_0083c488(param_1,param_2,0);
  }
LAB_0083c91d:
  FUN_0083c626(param_1,param_2 + 5,iVar1);
  FUN_0083cadc(param_1,param_2[4]);
  param_2[4] = -1;
  return;
}

