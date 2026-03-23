
void __fastcall FUN_00660910(int param_1)

{
  *(int *)(param_1 + 0x1b4) = *(int *)(param_1 + 0x1b4) + 1;
  if (*(int *)(param_1 + 0x1bc) <= *(int *)(param_1 + 0x1b4)) {
    *(undefined4 *)(param_1 + 0x1b4) = 0;
  }
  *(int *)(param_1 + 0x1a8) = param_1 + 0x28;
  return;
}

