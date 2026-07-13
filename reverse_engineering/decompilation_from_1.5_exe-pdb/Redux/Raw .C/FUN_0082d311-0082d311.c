
undefined4 FUN_0082d311(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_0082c4a6(param_1,param_2);
  if ((piVar1[2] == 6) && (*(char *)(*piVar1 + 6) != '\0')) {
    return *(undefined4 *)(*piVar1 + 0x10);
  }
  return 0;
}

