
void FUN_006f0540(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 extraout_var;
  undefined4 uVar2;
  undefined1 local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854e48;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_006f4870(param_2);
  local_8 = 0;
  uVar2 = extraout_var;
  FUN_006fde00(param_1,local_54);
  FUN_00417c60(uVar1,uVar2);
  local_8 = 0xffffffff;
  FUN_006f2210();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

