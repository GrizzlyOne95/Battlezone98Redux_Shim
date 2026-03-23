
void FUN_0083c626(undefined4 param_1,int *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_3 != -1) {
    iVar1 = *param_2;
    if (*param_2 == -1) {
      *param_2 = param_3;
    }
    else {
      do {
        iVar2 = iVar1;
        iVar1 = FUN_0083c3e8(param_1,iVar2);
      } while (iVar1 != -1);
      FUN_0083c362(param_1,iVar2,param_3);
    }
  }
  return;
}

