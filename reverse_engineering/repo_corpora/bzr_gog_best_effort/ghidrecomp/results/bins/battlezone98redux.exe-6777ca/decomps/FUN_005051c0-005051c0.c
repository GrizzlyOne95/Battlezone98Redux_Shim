
undefined4 FUN_005051c0(undefined4 param_1)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  uVar2 = FUN_004ff750(param_1,1);
  uVar3 = FUN_0082ba1c(param_1,2,uVar2);
  uVar4 = FUN_0082ba1c(param_1,3,uVar2,uVar3);
  uVar5 = FUN_0082ba1c(param_1,4,uVar2,uVar3,uVar4);
  uVar6 = FUN_004ff750(param_1,5);
  uVar1 = FUN_005cd440(uVar2,uVar3,uVar4,uVar5,uVar6);
  FUN_0082cbf5(param_1,uVar1);
  return 1;
}

