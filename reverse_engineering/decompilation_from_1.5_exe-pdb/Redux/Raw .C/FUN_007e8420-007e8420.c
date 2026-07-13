
void FUN_007e8420(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_94 [20];
  uint local_80;
  undefined1 local_79;
  undefined1 local_78 [100];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863d08;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_80 = 0;
  local_14 = uVar1;
  FUN_007e0b60(&local_79,param_2,param_3,param_4);
  puVar4 = &local_79;
  uVar3 = param_4;
  uVar2 = FUN_007e3090(param_2,puVar4,param_4,uVar1);
  FUN_007e8580(local_94,uVar2,puVar4,uVar3);
  puVar4 = local_94;
  uVar3 = FUN_007e3040(param_2,puVar4,param_4);
  FUN_007e85b0(local_78,uVar3,puVar4,param_4);
  local_8 = 0;
  FUN_007de350(local_78);
  local_80 = local_80 | 1;
  local_8 = 0xffffffff;
  ~<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

