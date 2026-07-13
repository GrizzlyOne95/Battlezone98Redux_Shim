
undefined4 FUN_00504ad0(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  
  uVar1 = FUN_004ff750(param_1,1);
  uVar2 = FUN_0082ba59(param_1,2,0);
  uVar3 = FUN_0082c1fd(param_1,4,1);
  iVar4 = FUN_004ff820(param_1,3);
  if (iVar4 == 0) {
    iVar4 = FUN_004ff7a0(param_1,3);
    if (iVar4 == 0) {
      iVar4 = FUN_0082c9f5(param_1,3);
      if (iVar4 == 0) {
        uVar5 = FUN_004ff750(param_1,3);
        FUN_005ccb30(uVar1,uVar2,uVar5,uVar3);
      }
      else {
        uVar5 = FUN_0082d377(param_1,3,0);
        FUN_005cc9a0(uVar1,uVar2,uVar5,uVar3);
      }
    }
    else {
      FUN_005cc6e0(uVar1,uVar2,iVar4,uVar3);
    }
  }
  else {
    FUN_005cc800(uVar1,uVar2,iVar4,uVar3);
  }
  return 0;
}

