
void FUN_0070dea0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008577d9;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = FUN_00417780(param_3,uVar1);
  uVar3 = FUN_00718890(0x98,param_3,uVar1,uVar2);
  local_8 = 0;
  iVar4 = forward<>(0x98,uVar3);
  local_8._0_1_ = 1;
  if (iVar4 == 0) {
    local_18 = 0;
  }
  else {
    local_18 = FUN_00712020(*param_1,param_3);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  uVar3 = FUN_006d6170(local_18);
  uVar5 = FUN_006d0d10(uVar3);
  uVar6 = FUN_006b3f60(uVar5);
  uVar7 = get(uVar6);
  FUN_006b1c80(param_1,uVar7,uVar6,uVar5,uVar3,local_18);
  local_8 = 0xffffffff;
  FUN_00712090(uVar1,uVar2,0);
  ExceptionList = local_10;
  return;
}

