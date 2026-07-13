
undefined4 FUN_00506ef0(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  
  fVar4 = (float10)FUN_0082d3e1(param_1,1);
  fVar5 = (float)fVar4;
  fVar4 = (float10)FUN_0082d3e1(param_1,2,fVar5);
  fVar6 = (float)fVar4;
  uVar1 = FUN_0082d338(param_1,3,fVar5,fVar6);
  uVar2 = FUN_0082d338(param_1,4,fVar5,fVar6,uVar1);
  uVar3 = FUN_0082d338(param_1,5);
  FUN_0049b430(fVar5,fVar6,uVar1,uVar2,uVar3);
  return 0;
}

