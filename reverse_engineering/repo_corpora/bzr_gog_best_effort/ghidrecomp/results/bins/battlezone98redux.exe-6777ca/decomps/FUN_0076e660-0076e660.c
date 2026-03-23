
void FUN_0076e660(void)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085dc88;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_007529c0(&stack0x00000004);
  local_8 = 0xffffffff;
  FUN_00753670(uVar1);
  ExceptionList = local_10;
  return;
}

