
int __thiscall FUN_00827390(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_00827330(param_2,param_3,param_1);
  if (iVar1 == 0) {
    iVar1 = -1;
  }
  else if ((*(uint *)(iVar1 + 0x20) & 6) == 0) {
    iVar1 = *(int *)(iVar1 + 0x18);
  }
  else {
    iVar1 = *(int *)(iVar1 + 0x20) >> 8;
  }
  return iVar1;
}

