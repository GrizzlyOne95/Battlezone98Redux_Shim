
void FUN_005ca980(int param_1)

{
  for (; param_1 != 0; param_1 = *(int *)(param_1 + 0x7c)) {
    if (*(int *)(param_1 + 0x84) == 0xf) {
      *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) | 0x200;
    }
    if (*(int *)(param_1 + 0x80) != 0) {
      FUN_005ca980(*(undefined4 *)(param_1 + 0x80));
    }
  }
  return;
}

