
void __thiscall FUN_005aba30(int param_1,int param_2)

{
  for (; param_2 != 0; param_2 = *(int *)(param_2 + 0x7c)) {
    if (*(int *)(param_2 + 0x84) == 0x46) {
      *(int *)(param_1 + 0x324 + *(int *)(param_1 + 0x344) * 4) = param_2;
      *(int *)(param_1 + 0x344) = *(int *)(param_1 + 0x344) + 1;
    }
    if (*(int *)(param_2 + 0x80) != 0) {
      FUN_005aba30(*(undefined4 *)(param_2 + 0x80));
    }
  }
  return;
}

