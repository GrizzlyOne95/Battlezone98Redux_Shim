
void FUN_007e1c10(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_110 [100];
  undefined1 local_ac [20];
  uint local_98;
  undefined1 local_90 [124];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863a5b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_98 = 0;
  local_14 = uVar1;
  uVar2 = FUN_007e1640(param_2,param_3,param_4);
  FUN_007de410(uVar2);
  puVar4 = local_ac;
  uVar2 = param_4;
  uVar3 = FUN_007e3090(param_2,puVar4,param_4,uVar1);
  FUN_007e1fd0(local_110,uVar3,puVar4,uVar2);
  puVar4 = local_110;
  uVar2 = FUN_007e3040(param_2,puVar4,param_4);
  FUN_007e2000(local_90,uVar2,puVar4,param_4);
  local_8 = 0;
  FUN_007ddd00(local_90);
  local_98 = local_98 | 1;
  local_8 = 0xffffffff;
  FUN_007dbb70();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

