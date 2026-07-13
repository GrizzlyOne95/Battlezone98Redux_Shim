
void __fastcall FUN_006f2840(int param_1)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_008552d0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
    std::_Xbad_function_call();
  }
  uVar1 = FUN_00417780(&stack0x0000000c,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  uVar1 = FUN_00417780(&stack0x00000004,uVar1);
  (**(code **)(**(int **)(param_1 + 0x10) + 8))(uVar1);
  local_8 = local_8 & 0xffffff00;
  FUN_006c9420();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return;
}

