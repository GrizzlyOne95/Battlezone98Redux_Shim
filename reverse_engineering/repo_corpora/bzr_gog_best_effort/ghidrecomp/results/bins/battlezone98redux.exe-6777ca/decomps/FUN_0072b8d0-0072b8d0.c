
void FUN_0072b8d0(void)

{
  undefined4 uVar1;
  undefined4 in_stack_00000030;
  undefined4 uStack_7c;
  undefined1 *puStack_78;
  undefined4 uStack_74;
  undefined1 *puStack_70;
  undefined1 auStack_6c [16];
  undefined4 uStack_5c;
  undefined1 *puStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [4];
  undefined4 uStack_4c;
  undefined1 *puStack_48;
  uint uStack_44;
  undefined4 local_40;
  undefined1 *local_3c;
  undefined4 local_38;
  undefined1 *local_34;
  undefined4 local_30;
  undefined1 *local_2c;
  undefined4 local_28;
  undefined1 *local_24;
  undefined4 *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00859908;
  local_10 = ExceptionList;
  uStack_44 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 3;
  puStack_48 = &stack0x00000034;
  uStack_4c = 0x72b908;
  uStack_54 = FUN_00417780();
  local_24 = auStack_50;
  puStack_58 = (undefined1 *)0x72b916;
  local_28 = FUN_006d4f40();
  local_8._0_1_ = 4;
  uStack_54 = in_stack_00000030;
  puStack_58 = (undefined1 *)0x72b92c;
  local_14 = local_28;
  uStack_54 = FUN_00417780();
  puStack_58 = &stack0x00000018;
  uStack_5c = 0x72b939;
  puStack_70 = (undefined1 *)FUN_00417780();
  local_2c = auStack_6c;
  uStack_74 = 0x72b947;
  local_30 = FUN_006f62b0();
  local_8._0_1_ = 5;
  puStack_70 = &stack0x00000010;
  uStack_74 = 0x72b95d;
  local_18 = local_30;
  puStack_78 = (undefined1 *)FUN_00417780();
  uStack_7c = 0x72b96b;
  local_34 = (undefined1 *)&uStack_74;
  local_38 = shared_ptr<>();
  local_8._0_1_ = 6;
  puStack_78 = &stack0x00000008;
  uStack_7c = 0x72b981;
  local_1c = local_38;
  uVar1 = FUN_00417780();
  local_3c = (undefined1 *)&uStack_7c;
  local_40 = shared_ptr<>(uVar1);
  local_8._0_1_ = 3;
  (*(code *)*local_20)();
  local_8._0_1_ = 2;
  FUN_006ca8c0();
  local_8._0_1_ = 1;
  FUN_006ca8c0();
  local_8 = (uint)local_8._1_3_ << 8;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000018);
  local_8 = 0xffffffff;
  FUN_006cd590();
  ExceptionList = local_10;
  return;
}

