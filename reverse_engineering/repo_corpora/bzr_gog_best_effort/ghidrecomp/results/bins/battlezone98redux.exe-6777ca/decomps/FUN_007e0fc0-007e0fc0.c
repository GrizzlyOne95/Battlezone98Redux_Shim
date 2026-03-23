
void FUN_007e0fc0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 extraout_var;
  undefined4 uVar5;
  uint uVar6;
  undefined1 local_100 [4];
  undefined1 local_fc [128];
  undefined1 local_7c [104];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863943;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar6 = 0;
  local_14 = uVar1;
  uVar2 = FUN_007e1640(param_2,param_3,param_4);
  uVar5 = extraout_var;
  FUN_007d9f70(uVar2);
  puVar4 = local_100;
  uVar2 = param_4;
  uVar3 = FUN_007e3090(param_2,puVar4,param_4,uVar1,uVar5);
  FUN_007e1650(local_7c,uVar3,puVar4,uVar2);
  local_8 = 0;
  puVar4 = local_7c;
  uVar2 = FUN_007e3040(param_2,puVar4,param_4);
  FUN_007e1690(local_fc,uVar2,puVar4,param_4);
  local_8._0_1_ = 1;
  FUN_007ddc30(local_fc);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007dbb50(uVar1,uVar5,uVar6 | 1);
  local_8 = 0xffffffff;
  FUN_007dbbb0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

