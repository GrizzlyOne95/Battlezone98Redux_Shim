
int FUN_00834002(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00834188(param_1,param_2);
  iVar2 = FUN_0082c5be(param_2,param_3);
  if (iVar2 == 0) {
    FUN_0082bc39(param_1,"too many arguments to resume");
  }
  if (iVar1 == 1) {
    FUN_0082d4cc(param_1,param_2,param_3);
    FUN_0082d15c(param_1,param_2);
    iVar1 = FUN_0082f6a3(param_2,param_3);
    if ((iVar1 == 0) || (iVar1 == 1)) {
      iVar1 = FUN_0082c8f6(param_2);
      iVar2 = FUN_0082c5be(param_1,iVar1 + 1);
      if (iVar2 == 0) {
        FUN_0082bc39(param_1,"too many results to resume");
      }
      FUN_0082d4cc(param_2,param_1,iVar1);
      return iVar1;
    }
    FUN_0082d4cc(param_2,param_1,1);
  }
  else {
    FUN_0082cc9e(param_1,"cannot resume %s coroutine",(&PTR_s_running_0086f230)[iVar1]);
  }
  return -1;
}

