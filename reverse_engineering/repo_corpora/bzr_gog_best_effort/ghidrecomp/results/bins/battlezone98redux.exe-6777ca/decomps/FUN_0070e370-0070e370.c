
void __thiscall FUN_0070e370(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_5c [72];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857808;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00712120(param_2);
  local_8 = 0;
  FUN_00718c90(param_1 + 4,local_5c);
  FUN_00417c60(uVar1);
  local_8 = 0xffffffff;
  FUN_0070ff00();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

