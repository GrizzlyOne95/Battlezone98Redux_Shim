
undefined4 FUN_0073d480(undefined4 param_1,undefined4 param_2,undefined1 param_3)

{
  undefined1 local_20 [12];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ab78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = 0;
  vector<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_0073d3a0(param_2,param_3,local_20);
  FUN_00748080(local_20);
  local_14 = local_14 | 1;
  local_8 = 0xffffffff;
  FUN_0048a040();
  ExceptionList = local_10;
  return param_1;
}

