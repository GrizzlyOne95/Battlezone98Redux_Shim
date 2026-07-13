
void FUN_0070e6f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 extraout_var;
  undefined4 uVar2;
  undefined1 local_84 [112];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857898;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00712190(param_4);
  local_8 = 0;
  uVar2 = extraout_var;
  FUN_00719720(param_1,param_2,param_3,local_84);
  FUN_00417c60(uVar1,uVar2);
  local_8 = 0xffffffff;
  FUN_0070ff60();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

