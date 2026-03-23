
void __fastcall FUN_006e6250(int param_1)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00851598;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
    std::_Xbad_function_call();
  }
  uVar1 = FUN_00417780(&stack0x00000004,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  (**(code **)(**(int **)(param_1 + 0x10) + 8))(uVar1);
  local_8 = 0xffffffff;
  FUN_006c9420();
  ExceptionList = local_10;
  return;
}

