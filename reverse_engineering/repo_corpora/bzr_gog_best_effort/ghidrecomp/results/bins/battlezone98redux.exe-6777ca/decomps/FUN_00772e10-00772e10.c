
void FUN_00772e10(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 local_c8 [180];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e0fb;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar1 = FUN_00417780(param_1,local_14);
  FUN_00753550(uVar1);
  local_8 = 0;
  uVar1 = FUN_00417780(param_2);
  FUN_007529c0(uVar1);
  uVar1 = FUN_00417780(local_c8);
  FUN_007529c0(uVar1);
  local_8 = 0xffffffff;
  FUN_00753670();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

