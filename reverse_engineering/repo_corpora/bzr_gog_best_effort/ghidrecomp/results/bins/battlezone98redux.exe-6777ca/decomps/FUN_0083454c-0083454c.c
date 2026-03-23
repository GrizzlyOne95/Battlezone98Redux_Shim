
undefined4 FUN_0083454c(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  FUN_0082bbb2(param_1,1,5);
  iVar1 = FUN_0082cb3b(param_1,1);
  FUN_0082bbb2(param_1,2,6);
  iVar3 = 1;
  if (0 < iVar1) {
    do {
      FUN_0082cdd2(param_1,2);
      FUN_0082ccca(param_1,iVar3);
      FUN_0082ce9d(param_1,1,iVar3);
      FUN_0082c585(param_1,2,1);
      iVar2 = FUN_0082d490(param_1,0xffffffff);
      if (iVar2 != 0) {
        return 1;
      }
      FUN_0082d226(param_1,0xfffffffe);
      iVar3 = iVar3 + 1;
    } while (iVar3 <= iVar1);
  }
  return 0;
}

