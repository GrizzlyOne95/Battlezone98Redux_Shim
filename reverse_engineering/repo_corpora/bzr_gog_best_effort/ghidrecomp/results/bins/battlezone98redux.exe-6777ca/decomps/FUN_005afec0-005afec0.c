
void __fastcall FUN_005afec0(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x310) != 0) {
    FUN_004e2e20();
    uVar1 = FUN_00462380();
    *(undefined4 *)(param_1 + 0x30c) = uVar1;
  }
  if (*(int *)(param_1 + 0x228) != 0) {
    FUN_005af7b0();
    if (*(int *)(param_1 + 0x228) == 2) {
      if (*(int *)(param_1 + 0x310) != 0) {
        FUN_004e2d90();
      }
      FUN_00468a70(param_1,1);
      FUN_00444ef0(*(undefined4 *)(param_1 + 0xf0));
    }
    if (*(int *)(param_1 + 0x310) != 0) {
      FUN_004e2e20();
      uVar1 = FUN_00462380();
      *(undefined4 *)(param_1 + 0x30c) = uVar1;
    }
  }
  FUN_004a82e0();
  return;
}

