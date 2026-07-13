
void __thiscall FUN_004a79a0(int param_1,int param_2)

{
  for (; param_2 != 0; param_2 = *(int *)(param_2 + 0x7c)) {
    if (*(int *)(param_2 + 0x84) == 0x4c) {
      *(int *)(param_1 + 0x25c + *(int *)(param_1 + 0x27c) * 4) = param_2;
      *(int *)(param_1 + 0x27c) = *(int *)(param_1 + 0x27c) + 1;
    }
    if (*(int *)(param_2 + 0x80) != 0) {
      FUN_004a79a0(*(undefined4 *)(param_2 + 0x80));
    }
  }
  return;
}

