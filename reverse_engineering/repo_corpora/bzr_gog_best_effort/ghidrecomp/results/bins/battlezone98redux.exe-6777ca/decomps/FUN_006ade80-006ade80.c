
void __thiscall FUN_006ade80(int param_1,undefined4 param_2)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008501b8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006c8ce0(param_1 + 0x38);
  local_8 = 0;
  FUN_006acac0(param_2);
  local_8 = 0xffffffff;
  FUN_006c8d50(uVar1);
  ExceptionList = local_10;
  return;
}

