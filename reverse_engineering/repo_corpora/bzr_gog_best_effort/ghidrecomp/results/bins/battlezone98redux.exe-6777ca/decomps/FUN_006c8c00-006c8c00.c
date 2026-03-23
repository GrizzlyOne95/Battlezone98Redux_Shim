
int __thiscall FUN_006c8c00(undefined4 param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_006cd800(param_1);
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return 0;
    }
    if (*piVar1 == param_2) break;
    piVar1 = (int *)piVar1[2];
  }
  return piVar1[1];
}

