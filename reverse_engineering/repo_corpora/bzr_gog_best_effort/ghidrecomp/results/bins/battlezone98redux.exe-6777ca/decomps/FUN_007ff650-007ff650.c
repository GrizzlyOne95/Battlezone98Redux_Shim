
void FUN_007ff650(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    if (*(int *)(param_1 + 4) != 0) {
      FUN_007ff6c0(*(undefined4 *)(param_1 + 4));
    }
    FUN_007ff650(*(undefined4 *)(param_1 + 8),param_2);
    FUN_007ff650(*(undefined4 *)(param_1 + 0xc),param_2);
    FUN_007ff650(*(undefined4 *)(param_1 + 0x10),param_2);
    FUN_007ff6c0(param_1);
  }
  return;
}

