
void FUN_00700990(void)

{
  undefined4 uVar1;
  undefined4 in_stack_00000030;
  undefined4 uStack_64;
  undefined1 *puStack_60;
  undefined4 uStack_5c;
  undefined1 *puStack_58;
  undefined1 auStack_54 [16];
  undefined4 uStack_44;
  undefined1 *puStack_40;
  undefined4 uStack_3c;
  uint uStack_38;
  undefined4 local_34;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined4 *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00856538;
  local_10 = ExceptionList;
  uStack_38 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 2;
  uStack_3c = in_stack_00000030;
  puStack_40 = (undefined1 *)0x7009c8;
  uStack_3c = FUN_00417780();
  puStack_40 = &stack0x00000018;
  uStack_44 = 0x7009d5;
  puStack_58 = (undefined1 *)FUN_00417780();
  local_20 = auStack_54;
  uStack_5c = 0x7009e3;
  local_24 = FUN_006f62b0();
  local_8._0_1_ = 3;
  puStack_58 = &stack0x00000010;
  uStack_5c = 0x7009f9;
  local_14 = local_24;
  puStack_60 = (undefined1 *)FUN_00417780();
  uStack_64 = 0x700a07;
  local_28 = (undefined1 *)&uStack_5c;
  local_2c = shared_ptr<>();
  local_8._0_1_ = 4;
  puStack_60 = &stack0x00000008;
  uStack_64 = 0x700a1d;
  local_18 = local_2c;
  uVar1 = FUN_00417780();
  local_30 = (undefined1 *)&uStack_64;
  local_34 = shared_ptr<>(uVar1);
  local_8._0_1_ = 2;
  (*(code *)*local_1c)();
  local_8._0_1_ = 1;
  FUN_006ca8c0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000018);
  ExceptionList = local_10;
  return;
}

