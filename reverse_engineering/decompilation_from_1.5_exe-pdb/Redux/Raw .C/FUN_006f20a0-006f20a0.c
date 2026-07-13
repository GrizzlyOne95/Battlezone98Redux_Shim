
void FUN_006f20a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_4c [56];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855213;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_006f5370(param_4);
  local_8 = 0;
  FUN_006f53e0(param_1,param_2,param_3,local_4c);
  local_8._0_1_ = 1;
  uVar4 = 1;
  uVar3 = 0;
  uVar2 = FUN_004fbb60(0,1,uVar1);
  FUN_006f5470(uVar2,uVar3,uVar4);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006f2450();
  FUN_00417c60();
  local_8 = 0xffffffff;
  FUN_006f23a0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

