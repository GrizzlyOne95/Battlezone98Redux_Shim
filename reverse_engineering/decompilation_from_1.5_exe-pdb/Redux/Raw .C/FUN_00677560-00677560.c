
void FUN_00677560(undefined4 param_1,int param_2,undefined1 param_3)

{
  undefined4 uVar1;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f068;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar1 = FUN_00417780(param_2 + -0x18,local_14);
  basic_string<>(uVar1);
  local_8 = 0;
  uVar1 = _Val_type<>(param_1);
  uVar1 = FUN_00417780(local_2c,param_3,uVar1);
  FUN_006779a0(param_1,param_2 + -0x18,param_2 + -0x18,uVar1);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

