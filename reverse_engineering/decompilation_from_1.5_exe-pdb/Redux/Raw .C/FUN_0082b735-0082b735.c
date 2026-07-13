
undefined4 FUN_0082b735(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  char *pcVar2;
  int iVar3;
  
  piVar1 = _errno();
  pcVar2 = strerror(*piVar1);
  iVar3 = FUN_0082d377(param_1,param_3,0);
  FUN_0082cc9e(param_1,"cannot %s %s: %s",param_2,iVar3 + 1,pcVar2);
  FUN_0082cf99(param_1,param_3);
  return 6;
}

