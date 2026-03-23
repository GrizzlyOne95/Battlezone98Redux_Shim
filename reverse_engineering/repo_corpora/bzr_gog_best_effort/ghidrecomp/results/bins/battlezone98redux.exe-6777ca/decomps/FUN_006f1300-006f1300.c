
void FUN_006f1300(undefined4 param_1)

{
  uint uVar1;
  undefined4 extraout_var;
  undefined4 uVar2;
  undefined1 local_8c [120];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854fab;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_006f4a50(param_1);
  local_8 = 0;
  uVar2 = extraout_var;
  FUN_006fe7a0(local_8c);
  FUN_00417c60(uVar1,uVar2);
  local_8 = 0xffffffff;
  FUN_006f22b0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

