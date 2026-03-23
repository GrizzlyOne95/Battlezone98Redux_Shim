
void FUN_007e5130(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 extraout_var;
  undefined4 uVar5;
  uint uVar6;
  undefined1 local_38 [7];
  undefined1 local_31;
  undefined1 local_30 [28];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863ba8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar6 = 0;
  local_14 = uVar1;
  FUN_007e0b60(&local_31,param_2,param_3,param_4);
  puVar4 = &local_31;
  uVar3 = param_4;
  uVar5 = extraout_var;
  uVar2 = FUN_007e3090(param_2,puVar4,param_4,uVar1,extraout_var);
  FUN_007e5570(local_38,uVar2,puVar4,uVar3);
  puVar4 = local_38;
  uVar3 = FUN_007e7720(param_2,puVar4,param_4);
  FUN_007e55a0(local_30,uVar3,puVar4,param_4);
  local_8 = 0;
  FUN_007de890(local_30);
  local_8 = 0xffffffff;
  FUN_007dbb70(uVar1,uVar5,uVar6 | 1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

