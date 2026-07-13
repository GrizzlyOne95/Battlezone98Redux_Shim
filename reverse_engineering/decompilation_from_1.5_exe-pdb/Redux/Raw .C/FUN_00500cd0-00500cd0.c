
undefined4 FUN_00500cd0(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  float10 fVar3;
  
  puVar1 = (undefined4 *)FUN_004ff7c0(param_1,1);
  puVar2 = (undefined4 *)FUN_004ff7c0(param_1,2);
  fVar3 = (float10)FUN_004976f0(*puVar1,puVar1[1],puVar1[2],*puVar2,puVar2[1],puVar2[2]);
  FUN_0082cd58(param_1,(double)fVar3);
  return 1;
}

