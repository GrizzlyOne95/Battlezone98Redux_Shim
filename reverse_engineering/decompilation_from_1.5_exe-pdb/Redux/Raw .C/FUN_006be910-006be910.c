
void FUN_006be910(void)

{
  uint uVar1;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00851598;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006cc550(1);
  FUN_006db850(local_14);
  local_8 = 0xffffffff;
  FUN_006c9420(uVar1);
  ExceptionList = local_10;
  return;
}

