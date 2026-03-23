
void FUN_006e4c20(void)

{
  undefined4 uStack_28;
  undefined1 *puStack_24;
  uint uStack_20;
  undefined4 local_1c;
  undefined1 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00853fb8;
  local_10 = ExceptionList;
  uStack_20 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_24 = &stack0x00000004;
  uStack_28 = 0x6e4c5e;
  FUN_006c9440();
  local_18 = (undefined1 *)&uStack_28;
  local_1c = shared_ptr<>(&stack0x00000004);
  FUN_006bb710();
  local_8 = 0xffffffff;
  puStack_24 = (undefined1 *)0x6e4c89;
  FUN_006c9420();
  ExceptionList = local_10;
  return;
}

