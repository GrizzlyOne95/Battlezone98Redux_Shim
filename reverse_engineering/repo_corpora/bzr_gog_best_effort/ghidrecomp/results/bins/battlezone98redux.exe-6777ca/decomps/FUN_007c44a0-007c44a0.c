
void __fastcall FUN_007c44a0(int param_1)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00848fa8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  uVar1 = FUN_0041f870(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  (**(code **)(**(int **)(param_1 + 0x148) + 0x3c))(uVar1);
  uVar1 = FUN_007ccaf0();
  FUN_007cca20(uVar1);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return;
}

