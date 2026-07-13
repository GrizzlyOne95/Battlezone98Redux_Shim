
undefined4 FUN_00502100(undefined4 param_1)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float10 fVar4;
  
  uVar2 = FUN_004ff750(param_1,1);
  uVar3 = FUN_004ff750(param_1,2,uVar2);
  fVar4 = (float10)FUN_0082ba89(param_1,3,uVar2,uVar3);
  uVar1 = FUN_005c96a0(uVar2,uVar3,(float)fVar4);
  FUN_0082cbf5(param_1,uVar1);
  return 1;
}

