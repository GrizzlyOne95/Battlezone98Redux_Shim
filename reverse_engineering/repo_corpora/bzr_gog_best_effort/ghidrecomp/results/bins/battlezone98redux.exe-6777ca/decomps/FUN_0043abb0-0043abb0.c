
int __thiscall FUN_0043abb0(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_0043bc50(param_1);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (*(int *)(iVar1 + 0x4c) == param_2) break;
    iVar1 = FUN_00439cc0(iVar1);
  }
  return iVar1;
}

