
undefined4 FUN_00834433(undefined4 param_1)

{
  int iVar1;
  
  FUN_0082d226(param_1,1);
  FUN_0082cac6(param_1,0);
  iVar1 = FUN_0082d2e8(param_1,1);
  if (iVar1 == 0) {
    return 1;
  }
  iVar1 = FUN_0082d490(param_1,1);
  if (iVar1 == 1) {
    FUN_0082c68b(param_1,0,0);
    FUN_0082cdd2(param_1,0xffffffff);
    FUN_0082cbf5(param_1,1);
    FUN_0082ced4(param_1,0xffffd8ed);
    goto LAB_008344de;
  }
  iVar1 = FUN_0082c882(param_1,1);
  if (iVar1 == 0) {
LAB_008344c6:
    FUN_0082b8e4(param_1,1,"boolean or proxy expected");
  }
  else {
    FUN_0082ce65(param_1,0xffffd8ed);
    iVar1 = FUN_0082d2e8(param_1,0xffffffff);
    FUN_0082d226(param_1,0xfffffffe);
    if (iVar1 == 0) goto LAB_008344c6;
  }
  FUN_0082c882(param_1,1);
LAB_008344de:
  FUN_0082d16f(param_1,2);
  return 1;
}

