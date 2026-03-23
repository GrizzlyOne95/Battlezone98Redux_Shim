
void FUN_00706350(int param_1,int param_2)

{
  undefined1 local_34 [16];
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856f40;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_18 = param_2;
  local_24 = FUN_00417780(param_2 + 0x28,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_20 = local_18;
  local_1c = local_18;
  local_8 = 0;
  FUN_007080b0(local_18 + 0x28,local_18 + 0x20);
  local_24 = FUN_00417780(local_34);
  FUN_00706420();
  if (param_1 != 0) {
    FUN_006acde0(0);
    local_8._0_1_ = 1;
    FUN_0070f990(local_34,local_34);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006ace20();
  }
  local_8 = 0xffffffff;
  FUN_00703b30();
  ExceptionList = local_10;
  return;
}

