
void FUN_0072b6e0(void)

{
  undefined4 uVar1;
  undefined4 uStack_28;
  undefined1 *puStack_24;
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
  puStack_24 = &stack0x00000008;
  uStack_28 = 0x72b718;
  uVar1 = FUN_00417780();
  local_18 = (undefined1 *)&uStack_28;
  local_1c = shared_ptr<>(uVar1);
  (*(code *)*local_14)();
  local_8 = 0xffffffff;
  FUN_006c9420();
  ExceptionList = local_10;
  return;
}

