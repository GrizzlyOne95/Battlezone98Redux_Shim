
void __fastcall FUN_005c3fd0(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0069d250();
  *(undefined4 *)(param_1 + 0x54) = uVar1;
  uVar1 = FUN_006a61b0(param_1,*(undefined4 *)(param_1 + 0x4c),*(undefined4 *)(param_1 + 0x28));
  *(undefined4 *)(param_1 + 0x50) = uVar1;
  FUN_006a6270(*(undefined4 *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x4c));
  return;
}

