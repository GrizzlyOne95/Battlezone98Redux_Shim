
void FUN_006fe1f0(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855eb9;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = FUN_00417780(param_1,uVar1);
  uVar3 = FUN_0070ae20(0x38,param_1,uVar1,uVar2);
  local_8 = 0;
  iVar4 = forward<>(0x38,uVar3);
  local_8._0_1_ = 1;
  if (iVar4 == 0) {
    local_18 = 0;
  }
  else {
    local_18 = FUN_00704230(param_1);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006acd90(local_18,0);
  local_8 = 0xffffffff;
  FUN_007042a0(uVar1,uVar2,0);
  ExceptionList = local_10;
  return;
}

