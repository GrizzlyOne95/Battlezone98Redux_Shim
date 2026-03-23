
void FUN_007e0830(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 extraout_var;
  undefined4 uVar5;
  uint uVar6;
  undefined1 local_61;
  undefined1 local_60 [44];
  undefined1 local_34 [32];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863890;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar6 = 0;
  local_14 = uVar1;
  FUN_007e0b60(&local_61,param_2,param_3,param_4);
  puVar4 = &local_61;
  uVar3 = param_4;
  uVar5 = extraout_var;
  uVar2 = FUN_007e3090(param_2,puVar4,param_4,uVar1,extraout_var);
  FUN_007e0d70(local_34,uVar2,puVar4,uVar3);
  local_8 = 0;
  puVar4 = local_34;
  uVar3 = FUN_007e3040(param_2,puVar4,param_4);
  FUN_007e0db0(local_60,uVar3,puVar4,param_4);
  local_8._0_1_ = 1;
  FUN_007ddd70(local_60);
  local_8 = (uint)local_8._1_3_ << 8;
  ~input_processor<>(uVar1,uVar5,uVar6 | 1);
  local_8 = 0xffffffff;
  FUN_007dba50();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

