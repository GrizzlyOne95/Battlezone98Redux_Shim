
void __thiscall FUN_004fab60(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x68) < 0x10) {
    iVar1 = *(int *)(param_1 + 0x28 + *(int *)(param_1 + 0x68) * 4);
    *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
    *(undefined4 *)(iVar1 + 0x1038) = param_2;
  }
  return;
}

