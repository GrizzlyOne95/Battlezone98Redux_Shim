
void FUN_0072b630(void)

{
  undefined4 uVar1;
  undefined4 uStack_3c;
  undefined1 *puStack_38;
  undefined4 uStack_34;
  undefined1 *puStack_30;
  uint uStack_2c;
  undefined4 local_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00859868;
  local_10 = ExceptionList;
  uStack_2c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  puStack_30 = &stack0x00000010;
  uStack_34 = 0x72b668;
  puStack_38 = (undefined1 *)FUN_00417780();
  uStack_3c = 0x72b676;
  local_1c = (undefined1 *)&uStack_34;
  local_20 = shared_ptr<>();
  local_8._0_1_ = 2;
  puStack_38 = &stack0x00000008;
  uStack_3c = 0x72b68c;
  local_14 = local_20;
  uVar1 = FUN_00417780();
  local_24 = (undefined1 *)&uStack_3c;
  local_28 = shared_ptr<>(uVar1);
  local_8._0_1_ = 1;
  (*(code *)*local_18)();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006c9420();
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return;
}

