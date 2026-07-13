
void FUN_0072d070(int param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 local_84;
  undefined4 local_80;
  int local_78;
  undefined1 local_74 [96];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859b0b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_84 = *param_3;
  local_80 = param_3[1];
  local_78 = param_2;
  local_14 = uVar2;
  uVar3 = FUN_00417780(param_2 + 0x38,uVar2);
  local_8 = 0;
  uVar1 = __Current_set(local_78 + 0x2c,&local_84,param_4,uVar2,uVar3,local_78,local_78);
  FUN_006af0d0(*(undefined1 *)(local_78 + 0x20),local_78 + 0x24,uVar1);
  FUN_0072d630(local_78 + 0x38,&local_84,&param_4);
  local_8._0_1_ = 1;
  uVar3 = FUN_00417780(local_74);
  FUN_0072d1b0(uVar2,uVar3);
  if (param_1 != 0) {
    FUN_006acde0(0);
    local_8._0_1_ = 2;
    FUN_00730340(local_74,local_74);
    local_8._0_1_ = 1;
    FUN_006ace20();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00726040();
  local_8 = 0xffffffff;
  FUN_0072c780();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

