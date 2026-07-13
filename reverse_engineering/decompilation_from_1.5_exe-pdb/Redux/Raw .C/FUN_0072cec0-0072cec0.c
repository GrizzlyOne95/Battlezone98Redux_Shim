
void FUN_0072cec0(int param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 local_8c;
  undefined4 local_88;
  int local_80;
  undefined1 local_7c [104];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859abb;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8c = *param_3;
  local_88 = param_3[1];
  local_80 = param_2;
  local_14 = uVar2;
  uVar3 = FUN_00417780(param_2 + 0x38,uVar2);
  local_8 = 0;
  uVar1 = __Current_set(local_80 + 0x2c,&local_8c,param_4,uVar2,uVar3,local_80,local_80);
  FUN_006af0d0(*(undefined1 *)(local_80 + 0x20),local_80 + 0x24,uVar1);
  FUN_0072d5f0(local_80 + 0x38,&local_8c,&param_4);
  local_8._0_1_ = 1;
  uVar3 = FUN_00417780(local_7c);
  FUN_0072d010(uVar2,uVar3);
  if (param_1 != 0) {
    FUN_006acde0(0);
    local_8._0_1_ = 2;
    FUN_007302f0(local_7c,local_7c);
    local_8._0_1_ = 1;
    FUN_006ace20();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00726020();
  local_8 = 0xffffffff;
  FUN_0072c6c0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

