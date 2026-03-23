
void FUN_007e2290(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_var;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863908;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  uVar2 = FUN_007e31e0(local_2c,param_2,param_3,param_4);
  local_8 = 0;
  FUN_007e3790(param_1,uVar2,param_3,uVar1,extraout_var);
  local_8 = 0xffffffff;
  FUN_00430320();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

