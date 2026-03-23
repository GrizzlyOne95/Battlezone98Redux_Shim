
void FUN_00727520(int param_1,int param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 local_9c;
  undefined4 local_98;
  int local_94;
  undefined1 local_8c [120];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859231;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_9c = *param_3;
  local_98 = param_3[1];
  local_94 = param_2;
  local_14 = uVar1;
  uVar2 = FUN_00417780(param_2 + 0x48,uVar1);
  local_8 = 0;
  FUN_006af160(local_94 + 0x20,&local_9c,uVar1,uVar2,local_94,local_94);
  FUN_007278e0(local_94 + 0x48,&local_9c,&stack0x00000010);
  local_8._0_1_ = 1;
  uVar2 = FUN_00417780(local_8c);
  FUN_00727680(uVar1,uVar2);
  if (param_1 != 0) {
    FUN_006acde0(0);
    local_8._0_1_ = 2;
    FUN_0072b2c0(local_8c,local_8c);
    local_8._0_1_ = 1;
    FUN_006ace20();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0071b5a0();
  local_8 = 0xffffffff;
  FUN_00726a20();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

