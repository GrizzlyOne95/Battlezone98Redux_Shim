
void FUN_0082c0d6(undefined4 param_1,int param_2,int *param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 != 0) {
    iVar3 = 0;
    iVar2 = *param_3;
    piVar1 = param_3;
    while (iVar2 != 0) {
      piVar1 = piVar1 + 2;
      iVar3 = iVar3 + 1;
      iVar2 = *piVar1;
    }
    FUN_0082bc6c(param_1,0xffffd8f0,"_LOADED",1);
    FUN_0082c82c(param_1,0xffffffff,param_2);
    iVar2 = FUN_0082d490(param_1,0xffffffff);
    if (iVar2 != 5) {
      FUN_0082d226(param_1,0xfffffffe);
      iVar2 = FUN_0082bc6c(param_1,0xffffd8ee,param_2,iVar3);
      if (iVar2 != 0) {
        FUN_0082bc39(param_1,"name conflict for module \'%s\'",param_2);
      }
      FUN_0082cdd2(param_1,0xffffffff);
      FUN_0082d102(param_1,0xfffffffd,param_2);
    }
    FUN_0082cf99(param_1,0xfffffffe);
    FUN_0082c953(param_1,-1 - param_4);
  }
  if (*param_3 != 0) {
    do {
      if (0 < param_4) {
        param_2 = param_4;
        do {
          FUN_0082cdd2(param_1,-param_4);
          param_2 = param_2 + -1;
        } while (param_2 != 0);
      }
      FUN_0082cc15(param_1,param_3[1],param_4);
      FUN_0082d102(param_1,-2 - param_4,*param_3);
      param_3 = param_3 + 2;
    } while (*param_3 != 0);
  }
  FUN_0082d226(param_1,-1 - param_4);
  return;
}

