
void __thiscall FUN_004c7250(int param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  DAT_02cc40b8 = 1;
  *(undefined2 *)(param_1 + 0x4160 + *(int *)(param_1 + 0x4150) * 6) = param_2;
  *(undefined2 *)(param_1 + 0x4162 + *(int *)(param_1 + 0x4150) * 6) = param_3;
  *(undefined2 *)(param_1 + 0x4164 + *(int *)(param_1 + 0x4150) * 6) = param_4;
  *(int *)(param_1 + 0x4148) = *(int *)(param_1 + 0x4148) + 1;
  *(uint *)(param_1 + 0x4150) = *(int *)(param_1 + 0x4150) + 1U & 0x7f;
  if (0x7f < *(int *)(param_1 + 0x4148)) {
    *(undefined4 *)(param_1 + 0x4148) = 0x7f;
    *(uint *)(param_1 + 0x414c) = *(int *)(param_1 + 0x4150) + 1U & 0x7f;
  }
  return;
}

