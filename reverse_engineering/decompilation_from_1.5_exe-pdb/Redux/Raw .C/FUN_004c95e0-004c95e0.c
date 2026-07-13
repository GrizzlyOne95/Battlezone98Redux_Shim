
void __fastcall FUN_004c95e0(int param_1)

{
  *(int *)(param_1 + 0x1230) = *(int *)(param_1 + 0x1230) + 1;
  if (*(int *)(param_1 + 0x1238) <= *(int *)(param_1 + 0x1230)) {
    *(undefined4 *)(param_1 + 0x1230) = 0;
  }
  *(int *)(param_1 + 0x1228) = param_1 + 0x28;
  return;
}

