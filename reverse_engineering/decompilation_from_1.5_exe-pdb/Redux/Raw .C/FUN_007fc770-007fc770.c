
undefined4
FUN_007fc770(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined1 local_28 [20];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864518;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = 0;
  FUN_007fd0e0(local_28,param_2,param_3,param_4,param_5,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_007fc640(local_28);
  local_14 = local_14 | 1;
  local_8 = 0xffffffff;
  FUN_007fb7c0();
  ExceptionList = local_10;
  return param_1;
}

