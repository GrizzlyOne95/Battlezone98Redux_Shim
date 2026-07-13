
void FUN_006e8150(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 local_34;
  uint local_30;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a048;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = 0;
  FUN_006d9b70(&local_34,param_2,param_3,FUN_006b6820,local_14);
  uVar1 = FUN_006c8830(param_2,local_34);
  local_8 = 0;
  FUN_006f7b80(param_1,uVar1,&local_34);
  local_30 = local_30 | 1;
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

