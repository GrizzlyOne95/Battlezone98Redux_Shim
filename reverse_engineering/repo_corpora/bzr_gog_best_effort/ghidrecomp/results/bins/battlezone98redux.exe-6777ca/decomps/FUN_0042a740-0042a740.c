
undefined4 FUN_0042a740(undefined4 param_1,undefined1 param_2)

{
  uint uVar1;
  undefined1 local_20 [8];
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845638;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0042daa0(param_1);
  local_8 = 0;
  local_18 = FUN_0042e130(local_20,param_2);
  local_8 = 0xffffffff;
  FUN_0042d420(uVar1);
  ExceptionList = local_10;
  return local_18;
}

