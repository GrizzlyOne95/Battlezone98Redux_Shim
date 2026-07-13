
void FUN_00489dc0(void)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00849118;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_00489e20(&stack0x00000004);
  local_8 = 0xffffffff;
  FUN_00482800(uVar1);
  ExceptionList = local_10;
  return;
}

