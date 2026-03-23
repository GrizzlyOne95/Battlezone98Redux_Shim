
void __fastcall FUN_00697580(int param_1)

{
  if (*(int *)(*(int *)(param_1 + 0x3c) + 0x60) == 0) {
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x48);
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 0x4c);
  }
  else {
    *(undefined4 *)(param_1 + 0x10) =
         *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x34);
    *(undefined4 *)(param_1 + 0xc) =
         *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x38);
  }
  return;
}

