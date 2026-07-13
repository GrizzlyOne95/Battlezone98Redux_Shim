
void FUN_0058e940(int param_1)

{
  int iVar1;
  
  while (*(int *)(param_1 + 0x30) != 0) {
    iVar1 = *(int *)(param_1 + 0x30);
    FUN_0058d7e0(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x28),
                 *(undefined4 *)(iVar1 + 0x24),*(undefined4 *)(iVar1 + 0x28));
    param_1 = iVar1;
  }
  return;
}

