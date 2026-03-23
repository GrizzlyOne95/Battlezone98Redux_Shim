
void FUN_0072b810(void)

{
  undefined4 uVar1;
  undefined4 in_stack_00000028;
  undefined4 uStack_50;
  undefined1 *puStack_4c;
  undefined1 auStack_48 [16];
  undefined4 uStack_38;
  undefined1 *puStack_34;
  undefined4 uStack_30;
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
  
  puStack_c = &LAB_008598a8;
  local_10 = ExceptionList;
  uStack_2c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  uStack_30 = in_stack_00000028;
  puStack_34 = (undefined1 *)0x72b848;
  uStack_30 = FUN_00417780();
  puStack_34 = &stack0x00000010;
  uStack_38 = 0x72b855;
  puStack_4c = (undefined1 *)FUN_00417780();
  local_1c = auStack_48;
  uStack_50 = 0x72b863;
  local_20 = FUN_006f62b0();
  local_8._0_1_ = 2;
  puStack_4c = &stack0x00000008;
  uStack_50 = 0x72b879;
  local_14 = local_20;
  uVar1 = FUN_00417780();
  local_24 = (undefined1 *)&uStack_50;
  local_28 = shared_ptr<>(uVar1);
  local_8._0_1_ = 1;
  (*(code *)*local_18)();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000010);
  ExceptionList = local_10;
  return;
}

