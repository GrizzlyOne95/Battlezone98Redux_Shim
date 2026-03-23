
void FUN_007eb4b0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_70 [32];
  uint local_50;
  undefined1 local_49;
  undefined1 local_48 [52];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863f78;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_50 = 0;
  local_14 = uVar1;
  FUN_007e0b60(&local_49,param_2,param_3,param_4);
  puVar4 = &local_49;
  uVar3 = param_4;
  uVar2 = FUN_007e3090(param_2,puVar4,param_4,uVar1);
  FUN_007eb5f0(local_70,uVar2,puVar4,uVar3);
  puVar4 = local_70;
  uVar3 = FUN_007e3040(param_2,puVar4,param_4);
  FUN_007eb620(local_48,uVar3,puVar4,param_4);
  local_8 = 0;
  FUN_007de7a0(local_48);
  local_50 = local_50 | 1;
  local_8 = 0xffffffff;
  FUN_007dbb70();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

