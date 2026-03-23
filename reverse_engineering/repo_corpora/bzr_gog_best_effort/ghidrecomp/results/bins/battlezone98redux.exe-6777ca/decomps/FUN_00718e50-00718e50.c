
void FUN_00718e50(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 in_stack_00000020;
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  undefined1 *puStack_2c;
  undefined4 uStack_28;
  undefined1 *puStack_24;
  uint uStack_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00858288;
  local_10 = ExceptionList;
  uStack_20 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_24 = &stack0x00000024;
  uStack_28 = 0x718e88;
  puVar1 = (undefined4 *)FUN_00417780();
  puStack_24 = (undefined1 *)*puVar1;
  uStack_28 = in_stack_00000020;
  puStack_2c = (undefined1 *)0x718e97;
  uStack_28 = FUN_00417780();
  puStack_2c = &stack0x00000008;
  uStack_30 = 0x718ea4;
  uVar2 = FUN_00417780();
  local_18 = auStack_40;
  local_1c = FUN_006f62b0(uVar2);
  FUN_00421ec0();
  (*(code *)*local_14)();
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000008);
  ExceptionList = local_10;
  return;
}

