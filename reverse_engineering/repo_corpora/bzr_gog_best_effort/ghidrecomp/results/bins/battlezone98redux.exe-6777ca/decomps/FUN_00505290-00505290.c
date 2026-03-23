
undefined4 FUN_00505290(undefined4 param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = FUN_0082c9f5(param_1,1);
  if (iVar2 == 0) {
    uVar3 = FUN_004ff750(param_1,1);
    uVar1 = FUN_005ce630(uVar3);
    FUN_0082cbf5(param_1,uVar1);
  }
  else {
    uVar3 = FUN_0082d377(param_1,1,0);
    uVar1 = FUN_005cd610(uVar3);
    FUN_0082cbf5(param_1,uVar1);
  }
  return 1;
}

