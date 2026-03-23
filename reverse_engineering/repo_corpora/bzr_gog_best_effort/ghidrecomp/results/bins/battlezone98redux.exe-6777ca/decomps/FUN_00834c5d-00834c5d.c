
undefined4 FUN_00834c5d(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0082d490(param_1,2);
  if (iVar1 == 0) {
    uVar2 = FUN_0082ca18(param_1,param_2,param_3);
  }
  else {
    FUN_0082cdd2(param_1,2);
    FUN_0082cdd2(param_1,param_2 + -1);
    FUN_0082cdd2(param_1,param_3 + -2);
    FUN_0082c585(param_1,2,1);
    uVar2 = FUN_0082d2e8(param_1,0xffffffff);
    FUN_0082d226(param_1,0xfffffffe);
  }
  return uVar2;
}

