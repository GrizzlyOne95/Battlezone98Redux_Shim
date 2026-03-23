
void __fastcall FUN_005b62c0(int param_1)

{
  if (*(int *)(param_1 + 0x4c) != 8) {
    FUN_005b63e0();
    *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x4c);
    *(undefined4 *)(param_1 + 0x4c) = 8;
    FUN_005b6340();
    if (*(int *)(param_1 + 0x4c) != 8) {
      return;
    }
  }
  FUN_005b6470();
  return;
}

