
void FUN_00805700(void)

{
  int iVar1;
  undefined4 in_stack_00000018;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008648f1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = forward<>(0x14,in_stack_00000018,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (iVar1 != 0) {
    FUN_007fe040(&stack0x00000004);
  }
  ExceptionList = local_10;
  return;
}

