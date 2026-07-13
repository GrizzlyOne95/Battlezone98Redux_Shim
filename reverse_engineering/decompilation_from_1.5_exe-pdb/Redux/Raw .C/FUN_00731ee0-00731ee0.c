
void __thiscall FUN_00731ee0(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_cc [184];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859e5b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00732f50(param_2);
  local_8 = 0;
  FUN_00733940(param_1 + 4,local_cc);
  FUN_00417c60(uVar1);
  local_8 = 0xffffffff;
  FUN_00732a70();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

