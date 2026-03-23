
void FUN_006d1f30(void)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008531a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_006b23d0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_006ddfd0(uVar1);
  local_8 = 0xffffffff;
  FUN_006b2390();
  ExceptionList = local_10;
  return;
}

