
undefined4 FUN_00507720(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_0082ba59(param_1,1,0);
  iVar2 = FUN_004ff820(param_1,2);
  if (iVar2 == 0) {
    iVar2 = FUN_004ff7a0(param_1,2);
    if (iVar2 == 0) {
      iVar2 = FUN_0082c9f5(param_1,2);
      if (iVar2 == 0) {
        uVar3 = FUN_004ff750(param_1,2);
        FUN_005ce2f0(uVar3,uVar1);
      }
      else {
        uVar3 = FUN_0082d377(param_1,2,0);
        FUN_005ce330(uVar3,uVar1);
      }
    }
    else {
      FUN_005ce280(iVar2,uVar1);
    }
  }
  else {
    FUN_005ce210(iVar2,uVar1);
  }
  return 0;
}

