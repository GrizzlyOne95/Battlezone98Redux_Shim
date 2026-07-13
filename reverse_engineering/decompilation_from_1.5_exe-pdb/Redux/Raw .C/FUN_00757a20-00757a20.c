
void FUN_00757a20(undefined4 param_1,int param_2,undefined1 param_3)

{
  undefined4 uVar1;
  undefined1 local_64 [80];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c5a8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar1 = FUN_00417780(param_2 + -0x50,local_14);
  FUN_00756b80(uVar1);
  local_8 = 0;
  uVar1 = _Val_type<>(param_1);
  uVar1 = FUN_00417780(local_64,param_3,uVar1);
  FUN_00757b10(param_1,param_2 + -0x50,param_2 + -0x50,uVar1);
  local_8 = 0xffffffff;
  FUN_007538f0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

