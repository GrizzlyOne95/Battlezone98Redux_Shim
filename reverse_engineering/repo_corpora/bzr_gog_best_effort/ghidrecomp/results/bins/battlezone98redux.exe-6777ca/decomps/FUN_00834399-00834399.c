
int FUN_00834399(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = FUN_0082d447(param_1,0xffffd8ed);
  uVar2 = FUN_0082c8f6(param_1);
  iVar3 = FUN_00834002(param_1,uVar1,uVar2);
  if (iVar3 < 0) {
    iVar4 = FUN_0082c9f5(param_1,0xffffffff);
    if (iVar4 != 0) {
      FUN_0082c341(param_1,1);
      FUN_0082c953(param_1,0xfffffffe);
      FUN_0082c61c(param_1,2);
    }
    FUN_0082c6fb(param_1);
  }
  return iVar3;
}

