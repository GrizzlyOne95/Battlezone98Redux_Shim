
undefined4 FUN_00503520(undefined4 param_1)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar2 = FUN_004ff750(param_1,1);
  uVar3 = FUN_0082c225(param_1,2,0,0,uVar2);
  iVar4 = FUN_0082c1fd(param_1,3,0xffffffff,uVar2,uVar3);
  if (iVar4 < 0) {
    uVar1 = FUN_005cb050(uVar2,uVar3);
    FUN_0082cbf5(param_1,uVar1);
  }
  else {
    uVar1 = FUN_005cb0d0(uVar2,uVar3,iVar4);
    FUN_0082cbf5(param_1,uVar1);
  }
  return 1;
}

