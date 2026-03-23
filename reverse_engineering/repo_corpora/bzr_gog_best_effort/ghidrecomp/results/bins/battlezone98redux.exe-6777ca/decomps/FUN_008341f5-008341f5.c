
undefined4 FUN_008341f5(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_0082bb89(param_1,2,"too many nested functions");
  FUN_0082cdd2(param_1,1);
  FUN_0082c585(param_1,0,1);
  iVar1 = FUN_0082d490(param_1,0xffffffff);
  if (iVar1 == 0) {
    *param_3 = 0;
  }
  else {
    iVar1 = FUN_0082c9f5(param_1,0xffffffff);
    if (iVar1 != 0) {
      FUN_0082cfd8(param_1,3);
      uVar2 = FUN_0082d377(param_1,3,param_3);
      return uVar2;
    }
    FUN_0082bc39(param_1,"reader function must return a string");
  }
  return 0;
}

