
void FUN_007e1260(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_b0 [20];
  uint local_9c;
  undefined1 local_94 [4];
  undefined1 local_90 [124];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086397b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_9c = 0;
  local_14 = uVar1;
  uVar2 = FUN_007e1640(param_2,param_3,param_4);
  FUN_007d9f70(uVar2);
  puVar4 = local_94;
  uVar2 = param_4;
  uVar3 = FUN_007e3090(param_2,puVar4,param_4,uVar1);
  FUN_007e1790(local_b0,uVar3,puVar4,uVar2);
  puVar4 = local_b0;
  uVar2 = FUN_007e3040(param_2,puVar4,param_4);
  FUN_007e17c0(local_90,uVar2,puVar4,param_4);
  local_8 = 0;
  FUN_007ddd00(local_90);
  local_9c = local_9c | 1;
  local_8 = 0xffffffff;
  FUN_007dbb70();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

