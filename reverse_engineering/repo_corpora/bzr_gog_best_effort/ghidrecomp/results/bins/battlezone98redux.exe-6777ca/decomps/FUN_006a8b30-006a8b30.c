
void __thiscall FUN_006a8b30(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = FUN_00694a90(param_3,param_4,param_1);
  *(int *)(param_2 + 0x34) = *(int *)(param_2 + 0x34) - iVar1;
  if (*(int *)(param_3 + 0x24) == param_2) {
    *(undefined4 *)(param_3 + 0x24) = 0;
  }
  FUN_0069d440(param_2 + 0xc,*(undefined4 *)(param_3 + 0x1c));
  return;
}

