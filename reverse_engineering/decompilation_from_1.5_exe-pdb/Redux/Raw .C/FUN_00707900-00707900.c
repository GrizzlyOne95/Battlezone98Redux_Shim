
void __thiscall FUN_00707900(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
    std::_Xbad_function_call();
  }
  uVar1 = FUN_00417780(&stack0x00000008);
  uVar1 = FUN_00417780(param_2,uVar1);
  (**(code **)(**(int **)(param_1 + 0x10) + 8))(uVar1);
  return;
}

