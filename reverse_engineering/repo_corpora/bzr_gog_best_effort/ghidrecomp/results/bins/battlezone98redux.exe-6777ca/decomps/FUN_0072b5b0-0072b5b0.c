
void FUN_0072b5b0(void)

{
  undefined4 uVar1;
  undefined4 in_stack_00000010;
  undefined4 uStack_2c;
  undefined1 *puStack_28;
  undefined4 uStack_24;
  uint uStack_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00859828;
  local_10 = ExceptionList;
  uStack_20 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uStack_24 = in_stack_00000010;
  puStack_28 = (undefined1 *)0x72b5e8;
  uStack_24 = FUN_00417780();
  puStack_28 = &stack0x00000008;
  uStack_2c = 0x72b5f5;
  uVar1 = FUN_00417780();
  local_18 = (undefined1 *)&uStack_2c;
  local_1c = shared_ptr<>(uVar1);
  (*(code *)*local_14)();
  local_8 = 0xffffffff;
  FUN_006c9420();
  ExceptionList = local_10;
  return;
}

