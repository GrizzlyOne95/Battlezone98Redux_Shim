
void __fastcall FUN_005d7830(int param_1)

{
  if (*(int *)(param_1 + 0x20) == 0x11) {
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xb0);
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xb4);
  }
  else {
    FUN_005fb1e0();
  }
  return;
}

