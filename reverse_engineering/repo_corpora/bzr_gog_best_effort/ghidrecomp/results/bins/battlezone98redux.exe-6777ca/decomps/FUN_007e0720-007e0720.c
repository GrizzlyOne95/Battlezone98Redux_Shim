
void FUN_007e0720(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 extraout_var;
  undefined4 uVar5;
  uint uVar6;
  undefined1 local_98 [7];
  undefined1 local_91;
  undefined1 local_90 [124];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008637db;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar6 = 0;
  local_14 = uVar1;
  FUN_007e0b60(&local_91,param_2,param_3,param_4);
  puVar4 = &local_91;
  uVar3 = param_4;
  uVar5 = extraout_var;
  uVar2 = FUN_007e31c0(param_2,puVar4,param_4,uVar1,extraout_var);
  FUN_007e0c00(local_98,uVar2,puVar4,uVar3);
  puVar4 = local_98;
  uVar3 = FUN_007e3040(param_2,puVar4,param_4);
  FUN_007e0d30(local_90,uVar3,puVar4,param_4);
  local_8 = 0;
  FUN_007ddd00(local_90);
  local_8 = 0xffffffff;
  FUN_007dbb70(uVar1,uVar5,uVar6 | 1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

