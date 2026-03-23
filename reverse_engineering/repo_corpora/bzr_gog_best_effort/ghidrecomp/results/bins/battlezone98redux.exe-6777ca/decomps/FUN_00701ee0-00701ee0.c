
undefined4 FUN_00701ee0(undefined4 param_1)

{
  uint uVar1;
  undefined4 extraout_var;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008566f8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_0070f160(0x17);
  local_8 = 0xffffffff;
  FUN_006ca8c0(uVar1,extraout_var);
  ExceptionList = local_10;
  return param_1;
}

