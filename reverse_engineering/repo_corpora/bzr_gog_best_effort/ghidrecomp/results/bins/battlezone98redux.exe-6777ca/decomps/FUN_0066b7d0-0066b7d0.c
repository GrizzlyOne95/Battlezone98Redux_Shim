
void FUN_0066b7d0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  uint uStack_2c;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e9a8;
  local_10 = ExceptionList;
  uStack_2c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_2c;
  ExceptionList = &local_10;
  uVar1 = FUN_00424670(&local_16);
  FUN_0066c340(uVar1,param_2);
  local_8 = 1;
  local_15 = 0;
  FUN_0066ed60(param_1,0);
  FUN_0066b852();
  return;
}

