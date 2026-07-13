
void FUN_00805780(void)

{
  int iVar1;
  undefined4 in_stack_00000014;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864921;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = forward<>(0x10,in_stack_00000014,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (iVar1 != 0) {
    FUN_007fe060(&stack0x00000004);
  }
  ExceptionList = local_10;
  return;
}

