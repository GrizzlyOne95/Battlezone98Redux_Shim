
undefined4 FUN_00504860(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar1 = FUN_004ff750(param_1,1);
  uVar2 = FUN_0082c1fd(param_1,3,1);
  iVar3 = FUN_0082c9f5(param_1,2);
  if (iVar3 == 0) {
    uVar4 = FUN_004ff750(param_1,2);
    FUN_005cc140(uVar1,uVar4,uVar2);
  }
  else {
    uVar4 = FUN_0082d377(param_1,2,0);
    FUN_005cc100(uVar1,uVar4,uVar2);
  }
  return 0;
}

