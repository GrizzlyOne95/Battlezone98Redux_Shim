
void __fastcall FUN_004e2d90(int param_1)

{
  if ((*(int *)(*(int *)(param_1 + 0xf8) + 0x160) != 0) && (*(char *)(param_1 + 0x238) != '\0')) {
    FUN_0044dc60(0,0);
  }
  *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) = *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) | 0x401;
  *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0xd0) = 0x3f800000;
  *(undefined1 *)(param_1 + 0x238) = 0;
  return;
}

