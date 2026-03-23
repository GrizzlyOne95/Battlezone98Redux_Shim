
undefined * __thiscall FUN_0062c890(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0062e050(param_2,param_1);
  iVar2 = 0;
  while( true ) {
    if (0x13ff < iVar2) {
      return (undefined *)0x0;
    }
    if (*(int *)(&DAT_02a1f570 + iVar2 * 0xe4) == iVar1) break;
    iVar2 = iVar2 + 1;
  }
  return &DAT_02a1f570 + iVar2 * 0xe4;
}

