
void FUN_007eb170(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_var;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined1 local_48 [52];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863f48;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar5 = 0;
  local_14 = uVar1;
  uVar2 = FUN_007eb4b0(local_48,param_2,param_3,param_4);
  local_8 = 0;
  uVar3 = extraout_var;
  uVar4 = uVar2;
  FUN_007ebc10(param_1,uVar2,param_4);
  local_8 = 0xffffffff;
  FUN_007dbb70(uVar1,uVar3,uVar2,uVar4,uVar5 | 1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

