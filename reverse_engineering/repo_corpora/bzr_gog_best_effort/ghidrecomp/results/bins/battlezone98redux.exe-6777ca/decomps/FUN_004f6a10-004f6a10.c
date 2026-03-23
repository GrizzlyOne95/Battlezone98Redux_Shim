
void __thiscall FUN_004f6a10(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)(param_1 + 0x18) = 0x3f800000;
  *(int *)(param_1 + 0x1c) = param_2;
  *(undefined4 *)(param_1 + 0x20) = param_3;
  *(undefined4 *)(param_1 + 0x24) = param_4;
  *(undefined1 *)(param_1 + 0x28) = 1;
  *(undefined1 *)(param_1 + 0x29) = 1;
  *(bool *)(param_1 + 0x2b) = 0xe0f < param_2;
  return;
}

