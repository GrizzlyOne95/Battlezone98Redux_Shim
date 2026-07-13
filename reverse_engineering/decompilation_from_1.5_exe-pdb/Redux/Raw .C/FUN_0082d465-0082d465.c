
int FUN_0082d465(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_0082c4a6(param_1,param_2);
  if (piVar1[2] == 2) {
    return *piVar1;
  }
  if (piVar1[2] != 7) {
    return 0;
  }
  return *piVar1 + 0x18;
}

