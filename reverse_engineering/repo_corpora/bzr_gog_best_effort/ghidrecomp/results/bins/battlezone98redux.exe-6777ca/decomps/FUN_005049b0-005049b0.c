
undefined4 FUN_005049b0(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar1 = FUN_004ff750(param_1,1);
  uVar2 = FUN_0082c1fd(param_1,3,1);
  iVar3 = FUN_004ff820(param_1,2);
  if (iVar3 == 0) {
    iVar3 = FUN_004ff7a0(param_1,2);
    if (iVar3 == 0) {
      uVar4 = FUN_0082ba59(param_1,2,0);
      FUN_005cc5f0(uVar1,uVar4,uVar2);
    }
    else {
      FUN_005cc3b0(uVar1,iVar3,uVar2);
    }
  }
  else {
    FUN_005cc470(uVar1,iVar3,uVar2);
  }
  return 0;
}

