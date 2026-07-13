
undefined4 FUN_0083472f(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  FUN_0082bbb2(param_1,1,5);
  iVar1 = FUN_0082cb3b(param_1,1);
  iVar1 = iVar1 + 1;
  iVar2 = FUN_0082c8f6(param_1);
  if (iVar2 != 2) {
    if (iVar2 != 3) {
      uVar3 = FUN_0082bc39(param_1,"wrong number of arguments to \'insert\'");
      return uVar3;
    }
    iVar4 = FUN_0082ba1c(param_1,2);
    iVar2 = iVar1;
    if (iVar1 < iVar4) {
      iVar2 = iVar4;
    }
    while (iVar1 = iVar4, iVar4 < iVar2) {
      FUN_0082ce9d(param_1,1,iVar2 + -1);
      FUN_0082cf37(param_1,1,iVar2);
      iVar2 = iVar2 + -1;
    }
  }
  FUN_0082cf37(param_1,1,iVar1);
  return 0;
}

