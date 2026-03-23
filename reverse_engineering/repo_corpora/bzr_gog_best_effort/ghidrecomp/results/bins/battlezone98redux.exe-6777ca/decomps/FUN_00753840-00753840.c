
undefined4 * __fastcall FUN_00753840(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c20b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cFriend::vftable;
  FUN_0073a6b0(uVar1);
  basic_string<>();
  local_8 = 0;
  basic_string<>();
  *(undefined1 *)(param_1 + 0x12) = 0;
  ExceptionList = local_10;
  return param_1;
}

