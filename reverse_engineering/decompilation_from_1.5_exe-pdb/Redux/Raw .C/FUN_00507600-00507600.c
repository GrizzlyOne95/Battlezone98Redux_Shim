
undefined4 FUN_00507600(undefined4 param_1)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float10 fVar4;
  
  uVar2 = FUN_004ff750(param_1,1);
  uVar3 = FUN_004ff750(param_1,2,uVar2);
  fVar4 = (float10)FUN_0082c276(param_1,3,0x3ff4ccccc0000000,uVar2,uVar3);
  uVar1 = FUN_005cdfb0(uVar2,uVar3,(float)fVar4);
  FUN_0082cbf5(param_1,uVar1);
  return 1;
}

