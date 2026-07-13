
void FUN_006fe880(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 extraout_var;
  undefined4 uVar2;
  undefined1 local_7c [104];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855f98;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_006f4ac0(param_3);
  local_8 = 0;
  uVar2 = extraout_var;
  FUN_0070dea0(param_1,param_2,local_7c);
  FUN_00417c60(uVar1,uVar2);
  local_8 = 0xffffffff;
  FUN_006e4540();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

