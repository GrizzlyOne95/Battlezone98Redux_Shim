
int FUN_006f3220(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_1c [8];
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008553c8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006f61c0(param_1);
  local_8 = 0;
  FUN_004fbb60(uVar1);
  FUN_006f6190(local_14 + 8,param_2,local_1c);
  FUN_006aba00(local_1c,"expires_from_now");
  ExceptionList = local_10;
  return local_14;
}

