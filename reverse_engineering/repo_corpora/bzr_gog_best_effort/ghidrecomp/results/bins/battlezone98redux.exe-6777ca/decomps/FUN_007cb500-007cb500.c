
void __fastcall FUN_007cb500(int param_1)

{
  if (0 < *(int *)(param_1 + 0x150)) {
    *(int *)(param_1 + 0x150) = *(int *)(param_1 + 0x150) + -1;
    FUN_007cb400();
  }
  return;
}

