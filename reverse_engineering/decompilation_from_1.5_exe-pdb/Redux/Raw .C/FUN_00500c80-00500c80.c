
undefined4 FUN_00500c80(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float10 fVar3;
  
  uVar1 = FUN_004ff7c0(param_1,1);
  uVar2 = FUN_004ff7c0(param_1,2,uVar1);
  fVar3 = (float10)FUN_00462010(uVar1,uVar2);
  FUN_0082cd58(param_1,(double)fVar3);
  return 1;
}

