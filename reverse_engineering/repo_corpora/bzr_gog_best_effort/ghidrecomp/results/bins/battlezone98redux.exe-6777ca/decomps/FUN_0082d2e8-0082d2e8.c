
undefined4 FUN_0082d2e8(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  undefined4 uVar2;
  
  piVar1 = (int *)FUN_0082c4a6(param_1,param_2);
  if ((piVar1[2] == 0) || ((uVar2 = 1, piVar1[2] == 1 && (*piVar1 == 0)))) {
    uVar2 = 0;
  }
  return uVar2;
}

