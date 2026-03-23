
undefined4 FUN_00502de0(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float10 fVar4;
  float fVar5;
  
  uVar1 = FUN_004ff750(param_1,1);
  fVar4 = (float10)FUN_0082ba89(param_1,2,uVar1);
  fVar5 = (float)fVar4;
  uVar2 = FUN_0082c1fd(param_1,3,0xffffffff,uVar1,fVar5);
  uVar3 = FUN_0082c225(param_1,4,0,0,uVar1,fVar5,uVar2);
  uVar1 = FUN_005ca520(uVar1,fVar5,uVar2,uVar3);
  FUN_0082ccca(param_1,uVar1);
  return 1;
}

