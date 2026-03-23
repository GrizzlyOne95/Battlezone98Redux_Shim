
undefined4 __thiscall FUN_007dcae0(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008633c8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007df050(param_2,0);
  local_8 = 0;
  FUN_007ddb70(param_1);
  local_8 = 0xffffffff;
  FUN_007d7950(uVar1);
  ExceptionList = local_10;
  return param_1;
}

