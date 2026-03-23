
int FUN_007fac60(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 uVar5;
  
  uVar3 = param_2;
  uVar5 = param_3;
  uVar1 = FUN_007f7af0(param_1,param_2,param_3);
  piVar2 = (int *)FUN_007f7df0(uVar1,uVar3,uVar5);
  uVar3 = FUN_007f7b10(param_1,param_2,param_3);
  piVar4 = (int *)FUN_007f7e40(uVar3,param_2,param_3);
  return *piVar2 * *piVar4;
}

