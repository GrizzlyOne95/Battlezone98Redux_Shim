
void FUN_00694ba0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(DAT_00920f04 + *(char *)(param_1 + 0x10) * 4);
  FUN_0069d330(iVar1 + 8,param_1);
  *(int *)(iVar1 + 0x48) = *(int *)(iVar1 + 0x48) + 1;
  *(int *)(iVar1 + 0x4c) = *(int *)(iVar1 + 0x4c) + 1;
  *(int *)(iVar1 + 0x50) = *(int *)(iVar1 + 0x50) + 1;
  *(int *)(iVar1 + 0x54) = *(int *)(iVar1 + 0x4c) + *(int *)(iVar1 + 0x50);
  return;
}

