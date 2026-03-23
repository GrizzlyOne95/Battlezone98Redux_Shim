
void FUN_007e0510(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 extraout_var;
  undefined4 uVar5;
  uint uVar6;
  undefined1 local_9c [7];
  undefined1 local_95;
  undefined1 local_94 [128];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086379b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar6 = 0;
  local_14 = uVar1;
  FUN_007e0b60(&local_95,param_2,param_3,param_4);
  puVar4 = &local_95;
  uVar3 = param_4;
  uVar5 = extraout_var;
  uVar2 = FUN_007e31c0(param_2,puVar4,param_4,uVar1,extraout_var);
  FUN_007e0c00(local_9c,uVar2,puVar4,uVar3);
  puVar4 = local_9c;
  uVar3 = FUN_007e3040(param_2,puVar4,param_4);
  FUN_007e0c30(local_94,uVar3,puVar4,param_4);
  local_8 = 0;
  FUN_007ddc30(local_94);
  local_8 = 0xffffffff;
  FUN_007dbb50(uVar1,uVar5,uVar6 | 1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

