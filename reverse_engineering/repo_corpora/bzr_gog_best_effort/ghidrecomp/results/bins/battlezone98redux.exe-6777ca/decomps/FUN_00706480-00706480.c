
void FUN_00706480(int param_1,int param_2,undefined4 *param_3)

{
  undefined1 local_40 [20];
  undefined4 local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856f70;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_20 = *param_3;
  local_1c = param_3[1];
  local_18 = param_2;
  local_2c = FUN_00417780(param_2 + 0x38,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_28 = local_18;
  local_24 = local_18;
  local_8 = 0;
  FUN_006af160(local_18 + 0x28,&local_20);
  FUN_006d57f0(*(undefined4 *)(local_18 + 0x24));
  FUN_007080f0(local_18 + 0x38,&local_20,&stack0x00000010);
  local_2c = FUN_00417780(local_40);
  FUN_00706580();
  if (param_1 != 0) {
    FUN_006acde0(0);
    local_8._0_1_ = 1;
    FUN_0070f9e0(local_40,local_40);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006ace20();
  }
  local_8 = 0xffffffff;
  FUN_00703c90();
  ExceptionList = local_10;
  return;
}

