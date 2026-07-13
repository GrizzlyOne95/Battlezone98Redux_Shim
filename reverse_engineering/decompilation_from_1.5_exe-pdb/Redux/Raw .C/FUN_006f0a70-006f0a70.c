
void FUN_006f0a70(undefined4 param_1)

{
  uint uVar1;
  undefined4 extraout_var;
  undefined4 uVar2;
  undefined1 local_3c [40];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854ec8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_006f48e0(param_1);
  local_8 = 0;
  uVar2 = extraout_var;
  FUN_006fe110(local_3c);
  FUN_00417c60(uVar1,uVar2);
  local_8 = 0xffffffff;
  FUN_006f2260();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

