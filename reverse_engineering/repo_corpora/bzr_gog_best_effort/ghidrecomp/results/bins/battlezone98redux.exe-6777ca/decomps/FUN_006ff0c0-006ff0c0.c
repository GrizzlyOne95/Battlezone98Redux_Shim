
void FUN_006ff0c0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856123;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_007045e0(param_3);
  local_8 = 0;
  uVar1 = FUN_006b2d70(uVar2);
  FUN_00704650(param_1,param_2,uVar1,local_54);
  local_8._0_1_ = 1;
  uVar5 = 1;
  uVar4 = 0;
  uVar3 = FUN_004fbb60(0,1);
  FUN_007046e0(uVar3,uVar4,uVar5);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ff970();
  FUN_00417c60();
  local_8 = 0xffffffff;
  FUN_006ff950();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

